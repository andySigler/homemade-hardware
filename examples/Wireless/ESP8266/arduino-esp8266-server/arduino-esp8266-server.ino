/*

This example demos using the ESP8266 control an LED by creating an HTTP server.

1) Enter your wifi credentials into the variables `wifi_name` and `wifi_password`
2) Upload to ESP8266
3) Open Serial monitor at baudrate 115200 to see print statements from ESP8266

The ESP8266 will then attempt to connect to the wifi network, blinking it's LED while waiting.

Once connected, make sure your computer is on the same wifi network.
Point your browser to the URL: "esp8266.local/on"
  - then, the LED will turn on

All the URLs you can point to:

1) "esp8266.local" (get the current LED brightness)
2) "esp8266.local/on" (turn the LED on)
3) "esp8266.local/off" (turn the LED off)
4) "esp8266.local/random" (turn the LED off)

*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* wifi_name = "WIFI_NAME";
const char* wifi_password = "";

const int led_pin = 2;
int brightness = 0;

ESP8266WebServer server(80);

void wifi_connect(void) {
  WiFi.mode(WIFI_STA);
  if (wifi_password && strlen(wifi_password) > 0) {
    WiFi.begin(wifi_name, wifi_password);
  } else {
    WiFi.begin(wifi_name);
  }
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(led_pin, HIGH);
    delay(250);
    digitalWrite(led_pin, LOW);
    delay(250);
    Serial.print(".");
  }
}

void handle_not_found() {
  server.send(404, "text/plain", "File Not Found");
}

void handle_response(int new_brightness) {
  Serial.println("Got HTTP request: " + String(new_brightness));
  if (new_brightness >= 0) {
    brightness = new_brightness;
  }
  server.send(200, "text/plain", "Brightness: " + String(brightness));
}

void create_server(void) {
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
  server.onNotFound(handle_not_found);
  server.on("/", []() {
    handle_response(-1);
  });
  server.on("/on", []() {
    handle_response(255);
  });
  server.on("/off", []() {
    handle_response(0);
  });
  server.on("/random", []() {
    handle_response(random(0, 255));
  });
  server.begin();
}

void setup(void) {
  Serial.begin(115200);
  Serial.println("\n\n\nDemo Beginning");
  pinMode(led_pin, OUTPUT);
  
  Serial.println("Trying to connect to Wifi...");
  wifi_connect();
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(wifi_name);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  create_server();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
  analogWrite(led_pin, brightness);
}

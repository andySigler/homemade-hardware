#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

const char* ssid = "Andy-AP";

const int ledPinMag = 2;

float minX = 1000;
float maxX = -1000;
int brightness = 0;

ESP8266WebServer server(80);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

void displaySensorDetails(void) {
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void magConnect(void) {
  mag.enableAutoRange(true);
  while(!mag.begin()) {
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    delay(1000);
  }
  displaySensorDetails();
}

void wifiConnect(void) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void handleNotFound() {
  server.send(404, "text/plain", "File Not Found");
}

void createServer(void) {
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
  server.on("/", []() {
    server.send(200, "text/plain", "Color is random\n\nSensor: " + String(brightness));
  });
  server.on("/red", []() {
    server.send(200, "text/plain", "Color is red\n\nSensor: " + String(brightness));
  });
  server.on("/green", []() {
    server.send(200, "text/plain", "Color is green\n\nSensor: " + String(brightness));
  });
  server.on("/blue", []() {
    server.send(200, "text/plain", "Color is blue\n\nSensor: " + String(brightness));
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void setup(void) {
  pinMode(ledPinMag, OUTPUT);
  digitalWrite(ledPinMag, LOW);
  Serial.begin(115200);
  magConnect();
  wifiConnect();
  createServer();
}

void loop(void) {
  server.handleClient();
  MDNS.update();
  sensors_event_t event; 
  mag.getEvent(&event);
  float x = event.magnetic.x;
  if (x < minX) minX = x;
  if (x > maxX) maxX = x;
  brightness = map(x, minX, maxX, 0, 255);
  analogWrite(ledPinMag, brightness);
}

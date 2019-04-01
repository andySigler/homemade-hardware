int LED_PIN = 0;
int SENSOR_PIN = A2;

unsigned long _sine_timestamp_ms = 0;
float _ms_per_cycle = 1000.0;
float _current_sine_value = 0;
float _max_brightness = 1.0;

float leading_value = 0;
float lagging_value = 0;

void set_herts(float new_hertz) {
  _ms_per_cycle = 1000.0 / new_hertz;
}

float get_next_sine_value() {
  unsigned long _current_time_ms = millis();
  float pi_step = (float(_current_time_ms - _sine_timestamp_ms) / _ms_per_cycle) * (PI * 2.0);
  _current_sine_value += pi_step;
  while (_current_sine_value > (PI * 2)) _current_sine_value -= (PI * 2);
  _sine_timestamp_ms = _current_time_ms;
  return (sin(_current_sine_value) / 2.0) + 0.5;
}

float get_sensor_value() {
  float new_value = analogRead(SENSOR_PIN);
  leading_value += ((new_value - leading_value) / 100.0);
  lagging_value += ((leading_value - lagging_value) / 99000.0);
  float diff = leading_value - new_value;
  if (diff < 0.0) diff = 0.0;
  if (diff > 200.0) diff = 200.0;
  return (diff / 200.0);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  set_herts(1);
}

void loop() {
  float sensor_val = get_sensor_value();
  set_herts((sensor_val * 30.0) + 1);
  _max_brightness = (sensor_val * (1.0 - 0.05)) + 0.05;
  float led_intesity = get_next_sine_value();     // 0.0 - 1.0
  led_intesity = pow(led_intesity, 2);      // looks nicer
  led_intesity *= _max_brightness;             // dimmer or brighter
  analogWrite(LED_PIN, led_intesity * 255.0);  // map to 0-255
  delay(1);
}

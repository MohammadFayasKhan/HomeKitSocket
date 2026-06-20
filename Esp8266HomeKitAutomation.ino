#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "wifi_info.h"

#define LOG_D(fmt, ...) printf_P(PSTR(fmt "\n"), ##__VA_ARGS__)

void setup() {
  Serial.begin(115200);
  wifi_connect();

  // Uncomment ONLY ONCE after changing accessory structure
  // homekit_storage_reset();

  my_homekit_setup();
}

void loop() {
  my_homekit_loop();
  delay(10);
}

extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_relay1_on;
extern "C" homekit_characteristic_t cha_relay2_on;

static uint32_t next_heap_millis = 0;

#define RELAY1_PIN D2
#define RELAY2_PIN D5

void relay1_setter(const homekit_value_t value) {
  bool on = value.bool_value;
  cha_relay1_on.value.bool_value = on;

  Serial.printf("Relay 1: %s\n", on ? "ON" : "OFF");

  // Active LOW relay
  digitalWrite(RELAY1_PIN, on ? LOW : HIGH);
}

void relay2_setter(const homekit_value_t value) {
  bool on = value.bool_value;
  cha_relay2_on.value.bool_value = on;

  Serial.printf("Relay 2: %s\n", on ? "ON" : "OFF");

  // Active LOW relay
  digitalWrite(RELAY2_PIN, on ? LOW : HIGH);
}

void my_homekit_setup() {

  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);

  // Relay OFF at boot
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);

  cha_relay1_on.setter = relay1_setter;
  cha_relay2_on.setter = relay2_setter;

  arduino_homekit_setup(&config);
}

void my_homekit_loop() {

  arduino_homekit_loop();

  const uint32_t t = millis();

  if (t > next_heap_millis) {

    next_heap_millis = t + 5000;

    LOG_D("Free heap: %d, HomeKit clients: %d",
          ESP.getFreeHeap(),
          arduino_homekit_connected_clients_count());
  }
}
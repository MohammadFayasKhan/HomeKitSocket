#include <homekit/homekit.h>
#include <homekit/characteristics.h>

void my_accessory_identify(homekit_value_t _value) {
  printf("accessory identify\n");
}

homekit_characteristic_t cha_relay1_on =
    HOMEKIT_CHARACTERISTIC_(ON, false);

homekit_characteristic_t cha_relay2_on =
    HOMEKIT_CHARACTERISTIC_(ON, false);

homekit_characteristic_t cha_relay1_name =
    HOMEKIT_CHARACTERISTIC_(NAME, "Relay 1");

homekit_characteristic_t cha_relay2_name =
    HOMEKIT_CHARACTERISTIC_(NAME, "Relay 2");

homekit_accessory_t *accessories[] = {

    HOMEKIT_ACCESSORY(
        .id = 1,
        .category = homekit_accessory_category_switch,
        .services =
            (homekit_service_t *[]) {

                HOMEKIT_SERVICE(
                    ACCESSORY_INFORMATION,
                    .characteristics =
                        (homekit_characteristic_t *[]) {
                            HOMEKIT_CHARACTERISTIC(NAME, "ESP8266 Relay Controller"),
                            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "Fayas"),
                            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "12413692"),
                            HOMEKIT_CHARACTERISTIC(MODEL, "NodeMCU ESP8266"),
                            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
                            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
                            NULL}),

                HOMEKIT_SERVICE(
                    SWITCH,
                    .primary = true,
                    .characteristics =
                        (homekit_characteristic_t *[]) {
                            &cha_relay1_on,
                            &cha_relay1_name,
                            NULL}),

                HOMEKIT_SERVICE(
                    SWITCH,
                    .characteristics =
                        (homekit_characteristic_t *[]) {
                            &cha_relay2_on,
                            &cha_relay2_name,
                            NULL}),

                NULL}),

    NULL};

homekit_server_config_t config = {
    .accessories = accessories,
    .password = "111-11-111"};
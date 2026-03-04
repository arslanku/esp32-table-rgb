// ===============================================
// Настройки WiFi и MQTT (глобальные)

#define WIFI_SSID "CHAIHANA_HOUSE"
#define WIFI_PASSWORD "987123654"
#define MQTT_SERVER "mqtt.dealgate.ru"
#define MQTT_PORT 1883
#define MQTT_USER "itman7144"
#define MQTT_PASSWORD "Parol2007dg7144"

// ===============================================
// ESP32 table
#if CONTROLLER_TYPE_ESP32_TABLE

#include <WiFi.h>
#include <PubSubClient.h>
#include <FastLED.h>

// =====================
#define LED_BUILTIN 2
#define LOGGING 1

// =====================
// Настройки WiFi и MQTT

#define MQTT_CLIENT_NAME "ESP32-client-" // + ...
#define TOPIC_TO_PUBLISH "STRIP-table-1-recieved"
#define STRIP_POWER_TOPIC "STRIP-table-power"
#define STRIP_BRIGHTNESS_TOPIC "STRIP-table-brightness"
#define STRIP_MODE_TOPIC "STRIP-table-mode"
#define STRIP_SPEED "STRIP-table-speed"
#define RESTART_OTA_TOPIC "STRIP-table-1-OTA"

// =====================
// Настройки FastLED

#define NUM_LEDS 120
#define DATA_PIN 5
#define LED_TYPE WS2812
#define COLOR_ORDER GRB

#endif

// ===============================================
// ESP8266 table
#if CONTROLLER_TYPE_ESP8266_TABLE

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <FastLED.h>

// =====================
#define LED_BUILTIN D4
#define LOGGING 1

// =====================
// Настройки WiFi и MQTT

#define MQTT_CLIENT_NAME "ESP8266-client-" // + ...
#define TOPIC_TO_PUBLISH "STRIP-table-2-recieved"
#define STRIP_POWER_TOPIC "STRIP-table-power"
#define STRIP_BRIGHTNESS_TOPIC "STRIP-table-brightness"
#define STRIP_MODE_TOPIC "STRIP-table-mode"
#define RESTART_OTA_TOPIC "STRIP-table-2-OTA"

// =====================
// Настройки FastLED

#define NUM_LEDS 120
#define DATA_PIN D1
#define LED_TYPE WS2812
#define COLOR_ORDER GRB

#endif

// ===============================================
// ESP8266 window
#if CONTROLLER_TYPE_ESP8266_WINDOW

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <FastLED.h>

// =====================
#define LED_BUILTIN D4
#define LOGGING 1

// =====================
// Настройки WiFi и MQTT

#define MQTT_CLIENT_NAME "ESP8266-client-" // + ...
#define TOPIC_TO_PUBLISH "STRIP-window-recieved"
#define STRIP_POWER_TOPIC "STRIP-window-power"
#define STRIP_BRIGHTNESS_TOPIC "STRIP-window-brightness"
#define STRIP_MODE_TOPIC "STRIP-window-mode"
#define RESTART_OTA_TOPIC "STRIP-window-OTA"

// =====================
// Настройки FastLED

#define NUM_LEDS 380
#define DATA_PIN D1
#define LED_TYPE WS2812
#define COLOR_ORDER GRB

#endif

// ===============================================
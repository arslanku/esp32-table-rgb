// ===============================================
// ESP32 table
#if CONTROLLER_TYPE_ESP32_TABLE

#include <WiFi.h>
#include <PubSubClient.h>
#include <FastLED.h>

#define LED_BUILTIN 2
#define LOGGING 1

#define MQTT_CLIENT_NAME "ESP32-client-" // + ...
#define TOPIC_TO_PUBLISH "STRIP/table-1/received"
#define STRIP_POWER_TOPIC "STRIP/table/power"
#define STRIP_BRIGHTNESS_TOPIC "STRIP/table/brightness"
#define STRIP_MODE_TOPIC "STRIP/table/mode"
#define STRIP_SPEED "STRIP/table/speed"
#define RESTART_TOPIC "STRIP/table-1/restart"

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

#define LED_BUILTIN D4
#define LOGGING 1

#define MQTT_CLIENT_NAME "ESP8266-client-" // + ...
#define TOPIC_TO_PUBLISH "STRIP/table-2/received"
#define STRIP_POWER_TOPIC "STRIP/table/power"
#define STRIP_BRIGHTNESS_TOPIC "STRIP/table/brightness"
#define STRIP_MODE_TOPIC "STRIP/table/mode"
#define RESTART_TOPIC "STRIP/table-2/restart"

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

#define LED_BUILTIN D4
#define LOGGING 1

#define MQTT_CLIENT_NAME "ESP8266-client-" // + ...
#define TOPIC_TO_PUBLISH "STRIP/window/received"
#define STRIP_POWER_TOPIC "STRIP/window/power"
#define STRIP_BRIGHTNESS_TOPIC "STRIP/window/brightness"
#define STRIP_MODE_TOPIC "STRIP/window/mode"
#define RESTART_TOPIC "STRIP/window/restart"

#define NUM_LEDS 380
#define DATA_PIN D1
#define LED_TYPE WS2812
#define COLOR_ORDER GRB

#endif

// ===============================================
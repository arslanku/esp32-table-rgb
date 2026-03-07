#include <Arduino.h>

#define CONTROLLER_TYPE_ESP32_TABLE 1
#define CONTROLLER_TYPE_ESP8266_TABLE 0
#define CONTROLLER_TYPE_ESP8266_WINDOW 0

#include "auth_data.h"
#include "settings.h"

// ===============================================

WiFiClient espClient;
PubSubClient client(espClient);

CRGB leds[NUM_LEDS];
uint8_t hue = 0;

bool stripPower = true;
uint8_t stripBrightness = 50;
uint16_t discoTimerMs = 5000;

enum class stripMode
{
    RAINBOW,
    CAMPFIRE,
    RED,
    GREEN,
    BLUE,
    DISCO
};
stripMode mode;

// ===============================================
// Прототипы функций

void WIFI_connect();
void MQTT_connect();
void MQTT_callback(char *topic, byte *payload, unsigned int length);
void setStripPower(bool power);
void setStripBrightness(uint8_t brightness);
void updateStrip();
void OTA_setup();
void OTA_handle();

// ===============================================

#include "WIFI_connect.h"
#include "MQTT_connect.h"

#include "OTA_connect.h"

#include "MQTT_callback.h"

#include "strip_control.h"

// ===============================================

void setup()
{
#if LOGGING
    Serial.begin(115200);
#endif

#ifdef LED_BUILTIN
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
#endif

    WIFI_connect();
    MQTT_connect();
    OTA_setup();

#ifdef LED_BUILTIN
    digitalWrite(LED_BUILTIN, HIGH);
#endif

    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(stripBrightness);

    connectSuccess();

    mode = stripMode::RAINBOW;
    // mode = stripMode::DISCO;

#if CONTROLLER_TYPE_ESP32_TABLE
    randomSeed(esp_random());
#elif CONTROLLER_TYPE_ESP8266_TABLE
    randomSeed(analogRead(0));
#elif CONTROLLER_TYPE_ESP8266_WINDOW
    randomSeed(analogRead(0));
#endif

    Serial.println("[SYSTEM] Система запущена");
}

// ===============================================

void loop()
{
    if (!client.connected())
    {
        MQTT_connect();
    }
    if (WiFi.status() != WL_CONNECTED)
    {
        WIFI_connect();
    }

    client.loop();

    OTA_handle();

    updateStrip();

    static uint64_t led_timer;
    if (millis() - led_timer >= 500)
    {
        led_timer = millis();
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
}
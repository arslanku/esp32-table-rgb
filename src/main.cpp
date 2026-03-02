#include <Arduino.h>

#include <WiFi.h>
#include <PubSubClient.h>
#include <FastLED.h>

// ===============================================
// Настройки

#define LED_BUILTIN 2
#define LOGGING 1
#define DELAY_TIME_MS 30

// ===============================================
// Настройки WiFi и MQTT

#define WIFI_SSID "CHAIHANA_HOUSE"
#define WIFI_PASSWORD "987123654"
#define MQTT_SERVER "mqtt.dealgate.ru"
#define MQTT_PORT 1883
#define MQTT_USER "itman7144"
#define MQTT_PASSWORD "Parol2007dg7144"

#define RESTART_OTA_TOPIC "STRIP-1-OTA"

#define STRIP_POWER_TOPIC "STRIP-power"
#define STRIP_BRIGHTNESS_TOPIC "STRIP-brightness"

#define STRIP_POWER_TOPIC_TO_PUBLISH "STRIP-1-power-value"
#define STRIP_BRIGHTNESS_TOPIC_TO_PUBLISH "STRIP-1-brightness-value"

WiFiClient espClient;
PubSubClient client(espClient);

// ===============================================
// Настройки FastLED

#define NUM_LEDS 120
#define DATA_PIN 5
#define LED_TYPE WS2812
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
uint8_t hue = 0;

bool stripPower = true;       // Состояние ленты (вкл/выкл)
uint8_t stripBrightness = 50; // Яркость ленты (0-255)

enum class stripMode
{
    RAINBOW,
    CAMPFIRE,
    RED,
    GREEN,
    BLUE,
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
void OTA_setup();      // Добавляем
void OTA_handle();     // Добавляем

// ===============================================

#include "WIFI_connect.h"
#include "MQTT_connect.h"

// ===============================================

#include "OTA_connect.h"

// ===============================================

#include "MQTT_callback.h"

// ===============================================

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
    mode = stripMode::RAINBOW;

    connectSuccess();

    Serial.println("[SYSTEM] Система запущена");
}

// ===============================================

void loop()
{
    if (!client.connected())
        MQTT_connect();
    client.loop();
    
    OTA_handle();

    updateStrip();

    static uint64_t led_timer;
    if (millis() - 500 >= led_timer)
    {
        led_timer = millis();
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }

    delay(DELAY_TIME_MS);
}
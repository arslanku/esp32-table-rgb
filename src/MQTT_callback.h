// ===============================================
// Функция обработки MQTT сообщений
void MQTT_callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("[MQTT] Сообщение получено [");
    Serial.print(topic);
    Serial.print("]: ");

    String message = "";
    for (int i = 0; i < length; i++)
        message += (char)payload[i];
    Serial.println(message);

    // Обработка топиков
    if (String(topic) == STRIP_POWER_TOPIC)
    {
        if (message == "1" || message == "on" || message == "ON")
        {
            FastLED.setBrightness(0);
            setStripPower(true);

            for (int i = 0; i < stripBrightness; i++)
            {
                FastLED.setBrightness(i);
                FastLED.show();
                updateStrip();
                delay(10);
            }

            client.publish("STRIP-status", "1");
            Serial.println("[STRIP] Лента включена");
        }
        else if (message == "0" || message == "off" || message == "OFF")
        {
            for (int i = stripBrightness; i > 0; i--)
            {
                FastLED.setBrightness(i);
                FastLED.show();
                delay(10);
            }

            setStripPower(false);
            client.publish(STRIP_POWER_TOPIC_TO_PUBLISH, "0");
            Serial.println("[STRIP] Лента выключена");
        }
    }
    else if (String(topic) == STRIP_BRIGHTNESS_TOPIC)
    {
        int brightnessPercent = message.toInt();
        if (brightnessPercent >= 0 && brightnessPercent <= 100)
        {
            setStripBrightness(brightnessPercent);
            client.publish(STRIP_BRIGHTNESS_TOPIC_TO_PUBLISH, String(brightnessPercent).c_str());
            Serial.printf("[STRIP] Яркость установлена: %d%%\n", brightnessPercent);
        }
    }
    else if (String(topic) == RESTART_OTA_TOPIC)
    {
        if (message == "1")
        {
            Serial.println("[OTA] Перезагрузка по команде");
            ESP.restart();
        }
    }
}
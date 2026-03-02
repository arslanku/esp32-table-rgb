// ===============================================
// Функция подключения к MQTT
void MQTT_connect()
{
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(MQTT_callback);

    while (!client.connected())
    {
        Serial.println("[MQTT] Подключение к MQTT");
        String client_id = MQTT_CLIENT_NAME + String(WiFi.macAddress());
        Serial.printf("[MQTT] Клиент %s подключается к MQTT\n", client_id.c_str());

        if (client.connect(client_id.c_str(), MQTT_USER, MQTT_PASSWORD))
        {
            // Подписываемся на топики
            Serial.println("[MQTT] Подключено к MQTT");
            client.subscribe(STRIP_POWER_TOPIC);
            client.subscribe(STRIP_BRIGHTNESS_TOPIC);
            client.subscribe(STRIP_MODE_TOPIC);
            client.subscribe(RESTART_OTA_TOPIC);

            // client.publish(STRIP_POWER_TOPIC_TO_PUBLISH, stripPower ? "1" : "0");
            // client.publish(STRIP_BRIGHTNESS_TOPIC_TO_PUBLISH, String(stripBrightness * 100 / 255).c_str());
        }
        else
        {
            Serial.print("[ERROR] Ошибка со статусом: ");
            Serial.print(client.state());
            delay(1000);
        }
    }
}
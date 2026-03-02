// ===============================================
#include <ArduinoOTA.h>

void OTA_setup()
{
    // Настройка обработчиков событий OTA
    ArduinoOTA.onStart([]()
                       {
        String type = (ArduinoOTA.getCommand() == U_FLASH) ? "прошивка" : "файловая система";
        Serial.println("[OTA] Начинается обновление: " + type);
        
        // При начале обновления выключаем ленту, чтобы не мешала
        FastLED.clear();
        FastLED.show(); });

    ArduinoOTA.onEnd([]()
                     { Serial.println("\n[OTA] Обновление завершено"); });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                          { Serial.printf("[OTA] Прогресс: %u%%\r", (progress * 100) / total); });

    ArduinoOTA.onError([](ota_error_t error)
                       {
        Serial.printf("[OTA] Ошибка[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Ошибка аутентификации");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Ошибка начала обновления");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Ошибка подключения");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Ошибка получения");
        else if (error == OTA_END_ERROR) Serial.println("Ошибка завершения"); });

    ArduinoOTA.begin();
    Serial.println("[OTA] Сервис готов к обновлениям");
    Serial.print("[OTA] IP адрес: ");
    Serial.println(WiFi.localIP());
}

// Функция обработки OTA (должна вызываться в loop)
void OTA_handle()
{
    ArduinoOTA.handle();
}
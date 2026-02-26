// ===============================================
// Функция управления питанием ленты
void setStripPower(bool power)
{
    stripPower = power;

    if (!stripPower)
    {
        FastLED.clear();
        FastLED.show();
    }
    // Если включаем - лента автоматически обновится в loop()
}

// ===============================================
// Функция установки яркости
void setStripBrightness(uint8_t brightnessPercent)
{
    // Конвертируем проценты (0-100) в значение яркости (0-255)
    stripBrightness = map(brightnessPercent, 0, 100, 0, 255);
    FastLED.setBrightness(stripBrightness);

    // Немедленно применяем изменения
    if (stripPower)
    {
        FastLED.show();
    }
}

// ===============================================
// Функция обновления состояния ленты
void updateStrip()
{
    if (stripPower)
    {
        switch (mode)
        {
        case stripMode::RAINBOW:
            for (int i = 0; i < NUM_LEDS; i++)
            {
                leds[i] = CHSV(hue + (i * 255 / NUM_LEDS), 255, 255);
            }
            break;

        case stripMode::CAMPFIRE:
            for (int i = 0; i < NUM_LEDS; i++)
            {
                leds[i] = CHSV(hue + (i * 255 / NUM_LEDS), 255, 255);
            }
            break;

        case stripMode::RED:
            break;

        case stripMode::GREEN:
            break;

        case stripMode::BLUE:
            break;

        default:
            break;
        }

        FastLED.show();

        // if (mode == stripMode::RAINBOW)
        // {
        // }
        // else if (mode == stripMode::CAMPFIRE)
        // {
        //     // КОСТЕР
        // }
        // else if (mode == stripMode::RED)
        // {
        // }
    }
    hue++;
}

// ===============================================
// Функция подтверждения подключения контроллера

void connectSuccess()
{
    for (int i = 0; i < 3; i++)
    {
        fill_solid(leds, NUM_LEDS, CRGB::Green);
        FastLED.show();
        delay(250);

        FastLED.clear();
        FastLED.show();
        delay(250);
    }
}
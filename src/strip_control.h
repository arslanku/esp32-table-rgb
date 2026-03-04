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
    stripBrightness = map(brightnessPercent, 0, 100, 0, 255);
    FastLED.setBrightness(stripBrightness);

    if (stripPower)
    {
        FastLED.show();
    }
}

// ===============================================
// Вспомогательная функция для пульсирующей яркости на основе времени
uint8_t pulsatingBrightness(uint16_t speed = 5, uint8_t minBright = 180, uint8_t maxBright = 255)
{
    uint16_t phase = (millis() / speed) % 256; // значение от 0 до 255
    uint8_t sinVal = sin8(phase);              // 0..255 по синусу
    return map(sinVal, 0, 255, minBright, maxBright);
}

// ===============================================
// Функция обновления состояния ленты
void updateStrip()
{
    static uint64_t timer = 0;
    
    if (!stripPower)
    {
        return;
    }
    switch (mode)
    {
    // Эффект РАДУГИ
    case stripMode::RAINBOW:
    {
        if (millis() - timer >= 30)
        {
            timer = millis();
            hue++;
        }
        for (int i = 0; i < NUM_LEDS; i++)
        {
            leds[i] = CHSV(hue + (i * 255 / NUM_LEDS), 255, 255);
        }
        break;
    }

    // Эффект КОСТРА
    case stripMode::CAMPFIRE:
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            // База оттенка — красный/оранжевый (HUE от 0 до 40)
            // Добавляем небольшую зависимость от позиции для разнообразия
            uint8_t baseHue = 16 + (i * 3) % 32;

            // Случайное изменение оттенка от -8 до +8
            int8_t hueVar = (random8(17) - 8); // random8(17) даёт 0..16, вычитаем 8 -> -8..8
            uint8_t finalHue = baseHue + hueVar;

            // Яркость также случайная, но в высоком диапазоне (180..255)
            uint8_t bright = 180 + random8(76); // 180..255

            leds[i] = CHSV(finalHue, 255, bright);
        }
        // Небольшое смещение базы для изменения характера огня со временем (опционально)
        // campfireHueOffset += 1;  // можно добавить, если хотите медленное изменение палитры
        break;
    }

    /*
    // КРАСНЫЙ
    case stripMode::RED:
    {
        // uint8_t bright = pulsatingBrightness(5, 200, 255); // скорость 5, яркость 200-255
        // uint8_t hueShift = sin8(millis() / 7) / 4;         // изменение оттенка 0..63
        // fill_solid(leds, NUM_LEDS, CHSV(0 + hueShift, 255, bright));
        if (millis() - timer >= 50)
        {
            timer = millis();
            hue++;
        }
        for (int i = 0; i < NUM_LEDS; i++)
        {
            float hue_float = 35 + sin(hue) * 5; // 20 - 35 - 50
            leds[i] = CHSV((int)hue_float + (i * 255 / NUM_LEDS), 255, 255);
        }
        break;
    }

    // ЗЕЛЕНЫЙ
    case stripMode::GREEN:
    {
        // uint8_t bright = pulsatingBrightness(5, 200, 255);
        // uint8_t hueShift = sin8(millis() / 7) / 6; // изменение оттенка 0..42
        // fill_solid(leds, NUM_LEDS, CHSV(96 + hueShift, 255, bright));
        if (millis() - timer >= 50)
        {
            timer = millis();
            hue++;
        }
        for (int i = 0; i < NUM_LEDS; i++)
        {
            float hue_float = 150 + sin(hue) * 5; // 135 - 150 - 165
            leds[i] = CHSV((int)hue_float + (i * 255 / NUM_LEDS), 255, 255);
        }
        break;
    }

    // СИНИЙ
    case stripMode::BLUE:
    {
        // uint8_t bright = pulsatingBrightness(5, 200, 255);
        // uint8_t hueShift = sin8(millis() / 7) / 6; // изменение оттенка 0..42
        // fill_solid(leds, NUM_LEDS, CHSV(160 + hueShift, 255, bright));
        if (millis() - timer >= 50)
        {
            timer = millis();
            hue++;
        }
        for (int i = 0; i < NUM_LEDS; i++)
        {
            float hue_float = 260 + sin(hue) * 5; // 245 - 260 - 275
            leds[i] = CHSV((int)hue_float + (i * 255 / NUM_LEDS), 255, 255);
        }
        break;
    }
    */

    // Продвинутая дискотека с автоматической сменой эффектов
    case stripMode::DISCO:
    {
        static uint16_t discoEffect = 0;
        static uint8_t discoHue = 0;
        static uint8_t offset = 0;

        static uint64_t effectChange_timer = 0;
        if (millis() - effectChange_timer > discoTimerMs)
        {
            effectChange_timer = millis();
            discoEffect = (discoEffect + 1) % 3;
        }
        switch (discoEffect)
        {
        // Быстре радужные вспышки
        case 0:
            if (millis() % 300 < 150)
            {
                fill_solid(leds, NUM_LEDS, CHSV(discoHue, 255, 255));
            }
            else
            {
                discoHue++;
                FastLED.clear();
            }
            break;

        // Быстрая радуга
        case 1:
            for (int i = 0; i < NUM_LEDS; i++)
            {
                leds[i] = CHSV(hue + (i * 255 / NUM_LEDS), 255, 255);
            }
            hue++;
            break;

        // Бегущие огни
        case 2:
            if (millis() % 100 < 50)
            {
                for (int i = 0; i < NUM_LEDS; i++)
                {
                    leds[i] = CHSV((i * 15 + offset) % 255, 255, 255);
                }
                offset++;
            }
            else
            {
                FastLED.clear();
            }
            break;

        default:
            break;
        }
    }

    default:
        break;
    }

    FastLED.show();
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
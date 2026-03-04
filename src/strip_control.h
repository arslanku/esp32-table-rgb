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
    if (!stripPower)
        return;

    switch (mode)
    {
    // Эффект РАДУГИ
    case stripMode::RAINBOW:
    {
        static uint64_t rainbowTimer = 0;
        if (millis() - rainbowTimer >= 30)
        {
            rainbowTimer = millis();
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
            uint8_t baseHue = 16 + (i * 3) % 32;
            int8_t hueVar = (random8(17) - 8);
            uint8_t finalHue = baseHue + hueVar;
            uint8_t bright = 180 + random8(76);
            leds[i] = CHSV(finalHue, 255, bright);
        }
        break;
    }

    // Продвинутая дискотека с автоматической сменой эффектов
    case stripMode::DISCO:
    {
        static uint8_t discoEffect = 0;
        static uint8_t discoHue = 0;
        static uint8_t offset = 0;
        static uint64_t effectChangeTimer = 0;

        if (millis() - effectChangeTimer >= discoTimerMs)
        {
            effectChangeTimer = millis();
            discoEffect = (discoEffect + 1) % 6;
        }

        // Вспомогательная функция для плавной смены цвета (используется в эффекте 5)
        auto pulseColor = [&](uint8_t baseHue) -> CRGB
        {
            uint8_t bright = pulsatingBrightness(5, 100, 255); // пульсация яркости
            return CHSV(baseHue + (millis() / 20) % 32, 255, bright);
        };

        switch (discoEffect)
        {
        // 0: Быстрые радужные вспышки
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

        // 1: Быстрая радуга (вперёд)
        case 1:
            for (int i = 0; i < NUM_LEDS; i++)
            {
                leds[i] = CHSV(hue + (i * 255 / NUM_LEDS), 255, 255);
            }
            hue++;
            break;

        // 2: Бегущие огни
        case 2:
            if (millis() % 200 < 100)
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

        // 3: Быстрая радуга (в другую сторону)
        case 3:
            for (int i = 0; i < NUM_LEDS; i++)
            {
                leds[i] = CHSV(hue + (i * 255 / NUM_LEDS), 255, 255);
            }
            hue--;
            break;

        // 4: Случайные цветные сектора
        case 4:
        {
            static uint64_t lastSectorUpdate = 0;
            if (millis() - lastSectorUpdate >= 450)
            {
                lastSectorUpdate = millis();
                int sector = NUM_LEDS / 5; // делим ленту на 5 примерно равных частей
                for (int part = 0; part < 5; part++)
                {
                    int start = part * sector;
                    int end = (part == 4) ? NUM_LEDS : (part + 1) * sector; // последний сектор до конца
                    fill_solid(leds + start, end - start, CHSV(random(255), 255, 255));
                }
            }
            break;
        }

        // 5: Пульсирующая волна цвета
        case 5:
        {
            uint8_t bright = pulsatingBrightness(20, 20, 200);
            uint8_t hueVal = (millis() / 10) % 255;
            fill_solid(leds, NUM_LEDS, CHSV(hueVal, 255, bright));
            break;
        }
        }
        break;
    }
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
/**
 * Test for XIAO built-in LED and SK6812MINI LEDs
 */

#include <Adafruit_NeoPixel.h>
#include <Adafruit_TinyUSB.h>

#include "dya-xiao-nrf52840-plus.h"

#define NUM_LEDS 8  // 4 for left, 8 for right
Adafruit_NeoPixel dya_pixels(NUM_LEDS, DYA_PIN_LED);

void setup() {
    pinMode(DYA_PIN_LED_EN, OUTPUT);
    digitalWrite(DYA_PIN_LED_EN, LOW);  // enabled
    pinMode(DYA_PIN_LED, OUTPUT);
    dya_pixels.begin();
    Serial.begin(38400);
}

uint8_t cnt = 0;
uint8_t cap_to_uint8(uint32_t value) { return value > 0xFF ? 0xFF : value; }
uint32_t calc_rgb(uint8_t counter) {
    uint32_t red   = 0;
    uint32_t green = 0;
    uint32_t blue  = 0;

    // change color based on upper 2bit
    switch (counter >> 6) {
        case 0:
            red = 255;
            break;
        case 1:
            green = 255;
            break;
        case 2:
            blue = 255;
            break;
        case 3:
            red   = 255;
            green = 255;
            blue  = 255;
            break;
    }

    // change brightness based on lower 6bit
    uint32_t brightness = counter & 0x3F;  // 00111111
    red                 = (red * brightness) >> 6;
    green               = (green * brightness) >> 6;
    blue                = (blue * brightness) >> 6;

    return Adafruit_NeoPixel::Color(cap_to_uint8(red), cap_to_uint8(green),
                                    cap_to_uint8(blue));
}

void loop() {
    for (int i = 0; i < NUM_LEDS; i++) {
        dya_pixels.setPixelColor(i, calc_rgb(cnt + i * 20));
    }
    dya_pixels.show();

    delay(50);
    cnt++;

    // XIAO's built-in LED
    digitalWrite(LED_RED, cnt % 3 == 0 ? 1 : 0);
    digitalWrite(LED_GREEN, cnt % 3 == 1 ? 1 : 0);
    digitalWrite(LED_BLUE, cnt % 3 == 2 ? 1 : 0);
}
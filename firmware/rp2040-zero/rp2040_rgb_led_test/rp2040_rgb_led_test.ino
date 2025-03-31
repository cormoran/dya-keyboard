#include <Adafruit_NeoPixel.h>

// LED in PR2040-zero board
#define ZERO_LED_PIN 16
// LED in dya keyboard
#define KBD_LED_PIN 15

Adafruit_NeoPixel zero_pixels(1, ZERO_LED_PIN);
Adafruit_NeoPixel dya_pixels(4, KBD_LED_PIN);

uint8_t cnt = 0;

void setup() {
    pinMode(26, OUTPUT);
    digitalWrite(26, LOW);  // enable LED
    zero_pixels.begin();
    dya_pixels.begin();
}

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
    zero_pixels.setPixelColor(0, calc_rgb(cnt));
    zero_pixels.show();
    for (int i = 0; i < 4; i++) {
        dya_pixels.setPixelColor(i, calc_rgb(cnt + i * 20));
    }
    dya_pixels.show();

    delay(50);
    cnt++;
}
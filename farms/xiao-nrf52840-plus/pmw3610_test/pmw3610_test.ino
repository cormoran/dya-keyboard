#include <Adafruit_TinyUSB.h>

#include "dya-xiao-nrf52840-plus.h"
#include "pmw3610.h"

#define BIT(i) (1 << i)
#define TOINT16(val, bits) (((struct { int16_t value : bits; }){val}).value)

static uint8_t reg_read(uint8_t reg_address) {
    pinMode(DYA_PIN_SDIO, OUTPUT);
    for (int8_t i = 7; i >= 0; i--) {
        digitalWrite(DYA_PIN_SCLK, 0);
        digitalWrite(DYA_PIN_SDIO, reg_address & BIT(i));
        delayMicroseconds(1);
        digitalWrite(DYA_PIN_SCLK, 1);
        delayMicroseconds(1);
    }
    pinMode(DYA_PIN_SDIO, INPUT);
    delayMicroseconds(T_SRAD);
    uint8_t r = 0;
    for (int8_t i = 7; i >= 0; i--) {
        digitalWrite(DYA_PIN_SCLK, 0);
        delayMicroseconds(1);
        digitalWrite(DYA_PIN_SCLK, 1);
        delayMicroseconds(1);
        r |= digitalRead(DYA_PIN_SDIO) << i;
    }
    delayMicroseconds(10);
    return r;
}

void _reg_write(uint8_t reg_address, uint8_t data) {
    reg_address |= PMW3610_WRITE_BIT;

    pinMode(DYA_PIN_SDIO, OUTPUT);
    for (int8_t i = 7; i >= 0; i--) {
        digitalWrite(DYA_PIN_SCLK, 0);
        digitalWrite(DYA_PIN_SDIO, reg_address & BIT(i));
        delayMicroseconds(1);
        digitalWrite(DYA_PIN_SCLK, 1);
        delayMicroseconds(1);
    }
    for (int8_t i = 7; i >= 0; i--) {
        digitalWrite(DYA_PIN_SCLK, 0);
        digitalWrite(DYA_PIN_SDIO, data & BIT(i));
        delayMicroseconds(1);
        digitalWrite(DYA_PIN_SCLK, 1);
        delayMicroseconds(1);
    }
    delayMicroseconds(T_SCLK_NCS_WR);
    delayMicroseconds(T_SWX);
}

void reg_write(uint8_t reg_address, uint8_t data) {
    _reg_write(PMW3610_REG_SPI_CLK_ON_REQ, PMW3610_SPI_CLOCK_CMD_ENABLE);
    _reg_write(reg_address, data);
    _reg_write(PMW3610_REG_SPI_CLK_ON_REQ, PMW3610_SPI_CLOCK_CMD_DISABLE);
}

void set_cpi(uint32_t cpi) {
    uint8_t value = cpi / 200;
    reg_write(PMW3610_REG_SPI_PAGE0, 0xFF);
    reg_write(PMW3610_REG_RES_STEP, value);
    reg_write(PMW3610_REG_SPI_PAGE1, 0x00);
}

void setup() {
    Serial.begin(38400);
    pinMode(DYA_PIN_SCLK, OUTPUT);
    pinMode(DYA_PIN_SDIO, OUTPUT);
    pinMode(DYA_PIN_MOTION, INPUT);

    delay(1000);
    init_pmw3610();
}

void init_pmw3610() {
    Serial.println("Initializing PMW3610");
    reg_write(PMW3610_REG_POWER_UP_RESET, PMW3610_POWERUP_CMD_RESET);

    delay(50);
    reg_write(PMW3610_REG_OBSERVATION, 0x00);

    delay(10);
    uint8_t obs = reg_read(PMW3610_REG_OBSERVATION);
    if ((obs & 0x0F) != 0x0F) {
        Serial.println("observation is wrong");
    }
    for (int i = 0; i < 10; i++) {
        Serial.write("* Product Id = ");
        Serial.println(reg_read(PMW3610_REG_PRODUCT_ID));
        Serial.write("* Revision Id = ");
        Serial.println(reg_read(PMW3610_REG_REVISION_ID));
    }

    reg_write(PMW3610_REG_PERFORMANCE,
              0x0d);  // normal operation, 4ms, 4ms, 4ms
    // Time after which sensor goes from RUN to REST1 mode.
    reg_write(PMW3610_REG_RUN_DOWNSHIFT,
              0x04);  // 128ms (unit: pos-rate (4ms) * 8 = 32ms)
    reg_write(PMW3610_REG_REST1_PERIOD, 0x04);  // 40ms (unit: 10ms)
    reg_write(PMW3610_REG_REST1_DOWNSHIFT,
              0x0f);  // (unit: 16 * Rest1_sample_period (above, 40ms))

    set_cpi(200);

    delay(50);

    reg_read(PMW3610_REG_MOTION);
    reg_read(PMW3610_REG_DELTA_X_L);
    reg_read(PMW3610_REG_DELTA_Y_L);
    reg_read(PMW3610_REG_DELTA_XY_H);
}

void loop() {
    if (Serial.available()) {
        String s = Serial.readString();
        if (s.startsWith("reset")) {
            init_pmw3610();
        }
    }
    uint8_t motion = reg_read(PMW3610_REG_MOTION);
    if (motion & BIT(7)) {
        // raw value
        if (false) {
            Serial.write("Motion = ");
            Serial.println(motion);
            Serial.write("delta_x = ");
            Serial.println(reg_read(PMW3610_REG_DELTA_X_L));
            Serial.write("delta_y = ");
            Serial.println(reg_read(PMW3610_REG_DELTA_Y_L));
            Serial.write("delta_xy = ");
            Serial.println(reg_read(PMW3610_REG_DELTA_XY_H));
        }
        // parsed value
        if (true) {
            uint8_t xl  = reg_read(PMW3610_REG_DELTA_X_L);
            uint8_t yl  = reg_read(PMW3610_REG_DELTA_Y_L);
            uint8_t xyh = reg_read(PMW3610_REG_DELTA_XY_H);
            int16_t x   = TOINT16(xl + ((xyh & 0xF0) << 4), 12);
            int16_t y   = TOINT16(yl + ((xyh & 0x0F) << 8), 12);
            Serial.printf("x = %d y = %d\n", x, y);
        }
    } else {
        Serial.write(".");
    }
    delay(100);
}
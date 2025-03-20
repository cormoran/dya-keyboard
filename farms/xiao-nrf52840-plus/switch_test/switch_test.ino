/**
 * Test for switch matrix scan
 */

#include <Adafruit_TinyUSB.h>

#include "dya-xiao-nrf52840-plus.h"

// Please comment-in to test left side.
// Note that testing right/left device with opposite setting is safe.
// #define DYA_LEFT

#ifdef DYA_LEFT

const uint8_t ROW_INPUTS[]  = {DYA_PIN_RL0, DYA_PIN_RL1, DYA_PIN_RL2,
                               DYA_PIN_RL3, DYA_PIN_RL4};
const uint8_t COL_OUTPUTS[] = {DYA_PIN_CL0, DYA_PIN_CL1, DYA_PIN_CL2,
                               DYA_PIN_CL3, DYA_PIN_CL4, DYA_PIN_CL5,
                               DYA_PIN_CL6};
const String ROW_NAMES[]    = {"R0", "R1", "R2", "R3", "R4"};
const String COL_NAMES[]    = {"C0", "C1", "C2", "C3", "C4", "C5", "C6"};

#else  // right

const uint8_t ROW_INPUTS[]  = {DYA_PIN_RR0, DYA_PIN_RR1, DYA_PIN_RR2,
                               DYA_PIN_RR3, DYA_PIN_RR4, DYA_PIN_RR5};
const uint8_t COL_OUTPUTS[] = {DYA_PIN_CR7,  DYA_PIN_CR8,  DYA_PIN_CR9,
                               DYA_PIN_CR10, DYA_PIN_CR11, DYA_PIN_CR12,
                               DYA_PIN_CR13};
const String ROW_NAMES[]    = {"R0", "R1", "R2", "R3", "R4", "R5"};
const String COL_NAMES[]    = {"C7", "C8", "C9", "C10", "C11", "C12", "C13"};

#endif

const uint8_t NUM_ROWS = sizeof(ROW_INPUTS) / sizeof(ROW_INPUTS[0]);
const uint8_t NUM_COLS = sizeof(COL_OUTPUTS) / sizeof(COL_OUTPUTS[0]);

bool key_states[NUM_COLS][NUM_ROWS]      = {};
bool last_key_states[NUM_COLS][NUM_ROWS] = {};

unsigned long num_scans  = 0;
unsigned long start_time = 0;

void setup() {
    // configure NFC1,2 as GPIO
    if ((NRF_UICR->NFCPINS & UICR_NFCPINS_PROTECT_Msk) ==
        (UICR_NFCPINS_PROTECT_NFC << UICR_NFCPINS_PROTECT_Pos)) {
        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy) {
        }
        NRF_UICR->NFCPINS &= ~UICR_NFCPINS_PROTECT_Msk;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy) {
        }
        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy) {
        }
        NVIC_SystemReset();
    }
    pinMode(DYA_PIN_LED_EN, OUTPUT);
    digitalWrite(DYA_PIN_LED_EN, LOW);  // enabled
    pinMode(DYA_PIN_LED, OUTPUT);
    // setup switch GPIOs
    for (uint8_t row : ROW_INPUTS) {
        pinMode(row, INPUT_PULLDOWN);
    }
    for (uint8_t col : COL_OUTPUTS) {
        pinMode(col, OUTPUT);
    }
    Serial.begin(38400);
    start_time = millis();
}

void loop() {
    // scan
    for (uint8_t c = 0; c < NUM_COLS; c++) {
        digitalWrite(COL_OUTPUTS[c], HIGH);
        for (uint8_t r = 0; r < NUM_ROWS; r++) {
            key_states[c][r] = digitalRead(ROW_INPUTS[r]);
        }
        digitalWrite(COL_OUTPUTS[c], LOW);
    }
    // print
    for (uint8_t c = 0; c < NUM_COLS; c++) {
        for (uint8_t r = 0; r < NUM_ROWS; r++) {
            if (key_states[c][r] != last_key_states[c][r]) {
                Serial.print("Key ");
                Serial.print(ROW_NAMES[r]);
                Serial.print(COL_NAMES[c]);
                Serial.print(" ");
                Serial.println(key_states[c][r] ? "pressed" : "released");
                last_key_states[c][r] = key_states[c][r];
            }
        }
    }
    // speed
    num_scans++;
    if (millis() - start_time > 1000) {
        unsigned long duration = millis() - start_time;
        Serial.print(num_scans);
        Serial.print(" scan/sec (");
        Serial.print(((double)duration) / ((double)num_scans));
        Serial.println(" ms) in avg");
        num_scans  = 0;
        start_time = millis();
    }
}
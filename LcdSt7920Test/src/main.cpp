#include <Arduino.h>

#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>


// RS : CHIP SELECT
#define RS 10
// RW : DATA MOSI
#define RW 11
// E : CLOCK
#define E 13


U8G2_ST7920_128X64_1_SW_SPI lcd(U8G2_R0, E, RW, RS);
void setup() {
    // put your setup code here, to run once:
}

void loop() {
    // put your main code here, to run repeatedly:
}

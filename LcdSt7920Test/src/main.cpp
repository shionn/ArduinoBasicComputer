#include <Arduino.h>

#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>


// CS ou SS ou CHIP SELECT : RS
#define CS 10
// DATA ou MOSI : R/W
#define DATA 11
// CLOCK, E
#define CLOCK 13


//U8G2_ST7920_128X64_1_8080 lcd(U8G2_R0, 2, 3, 4, 5, 6, 7, 8, 9, 10, U8X8_PIN_NONE, 12);
//U8G2_ST7920_128X64_F_SW_SPI lcd(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* CS=*/ 10, /* reset=*/ 8);
U8G2_ST7920_128X64_F_HW_SPI lcd(U8G2_R0, CS);

void setup() {
  lcd.begin();
}

void loop() {
  //lcd.clear();
//  lcd.firstPage();
//  do {
//   lcd.setFont(u8g2_font_ncenB12_tr);
//   lcd.drawStr(5,15,"Hello World !");
//   lcd.drawBox(5, 17, 118, 2);
// } while ( lcd.nextPage() );

lcd.clearBuffer();
lcd.setFont(u8g2_font_ncenB14_tr);
lcd.drawStr(0,20,"Hello World!");
   lcd.drawBox(5, 23, 118, 2);
lcd.sendBuffer();

 delay(1000);
}

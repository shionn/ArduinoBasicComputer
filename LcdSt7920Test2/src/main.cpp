#include <Arduino.h>

#define __SPI__ 1

#ifdef __SPI__
#include <SPI.h>
#endif

// CS ou SS ou CHIP SELECT : RS
#define CS 10
// DATA ou MOSI : R/W
#define DATA 11
// CLOCK, E
#define CLOCK 13

#define DELAI 1


void clock() {
  digitalWrite(CLOCK, HIGH);
  digitalWrite(CLOCK, LOW);
}

void writeWord(uint8_t data) {
  #ifdef __SPI__
  SPI.transfer(data);
  #else
  for (int i=0; i<8; i++) {
    digitalWrite(DATA, (data & 0b10000000) != 0 );
    clock();
    data = (uint8_t)(data << 1);
  }
  #endif
}


void write(uint8_t data) {
  #ifdef __SPI__
  SPI.transfer(data & 0b11110000);
  SPI.transfer((uint8_t)(data << 4));
  #else
  writeWord(data & 0b11110000);
  writeWord((uint8_t)(data << 4));
  #endif
}

#ifdef __SPI__
SPISettings setting = SPISettings(1000000, MSBFIRST, SPI_MODE3);
#endif


void setup() {
  Serial.begin(9600);

  pinMode(CS,    OUTPUT);
  pinMode(DATA,  OUTPUT);
  pinMode(CLOCK, OUTPUT);

  //delay(100);
  digitalWrite(CS, HIGH);
  //delay(10);
  #ifdef __SPI__
  SPI.begin();
  SPI.beginTransaction(setting);
  #endif
  writeWord(0b11111000); // synchro 11111 RW RS 0
  write(0b00000001); // clear
  delay(2);
  write(0b00001100); // display on, no cursor no blink
  delayMicroseconds(DELAI);
  write(0b00110100); // 8bit extend
  delayMicroseconds(DELAI);
  write(0b00110110); // 8bit extend mode graphic
  delayMicroseconds(DELAI);

  #ifdef __SPI__
  SPI.endTransaction();
  #endif
  digitalWrite(CS, LOW);
  delayMicroseconds(DELAI);
}

void locate(int y){
  digitalWrite(CS, HIGH);
  #ifdef __SPI__
  SPI.beginTransaction(setting);
  #endif
  writeWord(0b11111000); // synchro 11111 RW RS 0
  write(0b10000000+y);
  write(0b10000000); // x=0
  #ifdef __SPI__
  SPI.endTransaction();
  #endif
  digitalWrite(CS, LOW);
  delayMicroseconds(DELAI);
}

int y=0;
void loop() {

  locate(y);
  y++;
  if (y==32) y=0;

  digitalWrite(CS, HIGH);
  #ifdef __SPI__
  SPI.beginTransaction(setting);
  #endif
  writeWord(0b11111010); // synchro 11111 RW RS 0
  for (int x=0;x<32;x++)
    write(0b00110011);
  #ifdef __SPI__
  SPI.endTransaction();
  #endif
  digitalWrite(CS, LOW);
  delayMicroseconds(DELAI);

  //delay(1000);

}

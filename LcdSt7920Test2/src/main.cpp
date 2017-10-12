#include <Arduino.h>
#include <SPI.h>

// CS ou SS ou CHIP SELECT : RS
#define CS 10
// DATA ou MOSI : R/W
#define DATA 11
// CLOCK, E
#define CLOCK 13

void write(uint8_t data) {
  Serial.print(data , BIN);
  Serial.print(' ');
  Serial.print(data & 0b11110000, BIN);
  Serial.print(' ');
  Serial.println((uint8_t)(data << 4), BIN);

  SPI.transfer(data & 0b11110000);
  SPI.transfer((uint8_t)(data << 4));
}

void setup() {
  Serial.begin(9600);

  pinMode(CS, OUTPUT);
  digitalWrite(CS, LOW);
  SPI.begin();
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
  SPI.transfer(0b11111000); // synchro 11111 RW RS 0
  write(0b00110010); // function set (8 bit
  write(0b00110110); // function set (extend instr. set
  write(0b00110110); // function set (grafika ON
  write(0b00000010); // enable CGRAM po prenastaveni do BASIC instr
//  SPI.endTransaction();
//  SPI.end();
  digitalWrite(CS, HIGH);

  delay(100);

  digitalWrite(CS, LOW);
  SPI.transfer(0b11111000); // synchro 11111 RW RS 0
  write(0b10000001); // y=0
  write(0b10000001); // x=0
  digitalWrite(CS, HIGH);
  delay(5000);
}

void loop() {


  digitalWrite(CS, LOW);
  SPI.transfer(0b11111010); // synchro 11111 RW RS 0
  write(0b11001111);
  write(0b11110011);
  write(0b11111100);
  write(0b11010101);
  digitalWrite(CS, HIGH);
  delay(5000);


}

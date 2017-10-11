#include <Arduino.h>
#include <SPI.h>

#define CS 10

void setup() {
  pinMode(CS, OUTPUT);
  SPI.begin();

  SPI.transfer(0b00110010);
  SPI.transfer(0b00110110);
  SPI.transfer(0b00110110);
  SPI.transfer(0b00000010);
}

void loop() {
    // put your main code here, to run repeatedly:
}

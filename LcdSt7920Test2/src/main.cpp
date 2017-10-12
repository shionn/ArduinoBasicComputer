#include <Arduino.h>

#ifdef __SPI__
#include <SPI.h>
#endif

// CS ou SS ou CHIP SELECT : RS
#define CS 10
// DATA ou MOSI : R/W
#define DATA 11
// CLOCK, E
#define CLOCK 13

#define DELAI 100000

void clock() {
  digitalWrite(CLOCK, HIGH);
  delayMicroseconds(DELAI);
  digitalWrite(CLOCK, LOW);
  delayMicroseconds(DELAI);
}

void writeWord(uint8_t data) {
  for (int i=0; i<8; i++) {
    digitalWrite(DATA, (data & 0b10000000) != 0 );
    delayMicroseconds(DELAI);
    clock();
    data = (uint8_t)(data << 1);
  }
}


void write(uint8_t data) {
  Serial.print(data , BIN);
  Serial.print(' ');
  Serial.print(data & 0b11110000, BIN);
  Serial.print(' ');
  Serial.println((uint8_t)(data << 4), BIN);

  #ifdef __SPI__
  SPI.transfer(data & 0b11110000);
  SPI.transfer((uint8_t)(data << 4));
  #else
  writeWord(data & 0b11110000);
  writeWord((uint8_t)(data << 4));
  #endif
}

#ifdef __SPI__
SPISettings setting = SPISettings(1, MSBFIRST, SPI_MODE2);
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

  write(0b00110010); // function set (8 bit
  write(0b00110110); // function set (extend instr. set
  write(0b00110110); // function set (grafika ON
  write(0b00000010); // enable CGRAM po prenastaveni do BASIC instr
  #ifdef __SPI__
  SPI.endTransaction();
  #endif
//  SPI.end();
  digitalWrite(CS, LOW);

  delay(100);

  digitalWrite(CS, HIGH);
  #ifdef __SPI__
  SPI.beginTransaction(setting);
  #endif
  writeWord(0b11111000); // synchro 11111 RW RS 0
  write(0b10000000+2); // y=0
  write(0b10000000+4); // x=0
  #ifdef __SPI__
  SPI.endTransaction();
  #endif
  digitalWrite(CS, LOW);
  delay(1000);
}

void loop() {


  digitalWrite(CS, HIGH);
  #ifdef __SPI__
  SPI.beginTransaction(setting);
  #endif
  writeWord(0b11111010); // synchro 11111 RW RS 0
  write(0b10101010);
  write(0b10101010);
  #ifdef __SPI__
  SPI.endTransaction();
  #endif
  digitalWrite(CS, LOW);
  delay(1000);


}

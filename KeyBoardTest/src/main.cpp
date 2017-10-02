#include <Arduino.h>

#include <Chatpad.h>

Chatpad pad;

void print_keys(Chatpad &pad, Chatpad::keycode_t code, Chatpad::eventtype_t type) {
	if (type == Chatpad::Down) {
		char a = pad.toAscii(code);
		if (a != 0) Serial.print(a);
	}
}

void setup() {
	Serial.begin(19200);
	pad.init(Serial, print_keys);
	Serial.println("start");
}

void loop() {
	pad.poll();
//	Serial.println("merde");
}

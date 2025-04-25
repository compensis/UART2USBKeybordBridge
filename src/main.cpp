
#include <Arduino.h>

#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const char ASCII_DEL_CHAR = 0x7F;

class DelayedKeyboard: public BootKeyboard_ {
public:
	template <typename T>
	size_t tap(T k)
	{
		// Press and release key (if press was successfull)
		auto ret = press(k);
		// Wait for the key to be sent
		delay(10);
		if(ret){
			release(k);
		}
		return ret;
	}
};

DelayedKeyboard USBKeyboard;

void setup() {
	// Sends a clean report to the host. This is important on any Arduino type.
	USBKeyboard.begin();
	
	// Open the hardware UART port
	Serial1.begin(115200);
}

void loop() {
	// Light led if keyboard uses the boot protocol (normally while in bios)
	// Keep in mind that on a 16u2 and Arduino Micro HIGH and LOW for TX/RX Leds are inverted.
	if (USBKeyboard.getProtocol() == HID_BOOT_PROTOCOL) {
		digitalWrite(pinLed, HIGH);
	} else {
		digitalWrite(pinLed, LOW);
	}

	// Check for incoming serial data
	if (Serial1.available() > 0) {
		// read incoming serial data
		char inChar = Serial1.read(); 

		if (inChar == '\r') {
			USBKeyboard.tap(KEY_ENTER);
		} else if (inChar == ASCII_DEL_CHAR) {
			USBKeyboard.tap(KEY_BACKSPACE);
		} else {
		// Type the received character
			USBKeyboard.tap(inChar);
		}

		// Indicate that the character was sent
		Serial1.write('*');
	}
}
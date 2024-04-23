#include <Arduino.h>
#include <Wire.h>
#include <base.h>

Base base;

void setup() {
	base = Base();
}

void loop() {
	// Read the up time from the controller and send it to
	// the serial monitor.
	// uint16_t upTime = base.readUpTime();
	// Serial.print(F("Up time: "));
	// Serial.println(upTime);

	// base.setMotorSpeed(3200);  // full-speed forward
    pinMode(13, 1);
	delay(1000);
	// base.setMotorSpeed(-3200);	// full-speed reverse
    pinMode(13, 0);
	delay(1000);


}

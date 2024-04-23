#include <Arduino.h>
#include <Wire.h>
#include <base.h>

Base::Base() {
	Base::smcDeviceNumber = 15;
    Base::speedModifer = 0.5;
	Wire.begin();
	Base::exitSafeStart();
}

void Base::exitSafeStart() {
	Wire.beginTransmission(Base::smcDeviceNumber);
	Wire.write(0x83);  // Exit safe start
	Wire.endTransmission();
}

void Base::setMotorSpeed(int16_t speed) {
    speed *= speedModifer;
	uint8_t cmd = 0x85;	 // Motor forward
	if (speed < 0) {
		cmd = 0x86;	 // Motor reverse
		speed = -speed;
	}
	Wire.beginTransmission(Base::smcDeviceNumber);
	Wire.write(cmd);
	Wire.write(speed & 0x1F);
	Wire.write(speed >> 5 & 0x7F);
	Wire.endTransmission();
}

// uint16_t Base::currentUpTime() {
// 	Wire.beginTransmission(smcDeviceNumber);
// 	Wire.write(0xA1);  // Command: Get variable
// 	Wire.write(28);	   // Variable ID: Up time (low)
// 	Wire.endTransmission();
// 	Wire.requestFrom(smcDeviceNumber, (uint8_t)2);
// 	uint16_t upTime = Wire.read();
// 	upTime |= Wire.read() << 8;
// 	return upTime;
// }

#include <Wire.h>

class Base {
   public:
	Base();

	void exitSafeStart();
	void setMotorSpeed(int16_t);
	// uint16_t currentUpTime();

   private:
	uint8_t smcDeviceNumber;
    float_t speedModifer;
};

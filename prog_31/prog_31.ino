#include <Servo.h>

const byte pinPot = A5;
const byte pinServo = 3;

int valPot;
int angleServo;
Servo servo;

int calcServoAngle() {
	return (int)((123120.0 - 180.0 * valPot) / 674.0);
}

void setup() {
	Serial.begin(9600);
	pinMode(pinPot, INPUT);
	servo.attach(pinServo);
}

void loop() {
	valPot = analogRead(pinPot);
	angleServo = calcServoAngle();
	if (angleServo > 180) {
		angleServo = 180;
	} else if (angleServo < 0) {
		angleServo = 0;
	}
	servo.write(angleServo);
	delay(200);
}

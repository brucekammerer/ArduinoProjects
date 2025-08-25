#include <Stepper.h>

const int stepsPerRevolution = 2048;
const int motorSpeed = 10; // rpm
Stepper stepper(stepsPerRevolution, 8, 10, 9, 11);
int motorSteps = 1;
int motorDirection = 1;

const byte pinButton = 2;
boolean wasButtonPressed = false;

void setup() {
	stepper.setSpeed(motorSpeed);
	pinMode(pinButton, INPUT);
	Serial.begin(9600);
}

void loop() {
	if (digitalRead(pinButton) == 0 && !wasButtonPressed) {
		wasButtonPressed = true;
		delay(30);
	}
	if (digitalRead(pinButton) == 1 && wasButtonPressed) {
		wasButtonPressed = false;
		delay(30);
		motorDirection *= -1;
	}
	stepper.step(motorSteps * motorDirection);
}

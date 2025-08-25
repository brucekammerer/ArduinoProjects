#include <Servo.h>

const byte pinServo = 9;
const byte messageLength = 5;
const byte lastIndex = messageLength - 1;

char message[messageLength];
int servoAngle = 0;
boolean gotMessage = false;
boolean askedQuestion = false;
Servo servo;

void getMessage() {
	static byte index = 0;
	if (Serial.available() && !gotMessage) {
		char nextChar = Serial.read();
		if (nextChar == '\n') {
			message[index] = '\0';
			index = 0;
			gotMessage = true;
		} else {
			message[index] = nextChar;
			if (index != lastIndex) {
				index++;
			}
		}
	}
}

void processMessage() {
	if (gotMessage) {
		int angle = atoi(message);
		if (angle >= 0 && angle <= 180) {
			servoAngle = angle;
		}
		servo.write(servoAngle);
		gotMessage = false;
		askedQuestion = false;
	}
}

void setup() {
	Serial.begin(9600);
	servo.attach(pinServo);
}

void loop() {
	if (!askedQuestion) {
		Serial.println("What angle to the servo?");
		askedQuestion = true;
	}
	getMessage();
	processMessage();
}

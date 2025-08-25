#include <Servo.h>

const byte pinServo1 = 5;
const byte pinServo2 = 6;
const byte pinX = A1;
const byte pinY = A0;
const byte pinZ = 12;
const byte pinBuz = 7;

Servo servo1;
Servo servo2;
byte angleServo1;
byte angleServo2;
int valX;
int valY;
int valZ;


void setup() {
	Serial.begin(9600);
	servo1.attach(pinServo1);
	servo2.attach(pinServo2);
	servo1.write(0);
	servo2.write(90);
	pinMode(pinBuz, OUTPUT);
}

void loop() {
	valX = analogRead(pinX);
	valY = analogRead(pinY);
	valZ = digitalRead(pinZ);
	angleServo1 = (int)(valX * -180.0 / 1023.0 + 180.0);
	angleServo2 = (int)(valY * -180.0 / 1023.0 + 180.0);
	servo1.write(angleServo1);
	servo2.write(angleServo2);
	if (valZ == 0) {
		digitalWrite(pinBuz, HIGH);
	} else {
		digitalWrite(pinBuz, LOW);
	}
	Serial.println(valZ);
	delay(100);
}

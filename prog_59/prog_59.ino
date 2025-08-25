#include <LiquidCrystal.h>

const byte pinEcho = 12;
const byte pinTrig = 11;
const byte pinButton = 10;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
float distance;
int buttonStateOld;
int buttonStateCurrent;

float getDuration() {
	digitalWrite(pinTrig, LOW);
	delayMicroseconds(2);
	digitalWrite(pinTrig, HIGH);
	delayMicroseconds(10);
	digitalWrite(pinTrig, LOW);
	return pulseIn(pinEcho, HIGH);
}

float getAverageDistance(byte times) {
	float allDurations = 0;
	for (byte i = 1; i <= times; i++) {
		allDurations += getDuration();
	}
	float duration = allDurations / times;
	return duration * 0.034 / 2.0;
}

void setup() {
	Serial.begin(9600);
	pinMode(pinEcho, INPUT);
	pinMode(pinTrig, OUTPUT);
	pinMode(pinButton, INPUT_PULLUP);
	lcd.begin(16, 2);
	buttonStateOld = digitalRead(pinButton);
	lcd.setCursor(0, 0);
	lcd.print("Click the btn to");
	lcd.setCursor(0, 1);
	lcd.print("get the distance");
}

void loop() {
	buttonStateCurrent = digitalRead(pinButton);
	if (buttonStateCurrent == 0 && buttonStateOld == 1) {
		delay(30);
	} else if (buttonStateCurrent == 1 && buttonStateOld == 0) {
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("Measuring...");
		distance = getAverageDistance(20);
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("Distance: ");
		lcd.setCursor(0, 1);
		lcd.print(distance);
		lcd.print(" cm");
		delay(30);
	}
	buttonStateOld = buttonStateCurrent;
}

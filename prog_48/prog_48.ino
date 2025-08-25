#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int dt = 500;

int valuePot; 

void setup() {
	Serial.begin(9600);
	lcd.begin(16, 2);
}

void loop() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Watch me Count");
	delay(dt);
	lcd.setCursor(0, 1);
	for (int i = 0; i < 11; i++) {
		lcd.print(i);
		delay(dt);
		lcd.setCursor(0, 1);
	}
	lcd.clear();
}

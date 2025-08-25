#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 12
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
	Serial.begin(9600);
	Serial.println(F("<DHT11 test>"));
	dht.begin();
	lcd.begin(16, 2);
}

void loop() {
	float h = dht.readHumidity();
	float t = dht.readTemperature();
	if (isnan(h) || isnan(t))
		return;
	lcd.clear();
	lcd.print(F("Humidity: "));
	lcd.print(h);
	lcd.print(F("%"));
	lcd.setCursor(0, 1);
	lcd.print(F("Temp: "));
	lcd.print(t);
	lcd.print(F("C"));
	delay(500);
}

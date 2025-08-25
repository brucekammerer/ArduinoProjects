#include <DHT.h>
#include <ArduinoGraphics.h>
#include <Arduino_LED_Matrix.h>

#define BTN_PIN 12
#define DHT_PIN 8
#define DHT_TYPE 11
#define DT 2000
#define ROWS 8
#define COLS 12

DHT dht(DHT_PIN, DHT_TYPE);
ArduinoLEDMatrix ledMatrix;
uint8_t frame[ROWS][COLS];
boolean btnStates[] = {false, false};

void setup() {
	pinMode(BTN_PIN, INPUT_PULLUP);
	dht.begin();
	ledMatrix.begin();
}

void renderMsg(char* msg) {
	ledMatrix.beginDraw();
	ledMatrix.textScrollSpeed(50);
	ledMatrix.textFont(Font_5x7);
	ledMatrix.beginText(0, 1, 255, 0, 0);
	ledMatrix.println(msg);
	ledMatrix.endText(SCROLL_LEFT);
	ledMatrix.endDraw();
}

char* createMsg(float h, float c, float f, float hic, float hif) {
	const uint8_t msgLen = 128;
	char msg[msgLen];
	snprintf(msg,
					 msgLen,
					 "        Humidity: %.2f%%, Temperature: %.2fC, %.2fF, Heat index: %.2fC, %.2fF",
					 h, c, f, hic, hif);
	renderMsg(msg);
}

void handleButtonClick() {
	boolean isFahrenheit = true;
	float h = dht.readHumidity();
	float c = dht.readTemperature();
	float f = dht.readTemperature(isFahrenheit);

	if (isnan(h) || isnan(c) || isnan(f)) {
		Serial.println("Failed to read from DHT sensor!");
		return;
	}

	float hif = dht.computeHeatIndex(f, h);
	float hic = dht.computeHeatIndex(c, h, !isFahrenheit);

	renderMsg(createMsg(h, c, f, hic, hif));
}

void loop() {
	btnStates[0] = digitalRead(BTN_PIN) == 0;
	if (!btnStates[1] && btnStates[0]) {
		delay(30);
	} else if (btnStates[1] && !btnStates[0]) {
		delay(30);
		handleButtonClick();
	}
	btnStates[1] = btnStates[0];
}

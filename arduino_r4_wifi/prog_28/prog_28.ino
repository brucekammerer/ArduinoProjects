#include <ArduinoGraphics.h>
#include <Arduino_LED_Matrix.h>

#define PIN_LED 13
#define ROWS 8
#define COLS 12

ArduinoLEDMatrix matrix;
uint8_t frame[ROWS][COLS];


void nullifyFrame() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			frame[i][j] = 0;
		}
	}
}

void displayRunningColumns() {
	for (int i = 1; i < COLS - 1; i++) {
		for (int j = 1; j < ROWS - 1; j++) {
			frame[j][i] = !frame[j][i];
		}
		delay(25);
		matrix.renderBitmap(frame, ROWS, COLS);
	}
}

void fireUpCorners() {
	frame[0][0] = true;
	frame[0][11] = true;
	frame[7][11] = true;
	frame[7][0] = true;
}

void setup() {
	pinMode(PIN_LED, OUTPUT);
	nullifyFrame();
	fireUpCorners();
	matrix.begin();
	nullifyFrame();
}

void loop() {
	matrix.beginDraw();
	matrix.textScrollSpeed(50);
	matrix.textFont(Font_5x7);
	matrix.beginText(0, 1, 255, 0, 0);
	matrix.println("     Hello from Bruce!");
	matrix.endText(SCROLL_LEFT);
	matrix.endDraw();
}

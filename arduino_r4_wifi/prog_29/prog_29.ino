#include <limits.h>
#include <ArduinoGraphics.h>
#include <Arduino_LED_Matrix.h>

#define ROWS 8
#define COLS 12
#define DT 100
#define DT_LONG 2000
#define PIN_BUTTON_UP 3
#define PIN_BUTTON_DOWN 2

ArduinoLEDMatrix matrix;

uint8_t frame[ROWS][COLS];
const uint8_t racketLen = 4;
uint8_t racket[racketLen];

int8_t delta = 0;
int8_t ballX;
int8_t ballY;
int8_t ballSpeedX;
int8_t ballSpeedY;

boolean isButtonUpPressed;
boolean isButtonDownPressed;
boolean wasButtonUpPressed = false;
boolean wasButtonDownPressed = false;
boolean isRunning = true;

void nullifyFrame() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			frame[i][j] = 0;
		}
	}
}

void setUpBall() {
	  ballX = COLS - 1;
		ballY = 3;
		ballSpeedX = -1;
		ballSpeedY = (random(LONG_MAX) % 2) * 2 - 1;
}

void setUpRacket() {
	racket[0] = 2;
	racket[1] = 3;
	racket[2] = 4;
	racket[3] = 5;
}

void fillInRacket() {
	for (int8_t i = 0; i < racketLen; i++) {
		frame[racket[i]][0] = 1;
	}
}

void clearRacket() {
	for (int8_t i = 0; i < racketLen; i++) {
		frame[racket[i]][0] = 0;
	}
}

void moveRacket() {
	if (((delta > 0) && (racket[racketLen - 1] == ROWS-1)) ||
			((delta < 0) && (racket[0] == 0))) {
		return;
	}
	for (int8_t i = 0; i < racketLen; i++) {
		racket[i] += delta;
	}
}

void handleInput() {
	isButtonUpPressed = digitalRead(PIN_BUTTON_UP) == 0;
	if (!wasButtonUpPressed && isButtonUpPressed) {
		delta += 1;
		delay(30);
	} else if (wasButtonUpPressed && !isButtonUpPressed) {
		delta -= 1;
		delay(30);
	}
	isButtonDownPressed = digitalRead(PIN_BUTTON_DOWN) == 0;
	if (!wasButtonDownPressed && isButtonDownPressed) {
		delta -= 1;
		delay(30);
	} else if (wasButtonDownPressed && !isButtonDownPressed) {
		delta += 1;
		delay(30);
	}
	wasButtonUpPressed = isButtonUpPressed;
	wasButtonDownPressed = isButtonDownPressed;
}

void clearBall() {
	frame[ballY][ballX] = 0;
}

void moveBall() {
	ballX += ballSpeedX;
	ballY += ballSpeedY;
}

void fillInBall() {
	frame[ballY][ballX] = 1;
}

void handleCollisions() {
	if (ballX == 0) {
		boolean areCollided = false;
		for (int8_t i = 0; i < racketLen; i++) {
			if (ballY == racket[i]) {
				ballSpeedX *= -1;
				areCollided = true;
				break;
			} 
		}
		if (!areCollided) {
			isRunning = false;
		}
	} else if (ballX == COLS - 1) {
		ballSpeedX *= -1;
	}
	if (ballY == 0 || ballY == ROWS - 1) {
		ballSpeedY *= -1;
	}
}

void fillInFrame() {
	fillInBall();
	fillInRacket();
}

void displayMessage() {
	matrix.beginDraw();
	matrix.textScrollSpeed(50);
	matrix.textFont(Font_5x7);
	matrix.beginText(0, 1, 255, 0, 0);
	matrix.println("     You're lost!");
	matrix.endText(SCROLL_LEFT);
	matrix.endDraw();
}

void setup() {
	randomSeed(analogRead(0));
	Serial.begin(9600);
	pinMode(PIN_BUTTON_UP, INPUT_PULLUP);
	pinMode(PIN_BUTTON_DOWN, INPUT_PULLUP);
	matrix.begin();
	nullifyFrame();
	setUpBall();
	setUpRacket();
	fillInBall();
	fillInRacket();
	matrix.renderBitmap(frame, ROWS, COLS);
	delay(DT_LONG);
}

void loop() {
	clearBall();
	clearRacket();
	if (!isRunning) {
		displayMessage();
		setUpBall();
		setUpRacket();
		fillInFrame();
		matrix.renderBitmap(frame, ROWS, COLS);
		delay(DT_LONG);
		isRunning = true;
	} else {
		handleInput();
	  moveBall();
	  moveRacket();
	  handleCollisions();
		fillInFrame();
		matrix.renderBitmap(frame, ROWS, COLS);
		delay(DT);
	}
}

#include <IRremote.h>

/*
You cannot use pins 3 and 11 for analogWrite.
Use other pins with PWM.
 */

/*
turon on/off LED

0 - white
1 - red
2 - green
3 - blue
4 - cyan
5 - magenta
6 - yellow
down - dim led
up - brighten led

brightness should be maintained between colors

 */

#define PIN_R 10
#define PIN_G 9
#define PIN_B 6
#define PIN_IR 5
#define B0 0xE916FF00
#define B1 0xF30CFF00
#define B2 0xE718FF00
#define B3 0xA15EFF00
#define B4 0xF708FF00
#define B5 0xE31CFF00
#define B6 0xA55AFF00
#define B_ON_OFF 0xBC43FF00
#define B_LIGHT_UP 0xEA15FF00
#define B_LIGHT_DOWN 0xF807FF00
 
IRrecv receiver(PIN_IR);
IRRawDataType result;
byte color[] = {0, 0, 0};
byte oldColor[] = {255, 255, 255};
float coefficient = 1.0;
boolean isLedOn = false;

void setR(byte light) {
	analogWrite(PIN_R, 255 - light);
}

void setG(byte light) {
	analogWrite(PIN_G, 255 - light);
}

void setB(byte light) {
	analogWrite(PIN_B, 255 - light);
}

void turnRGBLedOff() {
	setR(0);
	setG(0);
	setB(0);
}

void setup() {
	Serial.begin(9600);
	pinMode(PIN_R, OUTPUT);
	pinMode(PIN_G, OUTPUT);
	pinMode(PIN_B, OUTPUT);
	receiver.begin(PIN_IR, ENABLE_LED_FEEDBACK);
	turnRGBLedOff();
}

void setColor(byte r, byte g, byte b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void increaseCoefficient() {
	boolean allLessThan1 = coefficient*color[0] < 1
		&& coefficient*color[1] < 1
		&& coefficient*color[2] < 1;
	boolean allLessThan2 = coefficient*color[0] < 2
		&& coefficient*color[1] < 2
		&& coefficient*color[2] < 2;
	if (allLessThan1 || !allLessThan2) {
		coefficient *= 1.35;
		if (coefficient > 1.0)
			coefficient = 1.0;
		return;
	}
	while (allLessThan2) {
		coefficient *= 1.35;
		allLessThan2 = coefficient*color[0] < 2
			&& coefficient*color[1] < 2
			&& coefficient*color[2] < 2;
	}
}

void decreaseCoefficient() {
	boolean allLessThan1 = coefficient*color[0] < 1
		&& coefficient*color[1] < 1
		&& coefficient*color[2] < 1;
	if (allLessThan1)
		return;
	boolean allLessThan2 = coefficient*color[0] < 2
		&& coefficient*color[1] < 2
		&& coefficient*color[2] < 2;
	if (!allLessThan2) {
		coefficient *= 0.75;
		return;
	}
	while (!allLessThan1) {
		coefficient *= 0.75;
		allLessThan1 = coefficient*color[0] < 1
			&& coefficient*color[1] < 1
			&& coefficient*color[2] < 1;
	}
}

void applyColor() {
	setR(byte(coefficient*color[0]));
	setG(byte(coefficient*color[1]));
	setB(byte(coefficient*color[2]));
}

void printColor() {
	Serial.print(byte(coefficient*color[0]));
	Serial.print(",");
	Serial.print(byte(coefficient*color[1]));
	Serial.print(",");
	Serial.println(byte(coefficient*color[2]));
}

void parseOnOff() {
	if (result == B_ON_OFF) {
		if (isLedOn) {
			oldColor[0] = color[0];
			oldColor[1] = color[1];
			oldColor[2] = color[2];
			setColor(0, 0, 0);
		} else {
			setColor(oldColor[0], oldColor[1], oldColor[2]);
		}
		isLedOn = !isLedOn;
	}
}

void parseOther() {
	switch (result) {
	case B0:
		setColor(255, 255, 255);
		break;
	case B1:
		setColor(255, 0, 0);
		break;
	case B2:
		setColor(0, 255, 0);
		break;
	case B3:
		setColor(0, 0, 255);
		break;
	case B4:
		setColor(0, 255, 255);
		break;
	case B5:
		setColor(255, 0, 255);
		break;
	case B6:
		setColor(255, 255, 0);
		break;
	case B_LIGHT_UP:
		increaseCoefficient();
		break;
	case B_LIGHT_DOWN:
		decreaseCoefficient();
		break;
	}
}

void parseSignal() {
	parseOnOff();
	if (isLedOn) {
		parseOther();
	}
}

void loop() {
	if (receiver.decode()) {
		result = receiver.decodedIRData.decodedRawData;
		parseSignal();
		applyColor();
		printColor();
		delay(100);
		receiver.resume();
	}
}

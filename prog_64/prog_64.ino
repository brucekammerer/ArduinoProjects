#include <IRremote.h>

#define B0 0xFF6897
#define B1 0xFF30CF
#define B2 0xFF18E7
#define B3 0xFF7A85
#define B4 0xFF10EF
#define B5 0xFF38C7
#define B6 0xFF5AA5
#define B7 0xFF42BD
#define B8 0xFF4AB5
#define B9 0xFF52AD
#define B100 0xFF9867
#define B200 0xFFB04F
#define B_VOL_DOWN 0xFFE01F
#define B_VOL_UP 0xFFA857
#define B_EQ 0xFF906F
#define B_PREV 0xFF22DD
#define B_NEXT 0xFF02FD
#define B_PLAY_PAUSE 0xFFC23D
#define B_CHANNEL_PREV 0xFFA25D
#define B_CHANNEL 0xFF629D
#define B_CHANNEL_NEXT 0xFFE21D

const byte pinEnable = 5;
const byte pinIn1 = 2;
const byte pinIn2 = 7;
const byte pinIR = 11;
const byte pinPower = 8;
const byte pinLed = 4;

const int minSpeed = 135;

IRrecv receiver(pinIR);
decode_results result;
boolean isMotorOn = false;
boolean isClockwise = true;
int speedStep = 5;
int motorSpeed = 180;

void setup() {
	TCCR2B = 0b00000001;
	TCCR2A = 0b00000011;
	Serial.begin(9600);
	receiver.enableIRIn();
	pinMode(pinPower, OUTPUT);
	pinMode(pinEnable, OUTPUT);
	pinMode(pinIn1, OUTPUT);
	pinMode(pinIn2, OUTPUT);
	pinMode(pinLed, OUTPUT);
	digitalWrite(pinPower, HIGH);
	digitalWrite(pinIn1, LOW);
	digitalWrite(pinIn2, HIGH);
	analogWrite(pinEnable, 0);
}

void kickstartMotor() {
	analogWrite(pinEnable, 255);
	delay(25);
	analogWrite(pinEnable, motorSpeed);
}

void loop() {
	if (receiver.decode(&result) != 0) {
		switch (result.value) {
		case B_PLAY_PAUSE:
			if (isMotorOn) {
				analogWrite(pinEnable, 0);
			} else {
				kickstartMotor();
			}
			isMotorOn = !isMotorOn;
			break;
		case B_PREV:
			if (isMotorOn && isClockwise) {
				digitalWrite(pinIn1, HIGH);
				digitalWrite(pinIn2, LOW);
				isClockwise = false;
				kickstartMotor();
			}
			break;
		case B_NEXT:
			if (isMotorOn && !isClockwise) {
				digitalWrite(pinIn1, LOW);
				digitalWrite(pinIn2, HIGH);
				isClockwise = true;
				kickstartMotor();
			}
			break;
		case B_VOL_UP:
			if (isMotorOn && motorSpeed != 255) {
				if (motorSpeed == 0) {
					motorSpeed = minSpeed;
					analogWrite(pinEnable, 255);
					delay(25);
				} else {
					motorSpeed += speedStep;
					if (motorSpeed > 255) {
						motorSpeed = 255;
					}
				}
				analogWrite(pinEnable, motorSpeed);
			}
			break;
		case B_VOL_DOWN:
			if (isMotorOn && motorSpeed != 0) {
				motorSpeed -= speedStep;
				if (motorSpeed < minSpeed) {
					motorSpeed = 0;
				}
				analogWrite(pinEnable, motorSpeed);
			}
			break;
		case B0:
			motorSpeed = 0;
			kickstartMotor();
			break;
		case B1:
			motorSpeed = 135;
			kickstartMotor();
			break;
		case B2:
			motorSpeed = 150;
			kickstartMotor();
			break;
		case B3:
			motorSpeed = 165;
			kickstartMotor();
			break;
		case B4:
			motorSpeed = 180;
			kickstartMotor();
			break;
		case B5:
			motorSpeed = 195;
			kickstartMotor();
			break;
		case B6:
			motorSpeed = 210;
			kickstartMotor();
			break;
		case B7:
			motorSpeed = 225;
			kickstartMotor();
			break;
		case B8:
			motorSpeed = 240;
			kickstartMotor();
			break;
		case B9:
			motorSpeed = 255;
			kickstartMotor();
			break;			
		}
		if (motorSpeed == 255) {
			digitalWrite(pinLed, HIGH);
		} else {
			digitalWrite(pinLed, LOW);
		}
		Serial.print("Motor speed: ");
		Serial.println(motorSpeed);
		delay(100);
		receiver.resume();
	}
}

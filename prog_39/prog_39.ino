#define STOP 0
#define FORWARD -1
#define BACKWARD 1

const byte pinVRx = A0;
const byte pinVRy = A1;
const byte pinSwitch = 12;

const byte pinSpeed = 3;
const byte pinDirection1 = 7;
const byte pinDirection2 = 8;

const int stopValueMin = 512;
const int stopValueMax = 532;

int valX;
int valY;
int motorSpeed;
boolean isSwitchClosed = false;
int8_t oldMotorState = STOP;
int8_t currentMotorState;

void setup() {
	TCCR2B = 0b00000001;
	TCCR2A = 0b00000011;
	Serial.begin(9600);
	pinMode(pinVRx, INPUT);
	pinMode(pinVRy, INPUT);
	pinMode(pinSwitch, INPUT);
	pinMode(pinSpeed, OUTPUT);
	pinMode(pinDirection1, OUTPUT);
	pinMode(pinDirection2, OUTPUT);
}

void loop() {
	isSwitchClosed = digitalRead(pinSwitch) == 0;
	valX = analogRead(pinVRx);
	valY = analogRead(pinVRy);
	if (valY > stopValueMax) {
		currentMotorState = BACKWARD;
		motorSpeed = (int)((65.0 * valY + 58710.0) / 491.0);
	} else if (valY < stopValueMin) {
		currentMotorState = FORWARD;
		motorSpeed = (int)(-65.0 * valY / 512.0 + 255.0);
	} else {
		currentMotorState = STOP;
		motorSpeed = 0;
	}
	if (oldMotorState == FORWARD && currentMotorState == BACKWARD) {
		digitalWrite(pinDirection1, HIGH);
		digitalWrite(pinDirection2, LOW);
	} else if (oldMotorState == BACKWARD && currentMotorState == FORWARD) {
		digitalWrite(pinDirection1, LOW);
		digitalWrite(pinDirection2, HIGH);
	} else if (oldMotorState == STOP && currentMotorState == FORWARD) {
		digitalWrite(pinDirection1, LOW);
		digitalWrite(pinDirection2, HIGH);
	} else if (oldMotorState == STOP && currentMotorState == BACKWARD) {
		digitalWrite(pinDirection1, HIGH);
		digitalWrite(pinDirection2, LOW);
	}
	analogWrite(pinSpeed, motorSpeed);
	delay(100);
}

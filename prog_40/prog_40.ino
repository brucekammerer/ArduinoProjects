enum MotorState {
	STOP,
	FORWARD,
	BACKWARD
};

const byte pinButtonMinus = 11;
const byte pinButtonPlus = 12;
const byte pinMotorSpeed = 3;
const byte pinMotorDirection1 = 4;
const byte pinMotorDirection2 = 5;

enum MotorState motorState;
int motorSpeed;
int motorSpeedStep;
boolean isSpeedUpNeeded;
boolean isDirectionPositive;
boolean isButtonMinusPressed;
boolean wasButtonMinusPressed;
boolean isButtonPlusPressed;
boolean wasButtonPlusPressed;

void handleClick() {
 	motorSpeed += (isDirectionPositive ? motorSpeedStep : -motorSpeedStep);
 	if (motorSpeed == motorSpeedStep) {
		digitalWrite(pinMotorDirection1, LOW);
		digitalWrite(pinMotorDirection2, HIGH);
		isSpeedUpNeeded = true;
 		motorSpeed = 175;
 	} else if (motorSpeed == -motorSpeedStep) {
		digitalWrite(pinMotorDirection1, HIGH);
		digitalWrite(pinMotorDirection2, LOW);
		isSpeedUpNeeded = true;
 		motorSpeed = -175;
 	} else if (motorSpeed > 255) {
 		motorSpeed = 255;
 	} else if (motorSpeed < -255) {
		motorSpeed = -255;
	} else if (motorSpeed > 0 && motorSpeed < 175) {
 		motorSpeed = 0;
	} else if (motorSpeed > -175 && motorSpeed < 0) {
 		motorSpeed = 0;
	}
}

void setup() {
	Serial.begin(9600);
	pinMode(pinButtonMinus, INPUT_PULLUP);
	pinMode(pinButtonPlus, INPUT_PULLUP);
	pinMode(pinMotorSpeed, OUTPUT);
	pinMode(pinMotorDirection1, OUTPUT);
	pinMode(pinMotorDirection2, OUTPUT);
	digitalWrite(pinMotorDirection1, LOW);
	digitalWrite(pinMotorDirection2, HIGH);
	motorState = STOP;
	motorSpeed = 0;
	motorSpeedStep = 5;
	wasButtonMinusPressed = false;
	wasButtonPlusPressed = false;
	isSpeedUpNeeded = false;
}

void loop() {
	isButtonMinusPressed = digitalRead(pinButtonMinus) == 0;
	isButtonPlusPressed = digitalRead(pinButtonPlus) == 0;
	if (!isButtonMinusPressed && wasButtonMinusPressed) {
		isDirectionPositive = false;
		handleClick();
		delay(30);
	} else if (isButtonMinusPressed && !wasButtonMinusPressed) {
		delay(30);
	}
	if (!isButtonPlusPressed && wasButtonPlusPressed) {
		isDirectionPositive = true;
		handleClick();
		delay(30);
	} else if (isButtonPlusPressed && !wasButtonPlusPressed) {
		delay(30);
	}
	Serial.println(motorSpeed);
	if (isSpeedUpNeeded) {
		analogWrite(pinMotorSpeed, 255);
		delay(50);
		isSpeedUpNeeded = false;
	}
	analogWrite(pinMotorSpeed, abs(motorSpeed));
	wasButtonMinusPressed = isButtonMinusPressed;
	wasButtonPlusPressed = isButtonPlusPressed;
	delay(100);
}

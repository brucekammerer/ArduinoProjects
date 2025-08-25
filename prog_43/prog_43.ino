const byte SD_IN = 12;
const byte ST_CP = 11;
const byte SH_CP = 10;
const byte MR = 8;
const byte pinBtnStart = 2;
const byte pinBtnEnd = 3;
const byte pinBtnZero = 4;
const byte pinBtnOne = 5;
const byte pinBtnClear = 6;

byte ledsData = 0b00000010;
boolean btnStartStateCurrent;
boolean btnStartStateOld;
boolean btnEndStateCurrent;
boolean btnEndStateOld;
boolean btnZeroStateCurrent;
boolean btnZeroStateOld;
boolean btnOneStateCurrent;
boolean btnOneStateOld;
boolean btnClearStateCurrent;
boolean btnClearStateOld;

void setup() {
	Serial.begin(9600);
	pinMode(SD_IN, OUTPUT);
	pinMode(ST_CP, OUTPUT);
	pinMode(SH_CP, OUTPUT);
	pinMode(MR, OUTPUT);
	pinMode(pinBtnStart, INPUT_PULLUP);
	pinMode(pinBtnEnd, INPUT_PULLUP);
	pinMode(pinBtnZero, INPUT_PULLUP);
	pinMode(pinBtnOne, INPUT_PULLUP);
	pinMode(pinBtnClear, INPUT_PULLUP);
	digitalWrite(MR, HIGH);
	digitalWrite(ST_CP, LOW);
	for (int i = 0; i < 8; i++) {
		digitalWrite(SD_IN, LOW);
		digitalWrite(SH_CP, HIGH);
		digitalWrite(SH_CP, LOW);
	}
	digitalWrite(ST_CP, HIGH);
	btnStartStateOld = digitalRead(pinBtnStart);
	btnEndStateOld = digitalRead(pinBtnEnd);
	btnZeroStateOld = digitalRead(pinBtnZero);
	btnOneStateOld = digitalRead(pinBtnOne);
	btnClearStateOld = digitalRead(pinBtnClear);
	delay(30);
}

void loop() {
	btnStartStateCurrent = digitalRead(pinBtnStart);
	btnEndStateCurrent = digitalRead(pinBtnEnd);
	btnZeroStateCurrent = digitalRead(pinBtnZero);
	btnOneStateCurrent = digitalRead(pinBtnOne);
	btnClearStateCurrent = digitalRead(pinBtnClear);
	if (btnStartStateCurrent == 0 && btnStartStateOld == 1) {
		delay(30);
	} else if (btnStartStateCurrent == 1 && btnStartStateOld == 0) {
		Serial.println("Sent low to latch.");
		digitalWrite(ST_CP, LOW);
		delay(30);
	}
	if (btnEndStateCurrent == 0 && btnEndStateOld == 1) {
		delay(30);
	} else if (btnEndStateCurrent == 1 && btnEndStateOld == 0) {
		Serial.println("Sent high to latch.");
		digitalWrite(ST_CP, HIGH);
		delay(30);
	}
	if (btnZeroStateCurrent == 0 && btnZeroStateOld == 1) {
		delay(30);
	} else if (btnZeroStateCurrent == 1 && btnZeroStateOld == 0) {
		Serial.println("Sent 0 to the shift register.");
		digitalWrite(SD_IN, LOW);
		digitalWrite(SH_CP, HIGH);
		digitalWrite(SH_CP, LOW);
		delay(30);
	}
	if (btnOneStateCurrent == 0 && btnOneStateOld == 1) {
		delay(30);
	} else if (btnOneStateCurrent == 1 && btnOneStateOld == 0) {
		Serial.println("Sent 1 to the shift register.");
		digitalWrite(SD_IN, HIGH);
		digitalWrite(SH_CP, HIGH);
		digitalWrite(SH_CP, LOW);
		delay(30);
	}
	if (btnClearStateCurrent == 0 && btnClearStateOld == 1) {
		delay(30);
	} else if (btnClearStateCurrent == 1 && btnClearStateOld == 0) {
		digitalWrite(MR, LOW);
		digitalWrite(MR, HIGH);
		delay(30);
	}
	btnStartStateOld = btnStartStateCurrent;
	btnEndStateOld = btnEndStateCurrent;
	btnZeroStateOld = btnZeroStateCurrent;
	btnOneStateOld = btnOneStateCurrent;
	btnClearStateOld = btnClearStateCurrent;
}

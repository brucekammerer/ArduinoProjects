const byte pinButton = 2;
const byte pinLed = 3;

boolean isLedOn = false;
boolean isButtonPressed = false;

void setup() {
	Serial.begin(9600);
	pinMode(pinButton, INPUT);
	pinMode(pinLed, OUTPUT);
}

void loop() {
	if ((digitalRead(pinButton) == 1) && !isButtonPressed) {
		delay(30);
		isButtonPressed = true;
	}
	if ((digitalRead(pinButton) == 0) && isButtonPressed) {
		delay(30);
		isButtonPressed = false;
		isLedOn = !isLedOn;
		digitalWrite(pinLed, isLedOn);
	}
}

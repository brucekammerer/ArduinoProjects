const byte pinButton = 2;
const byte pinLed = 3;

byte buttonState;

void setup() {
	Serial.begin(9600);
	pinMode(pinButton, INPUT);
	pinMode(pinLed, OUTPUT);
}

void loop() {
	buttonState = digitalRead(pinButton);
	Serial.println(buttonState);
	if (buttonState == 1) {
		digitalWrite(pinLed, HIGH);
	} else {
		digitalWrite(pinLed, LOW);
	}
	delay(500);
}

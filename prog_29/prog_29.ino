const byte pinLed = 5;
const byte pinBuzzer = 7;
const byte pinButtonInc = 2;
const byte pinButtonDec = 3;

boolean buttonIncState = false;
boolean buttonDecState = false;
byte ledState = 0;
boolean isSignaled = true;

void setup() {
	Serial.begin(9600);
	pinMode(pinLed, OUTPUT);
	pinMode(pinBuzzer, OUTPUT);
	pinMode(pinButtonInc, INPUT);
	pinMode(pinButtonDec, INPUT);
}

void loop() {
	buttonIncState = digitalRead(pinButtonInc);
  buttonDecState = digitalRead(pinButtonDec);
	if (buttonIncState == 0 && buttonDecState == 1) {
		ledState = (ledState < 255) ? ledState + 1 : 255;
	} else if (buttonIncState == 1 && buttonDecState == 0) {
		ledState = (ledState > 0) ? ledState - 1 : 0;
	}
	if (ledState == 255 || ledState == 0) {
		if (!isSignaled) {
			digitalWrite(pinBuzzer, HIGH);
			delay(50);
			digitalWrite(pinBuzzer, LOW);
			isSignaled = true;
		}
	} else {
		isSignaled = false;
	}
	Serial.println(ledState);
	analogWrite(pinLed, ledState);
	delay(10);
}

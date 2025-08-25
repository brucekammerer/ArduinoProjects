const byte pinBuz = 12;
const byte pinBtn = 2;

boolean btnState;

void setup() {
	Serial.begin(9600);
	pinMode(pinBuz, OUTPUT);
	pinMode(pinBtn, INPUT);
	digitalWrite(pinBtn, HIGH);
}

void loop() {
	btnState = digitalRead(pinBtn);
	Serial.println(btnState);
	if (btnState == 0) {
		digitalWrite(pinBuz, HIGH);
	} else {
		digitalWrite(pinBuz, LOW);
	}
	delay(200);
}

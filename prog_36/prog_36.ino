const byte pinTiltSensor = 2;
const byte pinGreen = 7;
const byte pinRed = 8;

boolean tiltSensorValue;

void setup() {
	Serial.begin(9600);
	pinMode(pinTiltSensor, INPUT);
	pinMode(pinGreen, OUTPUT);
	pinMode(pinRed, OUTPUT);
}

void loop() {
	tiltSensorValue = digitalRead(pinTiltSensor);
	if (tiltSensorValue == 1) {
		digitalWrite(pinGreen, HIGH);
		digitalWrite(pinRed, LOW);
	} else {
		digitalWrite(pinGreen, LOW);
		digitalWrite(pinRed, HIGH);
	}
	delay(100);
}

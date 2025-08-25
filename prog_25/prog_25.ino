const int pinSensor = A5;
const int pinLedGreen = 5;
const int pinLedRed = 6;
const int delayTime = 250;

int sensorValue;

void setup() {
  pinMode(pinSensor, INPUT);
	pinMode(pinLedGreen, OUTPUT);
	pinMode(pinLedRed, OUTPUT);
	Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(pinSensor);
	if (sensorValue < 100) {
		digitalWrite(pinLedRed, HIGH);
		digitalWrite(pinLedGreen, LOW);
	} else {
		digitalWrite(pinLedRed, LOW);
		digitalWrite(pinLedGreen, HIGH);
	}
	delay(delayTime);
}

const byte pinPotentiometer = A5;
const byte pinBuzzer = 2;

int potentiometerValue;
int delayTime;

void setup() {
	Serial.begin(9600);
	pinMode(pinPotentiometer, INPUT);
	pinMode(pinBuzzer, OUTPUT);
}

void loop() {
	potentiometerValue = analogRead(pinPotentiometer);
	delayTime = 9940.0 * potentiometerValue / 1023.0 + 60.0;
	digitalWrite(pinBuzzer, HIGH);
	delayMicroseconds(delayTime);
	digitalWrite(pinBuzzer, LOW);
	delayMicroseconds(delayTime);
}

// Lowest: 10 000 Micro Seconds
// Highest: 100 Micro Seconds

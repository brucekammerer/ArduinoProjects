const byte pinPhotoresistor = A5;
const byte pinBuzzer = 7;

int photoresistorValue;
int delayTime;

void setup() {
	Serial.begin(9600);
	pinMode(pinPhotoresistor, INPUT);
	pinMode(pinBuzzer, OUTPUT);
	Serial.println("<Arduino is ready>");
}

void loop() {
	photoresistorValue = analogRead(pinPhotoresistor);
	delayTime = (int)(-98.0 * photoresistorValue / 7.0 + 10700.0);
	Serial.println(delayTime);
	digitalWrite(pinBuzzer, HIGH);
	delayMicroseconds(delayTime);
	digitalWrite(pinBuzzer, LOW);
	delayMicroseconds(delayTime);
}

const byte trigPin = 9;
const byte echoPin = 10;

float duration;
float distance;

void setup() {
	Serial.begin(9600);
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
}

void loop() {
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance = duration * 0.0343 / 2.0;
	Serial.print("The distance is: ");
	Serial.print(distance);
	Serial.println(" cm");
	delay(100);
}

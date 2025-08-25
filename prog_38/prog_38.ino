const byte pinTiltSensor = 2;
const byte pinSpeed = 9;
const byte pinDirection1 = 7;
const byte pinDirection2 = 8;

boolean isTilted;
int motorSpeed = 255;

void setup() {
	Serial.begin(9600);
	pinMode(pinTiltSensor, INPUT);
	pinMode(pinDirection1, OUTPUT);
	pinMode(pinDirection2, OUTPUT);
	pinMode(pinSpeed, OUTPUT);
	digitalWrite(pinDirection1, HIGH);
	digitalWrite(pinDirection2, LOW);
	isTilted = digitalRead(pinTiltSensor) == 0;
	Serial.println(isTilted);
	if (!isTilted) {
		analogWrite(pinSpeed, 255);
		delay(10);
		analogWrite(pinSpeed, motorSpeed);
	}
}

void loop() {
	if ((digitalRead(pinTiltSensor) == 0) && !isTilted) {
		analogWrite(pinSpeed, 0);
		isTilted = true;
	}
	if ((digitalRead(pinTiltSensor) == 1) && isTilted) {
		analogWrite(pinSpeed, 255);
		delay(10);
		analogWrite(pinSpeed, motorSpeed);
		isTilted = false;
	}
}

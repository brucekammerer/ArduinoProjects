const byte pinSpeed = 5;
const byte pinDirection1 = 4;
const byte pinDirection2 = 7;

int motorSpeed = 255;

void setup() {
	pinMode(pinSpeed, OUTPUT);
	pinMode(pinDirection1,OUTPUT);
	pinMode(pinDirection2,OUTPUT);
	digitalWrite(pinDirection1, LOW);
	digitalWrite(pinDirection2, HIGH);
	analogWrite(pinSpeed, 255);
	delay(10);
	analogWrite(pinSpeed, 200);
}

void loop() {
	
}

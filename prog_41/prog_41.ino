byte number;
int delayTime = 500; // ms

void setup() {
	Serial.begin(9600);
	number = 0;
}

void loop() {
	Serial.println(number, HEX);
	number += 1;
	delay(delayTime);
}

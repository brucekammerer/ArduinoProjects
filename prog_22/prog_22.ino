const byte pinPotentiometer = A5;
const int delayTime = 500;
const byte pinBuzzer = 8;
const byte length = 5;
const char endMarker = '\n';

int number;
int potentiometerValue;
char nextChar;
char message[length];
boolean gotMessage = false;

void receiveData() {
	static byte index = 0;
		while (Serial.available() && !gotMessage) {
		nextChar = Serial.read();
		if (nextChar == endMarker) {
			message[index] = '\0';
			index = 0;
			gotMessage = true;
		} else {
			message[index] = nextChar;
			index++;
			index = (index == length)
				? index - 1
				: index;
			}
	}
}

void handleData() {
	if (gotMessage) {
		number = atoi(message);
		if (number > 10) {
			digitalWrite(pinBuzzer, HIGH);
			delay(delayTime);
			digitalWrite(pinBuzzer, LOW);
		}
		gotMessage = false;
	}
}

void setup() {
	pinMode(pinBuzzer, OUTPUT);
	pinMode(pinPotentiometer, INPUT);
	Serial.begin(9600);
	Serial.println("<Arduino is ready>");
}

void loop() {
	potentiometerValue = analogRead(pinPotentiometer);
	Serial.println(potentiometerValue);
	if (potentiometerValue > 1000) {
		digitalWrite(pinBuzzer, HIGH);
	} else {
		digitalWrite(pinBuzzer, LOW);
	}
	delay(delayTime);
}

const byte pinVoltageX = A1;
const byte pinVoltageY = A0;
const byte pinSwitch = 13;

int valVoltageX;
int valVoltageY;
boolean isSwitchClosed;

void setup() {
	Serial.begin(9600);
	pinMode(pinVoltageX, INPUT);
	pinMode(pinVoltageY, INPUT);
	pinMode(pinSwitch, INPUT);
}

void loop() {
	valVoltageX = analogRead(pinVoltageX);
	valVoltageY = analogRead(pinVoltageY);
	isSwitchClosed = digitalRead(pinSwitch);
	Serial.print("X: ");
	Serial.print(valVoltageX);
	Serial.print(", Y: ");
	Serial.print(valVoltageY);
	Serial.print(", Switch: ");
	Serial.println(isSwitchClosed);
	delay(100);
}

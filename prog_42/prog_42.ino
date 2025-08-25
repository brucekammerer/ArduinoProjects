const byte ST_CP = 11;
const byte SH_CP = 9;
const byte SI_P = 12;
const int DT = 500;

byte ledsData;

void setup() {
	Serial.begin(9600);
	pinMode(SI_P, OUTPUT);
	pinMode(ST_CP, OUTPUT);
	pinMode(SH_CP, OUTPUT);
	/* ledsData = 0b10000111; */
	/* digitalWrite(ST_CP, LOW); */
	/* shiftOut(SI_P, SH_CP, LSBFIRST, ledsData); */
	/* digitalWrite(ST_CP, HIGH); */
}

void loop() {
	ledsData = 0x00;
	for (; ledsData <= 0xFF; ledsData++) {
	  digitalWrite(ST_CP, LOW); // telling that we are ready to send some data
	  shiftOut(SI_P, SH_CP, LSBFIRST, ledsData);
	  digitalWrite(ST_CP, HIGH); // telling that the data was sent
		delay(DT);
	}
}

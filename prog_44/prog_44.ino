const byte DATA_INPUT_PIN = 12;
const byte STORAGE_REGISTER_CLOCK_PIN = 11;
const byte SHIFT_REGISTER_CLOCK_PIN = 10;
const byte MASTER_RECLEAR_PIN = 8;

const int dt = 2000;

byte data = 0b10101010;

void shift_right() {
	byte number = data;
	while (1) {
		shiftOut(DATA_INPUT_PIN, SHIFT_REGISTER_CLOCK_PIN, LSBFIRST, number);
		digitalWrite(STORAGE_REGISTER_CLOCK_PIN, LOW);
		digitalWrite(STORAGE_REGISTER_CLOCK_PIN, HIGH);
		delay(dt);
		if (number == 0)
			break;
		number /= 2;
	}
}

void shift_left() {
	byte number = data;
	while (1) {
		shiftOut(DATA_INPUT_PIN, SHIFT_REGISTER_CLOCK_PIN, LSBFIRST, number);
		digitalWrite(STORAGE_REGISTER_CLOCK_PIN, LOW);
		digitalWrite(STORAGE_REGISTER_CLOCK_PIN, HIGH);
		delay(dt);
		if (number == 0xFF)
			break;
		number *= 2;
	}
}

void rotate_left() {
	byte number = data;
	boolean isMSBOne;
	while (1) {
		shiftOut(DATA_INPUT_PIN, SHIFT_REGISTER_CLOCK_PIN, LSBFIRST, number);
		digitalWrite(STORAGE_REGISTER_CLOCK_PIN, LOW);
		digitalWrite(STORAGE_REGISTER_CLOCK_PIN, HIGH);
		delay(dt);
		isMSBOne = number > 127;
		number *= 2;
		if (isMSBOne) {
			number += 1;
		}
	}
}

void rotate_right() {
	byte number = data;
	boolean isLSBOne;
	while (1) {
		shiftOut(DATA_INPUT_PIN, SHIFT_REGISTER_CLOCK_PIN, LSBFIRST, number);
		digitalWrite(STORAGE_REGISTER_CLOCK_PIN, LOW);
		digitalWrite(STORAGE_REGISTER_CLOCK_PIN, HIGH);
		delay(dt);
		isLSBOne = number%2 == 1;
		number /= 2;
		if (isLSBOne) {
			number += 128;
		}
	}
}

void flip_bits() {
 	data = 255 - data;
}

void setup() {
	pinMode(DATA_INPUT_PIN, OUTPUT);
	pinMode(STORAGE_REGISTER_CLOCK_PIN, OUTPUT);
	pinMode(SHIFT_REGISTER_CLOCK_PIN, OUTPUT);
	pinMode(MASTER_RECLEAR_PIN, OUTPUT);
	digitalWrite(MASTER_RECLEAR_PIN, HIGH);
	data = 0b10101010;
}

void loop() {
	shiftOut(DATA_INPUT_PIN, SHIFT_REGISTER_CLOCK_PIN, LSBFIRST, data);
	digitalWrite(STORAGE_REGISTER_CLOCK_PIN, LOW);
	digitalWrite(STORAGE_REGISTER_CLOCK_PIN, HIGH);
	delay(dt);
	flip_bits();
	shiftOut(DATA_INPUT_PIN, SHIFT_REGISTER_CLOCK_PIN, LSBFIRST, data);
	digitalWrite(STORAGE_REGISTER_CLOCK_PIN, LOW);
	digitalWrite(STORAGE_REGISTER_CLOCK_PIN, HIGH);
	delay(dt);
	flip_bits();
}

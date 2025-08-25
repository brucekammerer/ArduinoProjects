#include <LiquidCrystal.h>

const byte messageLength = 32;

char message[messageLength];
char nextChar;
double operandA;
double operandB;
double result;
char op;
LiquidCrystal lsd(2, 3, 4, 5, 6, 7);
boolean sentPrompt = false;

void getMessage() {
	boolean gotMessage = false;
	int index = 0;
	while (!gotMessage) {
		if (Serial.available()) {
			nextChar = Serial.read();
			if (index == messageLength)
				index--;
			if (nextChar == '\n') {
				message[index] = '\0';
				gotMessage = true;
			} else {
				message[index] = nextChar;
				index++;
			}
		}
	}
}

int extractNumber() {
	return atoi(message);
}

void printPrompt(const char* msg, int col, int row, boolean toClear) {
	if (toClear)
		lsd.clear();
	lsd.setCursor(col, row);
	lsd.print(msg);
}

void printResult() {
	lsd.clear();
	lsd.setCursor(0, 0);
	lsd.print(operandA,1);
	lsd.print(op);
	lsd.print(operandB, 1);
	lsd.print(" =");
	lsd.setCursor(0, 1);
	lsd.print("= ");
	lsd.print(result, 1);
}

void setup() {
	int index = 0;
	Serial.begin(9600);
	lsd.begin(20, 2);
}

void loop() {
	printPrompt("Enter A:", 0, 0, true);
	getMessage();
	operandA = atof(message);
	printPrompt("Enter B:", 0, 0, true);
	getMessage();
	operandB = atof(message);
	printPrompt("Enter OP:", 0, 0, true);
	getMessage();
	op = message[0];
	switch (op) {
	case '+':
		result = operandA + operandB;
		break;
	case '-':
		result = operandA - operandB;
		break;
	case '*':
		result = operandA * operandB;
		break;
	case '/':
		result = operandA / operandB;
		break;
	}
	printResult();
	while (true) {
		getMessage();
		if (message[0] == '\0') {
			break;
		}
	}
}

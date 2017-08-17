#include <string>
#include <iostream>

void emptyInputBuffer() {
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n'); // Emptying input buffer
}

double inputNumber() {
	double nr;
	while (true) {
		std::cin >> nr;
		if (std::cin.fail()) {
			std::cout << " is not a valid number.\n";
			emptyInputBuffer();
		}
		else {
			return nr;
		}
	}
}

char inputOperator() {
	std::string legalOperators = "+-*/";
	char op;
	while (true) {
		std::cin >> op;
			for (int i = 0; i < legalOperators.length(); i++) {
				if (op == legalOperators[i]) {
					return op;
				}
			}
		std::cout << "Invalid operator.\n";
		emptyInputBuffer();
	}
}

void runCalc() {
	double nr1, nr2;
	char op;

	nr1 = inputNumber();
	op = inputOperator();
	nr2 = inputNumber();

	std::cout << nr1 << " " << op << " " << nr2 << " = ";

	switch (op) {
	case '+':
		std::cout << nr1 + nr2 << '\n';
		break;
	case '-':
		std::cout << nr1 - nr2 << '\n';
		break;
	case '*':
		std::cout << nr1 * nr2 << '\n';
		break;
	case '/':
		std::cout << nr1 / nr2 << '\n';
		break;
	default:
		std::cout << "Illegal operator.\n";
	}
	//std::cout << "Alt gikk bra." << nr1 + nr2 << '\n';
}

std::string getInput() {
	std::string input = "";
	char c = std::cin.get();
	while (c != '\n') {
		input += c;
		c = std::cin.get();
	}
	return input;
}

char findOperator(std::string s) {
	std::string legalOperators = "+-*/";
	if (s.length() > 1) {
		return '_';
	}
	else {
		for (int i = 0; i < legalOperators.length(); i++) {
			if (s[0] == legalOperators[i]) {
				return legalOperators[i];
			}
		}
		return 'p';
	}
}

void oldMain() {
	//try {
	//	std::cout << "Tall 1> ";
	//	std::string sTall1;
	//	sTall1 = getInput();
	//	int tall1 = stoi(sTall1);

	//	std::cout << "Regneart> ";
	//	std::string sRegneart;
	//	sRegneart = getInput();
	//	char regneart = findOperator(sRegneart);

	//	std::cout << "Tall 2> ";
	//	std::string sTall2;
	//	sTall2 = getInput();
	//	int tall2 = stoi(sTall2);

	//	std::cout << "Svaret på " << tall1 << " " << regneart << " " << tall2 << " er ";

	//	switch (regneart) {
	//	case '+':
	//		std::cout << tall1 + tall2 << ".";
	//		break;
	//	case '-':
	//		std::cout << tall1 - tall2 << ".";
	//		break;
	//	case '*':
	//		std::cout << tall1 * tall2 << ".";
	//		break;
	//	case '/':
	//		std::cout << tall1 / tall2 << ".";
	//		break;
	//	case '_':
	//		std::cout << "ikke mulig å si, siden du puttet inn er operator som hadde mer en et tegn.";
	//		break;
	//	case 'p':
	//		std::cout << "ikke mulig å si, fordi du puttet ikke inn +, -, * eller /.";
	//		break;
	//	default:
	//		std::cout << "vansklig å si, siden jeg ikke vet hva " << regneart << " betyr.";
	//	}
	//}
	//catch (std::invalid_argument& exception) {
	//	std::cout << "Du må jo putte inn tall da.";
	//}

	//std::cout << std::endl;
}

int main() {
	std::string s;
	std::getline(std::cin, s);

	std::cout << s << '\n';

	//runCalc();

	system("PAUSE");
	return 0;
}
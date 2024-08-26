#include "Input.h"
#include <string>
#include <iostream>



bool Input::GetYesOrNo() {

	while (true) {

		std::string input = {};

		std::cin >> input;
		if (input == "yes") {
			return true;
		}
		else if (input == "no") {
			return false;
		}
		else {
			std::cout << "Wrong input. Try again" << std::endl;
		}
	}
}

int Input::GetNumberMinMax(int a_iMin, int a_iMax) {

	while (true) {

		int iInput = 0;
		std::cin >> iInput;

		if (iInput >= a_iMin && iInput <= a_iMax) {
			return iInput;
		}

		else {
			std::cout << "Wrong input. Try again" << std::endl;
		}
	}
}

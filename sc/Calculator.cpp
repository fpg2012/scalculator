#include "Calculator.hpp"
#include <iostream>

int main(void)
{
	SuperCalculator::Calculator calculator;
	std::cout << calculator.calculate("3*3");
	return 0;
}

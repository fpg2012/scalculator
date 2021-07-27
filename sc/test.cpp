#include "Calculator.hpp"

using namespace std;
using namespace SuperCalculator;

int main()
{
	Calculator calculator;
	string s;
	while (!cin.eof())
	{
		string t;
		cin >> t;
		s = s + t;
	}
	cout << calculator.calculate(s);
	return 0;
}

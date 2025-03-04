#include<iostream>
using namespace std;

int main() 
{
	int number1, number2, difference;
	while (cin >> number1 >> number2) 
	{
		difference = number1 - number2;
		if (number1 < number2) 
		{
			difference = -difference;
		}
		cout << difference << endl;
	}
	return 0;
}
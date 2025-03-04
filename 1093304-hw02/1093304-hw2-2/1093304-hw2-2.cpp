#include<iostream>
#include<math.h>
using namespace std;

int main()
{
	int number, power, divisor, sum = 0;
	cout << "Enter a positive integer of at most 8 digits: ";
	cin >> number;
	for (power = 0; power <= 7; power++)
	{
		divisor = pow(10, power);
		sum = (number / divisor) % 10 + sum;
	}
	cout << "The sum of all digits of " << number << " is " << sum << endl;
	return 0;
}
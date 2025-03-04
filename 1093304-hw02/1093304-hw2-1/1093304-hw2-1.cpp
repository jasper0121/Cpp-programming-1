#include<iostream>
#include<math.h>

using namespace std;
int main()
{
	int number, power, remainder, divisor, binary[27], octal = 0, counter = 0, t;
	cout << "Enter a positive decimal integer of at most 8 digits: ";
	cin >> number;
	//十進位轉二進位
	cout << "The binary equivalent of " << number << " is ";
	t = number;
	while (t != 0)
	{
		t = t / 2;
		counter++;
	}
	if (number == 0)
	{
		cout << number;
	}
	else
	{
		for (power = counter - 1; power >= 0; power--)
		{
			divisor = pow(2, power);
			remainder = (number / divisor) % 2;
			binary[power] = remainder;
			cout << binary[power];
		}
	}
	cout << endl;
	//十進位轉八進位
	for (power = 0; number != 0; power++)
	{
		divisor = pow(8, power);
		remainder = (number / divisor) % 8;
		octal = pow(10, power) * remainder + octal;
		if (number / divisor == 0)
		{
			break;
		}
	}
	cout << "The octal equivalent of " << number << " is " << octal << endl;
	return 0;
}
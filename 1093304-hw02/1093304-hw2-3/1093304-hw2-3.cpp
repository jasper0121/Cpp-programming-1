#include<iostream>
#include<math.h>
using namespace std;

int main() 
{
	int number, power, divisor, remainder;
	cout << "all Armstrong numbers of three digits: " << endl;
	for (number = 100; number < 1000; number++) 
	{
		int sum = 0;
		for (power = 0; power < 3; power++) 
		{
			divisor = pow(10, power);
			remainder = (number / divisor) % 10;
			sum = pow(remainder, 3) + sum;
		}
		if (number == sum) 
		{
			cout << number << " ";
		}
	}
	return 0;
}
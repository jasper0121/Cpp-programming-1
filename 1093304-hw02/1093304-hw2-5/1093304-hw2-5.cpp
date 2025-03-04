#include<iostream>
#include<math.h>
using namespace std;

int main()
{
	int number, sum;
	while (cin >> number && number != 0)
	{
		sum = (number * (number + 1) * (2 * number + 1)) / 6;
		cout << sum << endl;
	}
	return 0;
}
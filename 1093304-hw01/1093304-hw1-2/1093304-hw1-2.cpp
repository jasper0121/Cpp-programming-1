#include <iostream> // allows program to perform input and output
using namespace std; // program uses names from the std namespace

int main()
{
	int number; // integer read from user

	cout << "Enter a five-digit integer: "; // prompt
	cin >> number; // read integer from user
	cout << number / 10000 << "   " << (number % 10000) / 1000 << "   " << (number % 1000) / 100 << "   " << (number % 100) / 10 << "   " << number % 10 << endl;
	system("pause");
} // end main
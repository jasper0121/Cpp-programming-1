// Determine whether a number is a palindrome.
#include <iostream>
using namespace std;

int main()
{
    int number; // user input number

    cout << "Enter a 5-digit number: "; // prompt for a number
    cin >> number; // get number
    if (number / 10000 == number % 10 && (number % 10000) / 1000 == (number % 100) / 10)
    {
        cout << number << " is a palindrome!!!" << endl;
    }
    else
    {
        cout << number << " is not a palindrome." << endl;
    }
    system("pause");
} // end main
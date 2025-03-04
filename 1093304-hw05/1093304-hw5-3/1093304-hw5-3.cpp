#include <iostream>
#include <iomanip>
using namespace std;

// returns 10 ^ i == the ith power of ten
int powerOfTen(int i);

// prints all quirksome number from 0 to i
void quirksomeSquares(int i);

int power;
int n; // number of digits
int main()
{
    while (cin >> n)
    {
        power = powerOfTen(n / 2);
        // power = 10 ^ ( n / 2 ) == the ( n / 2 )th power of ten

        // print all quirksome number of n digits
        // power * power == 10 ^ n == the nth power of ten
        quirksomeSquares(power * power - 1);
    }
}

// returns 10 ^ i == the ith power of ten
 int powerOfTen(int i)
{
    if (i > 0) {
        return 10 * powerOfTen(i - 1); //若i>0，則一直呼叫函式直到i=0
    }
    else
    {
        return 1; //i=0時 回傳1給powerOfTen(1-1)
    }
}

// print all quirksome number from 0 to i
void quirksomeSquares(int i)
{
    if (i >= 0) //若i>=0
    {
        quirksomeSquares(i - 1); //則一直呼叫函式直到i=-1
        if ((i / power + i % power) * (i / power + i % power) == i) //i / power=數字前半，i % power=數字後半
        {
            cout  << std::setfill('0') << std::setw(n) << i << endl;
        }
    }
    return;
}
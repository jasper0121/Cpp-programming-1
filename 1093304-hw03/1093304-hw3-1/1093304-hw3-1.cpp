// Polynomial division provided that the quotient and remainder have integer coefficients

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

// outputs the specified polynomial
void output(int polynomial[], int degree);

// returns true if and only if the specified polynomial is zero polynomial
bool isZero(int polynomial[], int degree);

// returns true if and only if polynomial1 == polynomial2
bool equal(int polynomial1[], int polynomial2[], int degree1, int degree2);

// polynomial1 = -polynomial2
void minus(int polynomial1[], int polynomial2[], int& degree1, int degree2);

// addend += adder
void addition(int addend[], int adder[], int& addendDegree, int adderDegree);

// minuend -= subtrahend
void subtraction(int minuend[], int subtrahend[], int& minuendDegree, int subtrahendDegree);

// product = multiplicand * multiplier
void multiplication(int multiplicand[], int multiplier[], int product[],
    int multiplicandDegree, int multiplierDegree, int& productDegree);

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendDegree >= divisorDegree
void division(int dividend[], int divisor[], int quotient[], int remainder[],
    int dividendDegree, int divisorDegree, int& quotientDegree, int& remainderDegree);

const int numTestCases = 200; // the number of test cases
const int arraySize = 20;

int main()
{
    ifstream inFile("Polynomials.dat", ios::in | ios::binary);

    // exit program if ifstream could not open file
    if (!inFile)
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    int numErrors = numTestCases;
    for (int i = 0; i < numTestCases; i++)
    {
        int dividend[arraySize] = {};
        int divisor[arraySize] = {};

        // input dividend and divisor from the file Polynomials.dat
        inFile.read(reinterpret_cast<char*>(dividend), 80);
        inFile.read(reinterpret_cast<char*>(divisor), 80);

        int dividendDegree = arraySize - 1;
        while (dividendDegree > 0 && dividend[dividendDegree] == 0)
            dividendDegree--;

        int divisorDegree = arraySize - 1;
        while (divisorDegree > 0 && divisor[divisorDegree] == 0)
            divisorDegree--;

        cout << "dividend:  ";
        output(dividend, dividendDegree);
        cout << "divisor:  ";
        output(divisor, divisorDegree);

        int quotient[arraySize] = {};
        int remainder[arraySize] = {};
        int quotientDegree = 0;
        int remainderDegree = 0;

        // quotient = dividend / divisor; remainder = dividend % divisor
        // thus, dividend == divisor * quotient + remainder
        division(dividend, divisor, quotient, remainder,
            dividendDegree, divisorDegree, quotientDegree, remainderDegree);

        if (quotientDegree != 0 && quotient[quotientDegree] == 0)
            cout << "Leading zeroes not allowed!\n";

        int buffer[arraySize] = {};
        int bufferDegree = 1;

        // buffer = divisor * quotient
        multiplication(divisor, quotient, buffer, divisorDegree, quotientDegree, bufferDegree);

        if (bufferDegree != 0 && buffer[bufferDegree] == 0)
            cout << "Leading zeroes not allowed!\n";

        // buffer = buffer + remainder = divisor * quotient + remainder
        addition(buffer, remainder, bufferDegree, remainderDegree);

        if (bufferDegree != 0 && buffer[bufferDegree] == 0)
            cout << "Leading zeroes not allowed!\n";

        // if buffer != dividend, an error occurred!
        if (equal(buffer, dividend, bufferDegree, dividendDegree))
            numErrors--;
    }

    inFile.close();

    cout << "\nThere are " << numErrors << " errors.\n\n";

    system("pause");
}

// outputs the specified polynomial
void output(int polynomial[], int degree)
{
    if (isZero(polynomial, degree)) // zero polynomial
        cout << 0;
    else
    {
        if (degree == 0) // constant polynomial
        {
            if (polynomial[0] < 0)
                cout << "-" << -polynomial[0];
            else if (polynomial[0] > 0)
                cout << polynomial[0];
        }
        else
        {
            if (degree == 1) // polynomial of degree 1
            {
                if (polynomial[1] < 0)
                    cout << "-" << -polynomial[1] << "x";
                else if (polynomial[1] > 0)
                    cout << polynomial[1] << "x";
            }
            else // polynomial of degree at least 2
            {
                // display the leading term
                if (polynomial[degree] < 0)
                    cout << "-" << -polynomial[degree] << "x^" << degree;
                else if (polynomial[degree] > 0)
                    cout << polynomial[degree] << "x^" << degree;

                // display all other terms
                for (int i = degree - 1; i > 1; i--)
                    if (polynomial[i] < 0)
                        cout << " - " << -polynomial[i] << "x^" << i;
                    else if (polynomial[i] > 0)
                        cout << " + " << polynomial[i] << "x^" << i;

                // display the term of degree 1
                if (polynomial[1] < 0)
                    cout << " - " << -polynomial[1] << "x";
                else if (polynomial[1] > 0)
                    cout << " + " << polynomial[1] << "x";
            }

            // display the constant term
            if (polynomial[0] < 0)
                cout << " - " << -polynomial[0];
            else if (polynomial[0] > 0)
                cout << " + " << polynomial[0];
        }
    }

    cout << endl;
}

// returns true if and only if the specified polynomial is zero polynomial
bool isZero(int polynomial[], int degree)
{  // leading term is 0
    if (degree == 0 && polynomial[0] == 0)
        return true;
    return false;
}

// returns true if and only if polynomial1 == polynomial2
bool equal(int polynomial1[], int polynomial2[], int degree1, int degree2)
{
    int d1 = degree1; //代替degree1
    int d2 = degree2; //代替degree2
    int counter = d1 + 1; //計數器的數值=陣列個數=最高次方+1
    while (d1 == d2 && d1 >= 0 && d2 >= 0) 
    {
        polynomial1[d1] -= polynomial2[d2]; //若這2個多項式相等，則相減=0
        if (polynomial1[d1] == 0) //若相減後多項式次方的係數為0
        { 
            counter--; //則計數器-1
        }
        d1--;
        d2--;
    }
    if (counter == 0) { //若計數器數=0，則代表這2個多項式相等
        return true;
    }
    else {
        return false;
    }
}

// polynomial1 = -polynomial2
void minus(int polynomial1[], int polynomial2[], int& degree1, int degree2)
{
    degree1 = degree2;
    for (int i = 0; i <= degree1; i++)
        polynomial1[i] = -polynomial2[i];
}

// addend += adder
void addition(int addend[], int adder[], int& addendDegree, int adderDegree)
{
    int addendD = addendDegree; //代替addendDegree
    int adderD = adderDegree; //代替adderDegree
    while (addendD > adderD && adderD >= 0) //被加數的最高次方數>加數的最高次方數
    { 
        addend[adderD] += adder[adderD];
        adderD--;
    }
    while (addendD < adderD && adderD >= 0) //被加數的最高次方數<加數的最高次方數
    { 
        addendD = adderD;
        addend[adderD] += adder[adderD];
        adderD--;
    }
    while (addendD == adderD && adderD >= 0) //被加數的最高次方數=加數的最高次方數
    {
        addend[adderD] += adder[adderD];
        adderD--;
    }
    while (addend[addendD] == 0) //若相加後的多項式其最高次方係數=0
    {
        addendD--; //則最高次方-1
    }
}

// minuend -= subtrahend
void subtraction(int minuend[], int subtrahend[], int& minuendDegree, int subtrahendDegree)
{
    int buffer[arraySize] = {};
    int bufferDegree = 0;

    // buffer = -subtrahend
    minus(buffer, subtrahend, bufferDegree, subtrahendDegree);

    // minuend = minuend + buffer = minuend - subtrahend
    addition(minuend, buffer, minuendDegree, bufferDegree);

    if (minuendDegree != 0 && minuend[minuendDegree] == 0)
        cout << "Leading zeroes not allowed!\n";
}

// product = multiplicand * multiplier
void multiplication(int multiplicand[], int multiplier[], int product[],
    int multiplicandDegree, int multiplierDegree, int& productDegree)
{
    int multiplicandD = multiplicandDegree; //代替multiplicandDegree
    int multiplierD = multiplierDegree; //代替multiplierDegree
    productDegree = multiplicandDegree + multiplierDegree;
    int a; //代表當前乘數正在運算的次方
    int b; //代表當前被乘數正在運算的次方
    for (a = 0; a <= multiplierD; a++) 
    {
        for (b = 0; b <= multiplicandD; b++) 
        {
            product[a + b] += multiplicand[b] * multiplier[a]; //將結果存入該次方的總和中
        }
    }
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendDegree >= divisorDegree
void division(int dividend[], int divisor[], int quotient[], int remainder[],
    int dividendDegree, int divisorDegree, int& quotientDegree, int& remainderDegree)
{
    if (isZero(dividend, dividendDegree))
    {
        quotientDegree = 0;
        quotient[0] = 0;

        remainderDegree = 0;
        remainder[0] = 0;
        return;
    }
    quotientDegree = dividendDegree - divisorDegree; //商的最高次方 = 被除式最高次方 - 除式最高次方
    remainderDegree = dividendDegree; //初始餘式最高次方=被除式最高次方
    for (int i = 0; i <= dividendDegree; i++) //將被除數複製給餘數，之後用餘數做運算
    { 
        remainder[i] = dividend[i];
    }
    int remainderD = remainderDegree; //代替remainderDegree的變數
    int quotientD = quotientDegree; //代替quotientDegree的變數
    int divisorD = divisorDegree; //代替divisiorDegree的變數
    while (remainderD >= divisorD) //當餘式最高次方>=除式最高次方時
    { 
        quotient[quotientD] = remainder[remainderD] / divisor[divisorD];//商的最高次方係數=被除式最高次方係數/除式最高次方係數
        while (divisorD >= 0) 
        {
            remainder[quotientD + divisorD] -= quotient[quotientD] * divisor[divisorD]; //餘數-(當前商的次方的係數x除數)，並將結果存入餘數
            divisorD--;
        }
        divisorD = divisorDegree; //重置除數的次方數
        while (remainder[remainderD] == 0) //若相減後的餘式最高次方係數為0
        {
            remainderD--; //則餘式的最高次方-1
            quotientD--; //商從下一個次方開始計算
        }
        remainderDegree = remainderD; //remainderD將運算完的餘式最高次方傳給remainderDegree
    }
}
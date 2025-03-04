// Polynomial division provided that the quotient and remainder have integer coefficients

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

// outputs the specified polynomial
void output(int coefficient[], int exponent[], int size);

// returns true if and only if the specified polynomial has at least a zero term
bool zeroTerms(int coefficient[], int size);

// returns true if and only if the specified polynomial is zero polynomial
bool isZero(int coefficient[], int size);

// returns true if and only if polynomial1 == polynomial2
bool equal(int coefficient1[], int exponent1[], int size1,
    int coefficient2[], int exponent2[], int size2);

// polynomial1 = -polynomial2
void minus(int coefficient1[], int exponent1[], int& size1,
    int coefficient2[], int exponent2[], int size2);

// addend += adder
void addition(int addendCoef[], int addendExpon[], int& addendSize,
    int adderCoef[], int adderExpon[], int adderSize);

// minuend -= subtrahend
void subtraction(int minuendCoef[], int minuendExpon[], int& minuendSize,
    int subtrahendCoef[], int subtrahendExpon[], int subtrahendSize);

// product = multiplicand * multiplier
void multiplication(int multiplicandCoef[], int multiplicandExpon[], int multiplicandSize,
    int multiplierCoef[], int multiplierExpon[], int multiplierSize,
    int productCoef[], int productExpon[], int& productSize);

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ]
void division(int dividendCoef[], int dividendExpon[], int dividendSize,
    int divisorCoef[], int divisorExpon[], int divisorSize,
    int quotientCoef[], int quotientExpon[], int& quotientSize,
    int remainderCoef[], int remainderExpon[], int& remainderSize);

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
        int dividendCoef[arraySize] = {};
        int dividendExpon[arraySize] = {};
        int divisorCoef[arraySize] = {};
        int divisorExpon[arraySize] = {};

        // input dividend and divisor from the file Polynomials.dat
        inFile.read(reinterpret_cast<char*>(dividendCoef), 80);
        inFile.read(reinterpret_cast<char*>(dividendExpon), 80);
        inFile.read(reinterpret_cast<char*>(divisorCoef), 80);
        inFile.read(reinterpret_cast<char*>(divisorExpon), 80);

        int dividendSize = arraySize;
        while (dividendSize > 1 && dividendCoef[dividendSize - 1] == 0)
            dividendSize--;

        int divisorSize = arraySize;
        while (divisorSize > 1 && divisorCoef[divisorSize - 1] == 0)
            divisorSize--;

        int quotientCoef[arraySize] = {};
        int quotientExpon[arraySize] = {};
        int remainderCoef[arraySize] = {};
        int remainderExpon[arraySize] = {};
        int quotientSize = 1;
        int remainderSize = 1;

        // quotient = dividend / divisor; remainder = dividend % divisor
        // thus, dividend == divisor * quotient + remainder
        division(dividendCoef, dividendExpon, dividendSize,
            divisorCoef, divisorExpon, divisorSize,
            quotientCoef, quotientExpon, quotientSize,
            remainderCoef, remainderExpon, remainderSize);

        if (zeroTerms(quotientCoef, quotientSize))
            cout << "quotient has at least a zero term!\n";

        int bufferCoef[arraySize] = {};
        int bufferExpon[arraySize] = {};
        int bufferSize = 1;

        // buffer = divisor * quotient
        multiplication(divisorCoef, divisorExpon, divisorSize,
            quotientCoef, quotientExpon, quotientSize,
            bufferCoef, bufferExpon, bufferSize);

        if (zeroTerms(bufferCoef, bufferSize))
            cout << "buffer has at least a zero term!\n";

        // buffer = buffer + remainder = divisor * quotient + remainder
        addition(bufferCoef, bufferExpon, bufferSize,
            remainderCoef, remainderExpon, remainderSize);

        if (zeroTerms(bufferCoef, bufferSize))
            cout << "buffer has at least a zero term!\n";

        // if buffer != dividend, an error occurred!
        if (equal(bufferCoef, bufferExpon, bufferSize,
            dividendCoef, dividendExpon, dividendSize))
            numErrors--;
    }

    inFile.close();

    cout << "There are " << numErrors << " errors!\n";

    system("pause");
}

// outputs the specified polynomial
void output(int coefficient[], int exponent[], int size)
{
    // the specified polynomial is zero polynomial
    if (isZero(coefficient, size))
        cout << 0;
    else
    {
        if (coefficient[size - 1] < 0)
            cout << "-" << -coefficient[size - 1];
        else if (coefficient[size - 1] > 0)
            cout << coefficient[size - 1];

        if (exponent[size - 1] > 0)
        {
            if (exponent[size - 1] == 1)
                cout << "x";
            else
                cout << "x^" << exponent[size - 1];
        }

        for (int i = size - 2; i >= 0; i--)
        {
            if (coefficient[i] < 0)
                cout << " - " << -coefficient[i];
            else if (coefficient[i] > 0)
                cout << " + " << coefficient[i];

            if (exponent[i] > 0)
            {
                if (exponent[i] == 1)
                    cout << "x";
                else
                    cout << "x^" << exponent[i];
            }
        }
    }

    cout << endl;
}

// returns true if and only if the specified polynomial has at least a zero term
bool zeroTerms(int coefficient[], int size)
{
    if (!isZero(coefficient, size))
        for (int i = 0; i < size; i++)
            if (coefficient[i] == 0)
                return true;

    return false;
}

// returns true if and only if the specified polynomial is zero polynomial
bool isZero(int coefficient[], int size)
{
    if (size == 1 && coefficient[0] == 0)
        return true;
    return false;
}

// returns true if and only if polynomial1 == polynomial2
bool equal(int coefficient1[], int exponent1[], int size1,
    int coefficient2[], int exponent2[], int size2)
{
    int s1 = size1; //代替size1
    int s2 = size2; //代替size2
    int counter = size1; //計數器個數=陣列個數
    int temp = 0; // 暫存值
    while (s1 == s2 && exponent1[s1 - 1] == exponent2[s2 - 1] && s1 > 0 && s2 > 0) //若size數相同且當前次方相同
    {
        temp = coefficient1[s1 - 1] - coefficient2[s2 - 1]; //暫存值=該次方的係數相減
        if (temp == 0) //若相減後(暫存值)=0
        {
            counter--; //則計數器-1
        }
        s1--;
        s2--;
    }
    if (counter == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// polynomial1 = -polynomial2
void minus(int coefficient1[], int exponent1[], int& size1,
    int coefficient2[], int exponent2[], int size2)
{
    size1 = size2;
    for (int i = 0; i < size1; i++)
    {
        coefficient1[i] = -coefficient2[i];
        exponent1[i] = exponent2[i];
    }
}

// addend += adder
void addition(int addendCoef[], int addendExpon[], int& addendSize,
    int adderCoef[], int adderExpon[], int adderSize)
{
    // if( adder == 0 )
    if (isZero(adderCoef, adderSize))
        return;

    // if( addend == 0 )
    if (isZero(addendCoef, addendSize))
    {
        // addend = adder
        addendSize = adderSize;
        for (int i = 0; i < addendSize; i++)
        {
            addendCoef[i] = adderCoef[i];
            addendExpon[i] = adderExpon[i];
        }
        return;
    }

    // buffer = 0
    int bufferCoef[arraySize] = {};
    int bufferExpon[arraySize] = {};
    int bufferSize = 1;

    // buffer = -adder
    minus(bufferCoef, bufferExpon, bufferSize, adderCoef, adderExpon, adderSize);

    // if( addend == -adder )
    if (equal(addendCoef, addendExpon, addendSize, bufferCoef, bufferExpon, bufferSize))
    {
        addendSize = 1;     // addend = 0;
        addendCoef[0] = 0;
        addendExpon[0] = 0;
        return;
    }

    int sumExpon[arraySize] = {};
    int sumCoef[arraySize] = {};
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < addendSize && j < adderSize)
    {
        if (addendExpon[i] > adderExpon[j]) //若當前被加式次方>加式次方
        {
            sumExpon[k] = adderExpon[j]; //則該加式次方先存入
            sumCoef[k] = adderCoef[j]; //則該加式係數先存入
            j++;
        }
        else if (addendExpon[i] < adderExpon[j]) //若當前被加式次方<加式次方
        {
            sumExpon[k] = addendExpon[i]; //則該被加式次方先存入
            sumCoef[k] = addendCoef[i]; //則該被加式係數先存入
            i++;
        }
        else if (addendExpon[i] == adderExpon[j]) //若當前被加式次方=加式次方
        {
            sumExpon[k] = addendExpon[i]; //則該被加式次方先存入(也可存入加式次方)
            sumCoef[k] = addendCoef[i] + adderCoef[j]; //因次方相同，故2者係數相加
            i++;
            j++;
        }
        if (sumCoef[k] != 0) //若相加後的係數不等於0
        {
            k++; //則把之後要存的數放在下一位
        }
    }

    while (i < addendSize) //若加式已算完，但被加式還沒
    {
        sumExpon[k] = addendExpon[i]; //則把剩下的被加式次方存入
        sumCoef[k] = addendCoef[i]; //則把剩下的被加式係數存入
        i++;
        k++;
    }

    while (j < adderSize) //若被加式已算完，但加式還沒
    {
        sumExpon[k] = adderExpon[j]; //則把剩下的加式次方存入
        sumCoef[k] = adderCoef[j]; //則把剩下的加式係數存入
        j++;
        k++;
    }

    addendSize = k;
    for (int i = 0; i < addendSize; i++) // addend = sum
    {
        addendCoef[i] = sumCoef[i];
        addendExpon[i] = sumExpon[i];
    }
}

// minuend -= subtrahend
void subtraction(int minuendCoef[], int minuendExpon[], int& minuendSize,
    int subtrahendCoef[], int subtrahendExpon[], int subtrahendSize)
{
    // minuend == subtrahend
    if (equal(minuendCoef, minuendExpon, minuendSize, subtrahendCoef, subtrahendExpon, subtrahendSize))
    {
        minuendSize = 1;     // minuend = 0;
        minuendCoef[0] = 0;
        minuendExpon[0] = 0;
        return;
    }

    // buffer = 0
    int bufferCoef[arraySize] = {};
    int bufferExpon[arraySize] = {};
    int bufferSize = 1;

    // buffer = -subtrahend
    minus(bufferCoef, bufferExpon, bufferSize, subtrahendCoef, subtrahendExpon, subtrahendSize);

    // minuend = minuend + buffer = minuend - subtrahend
    addition(minuendCoef, minuendExpon, minuendSize, bufferCoef, bufferExpon, bufferSize);

    if (minuendSize > 1 && minuendCoef[minuendSize - 1] == 0)
        cout << "Leading zeroes not allowed!\n";
}

// product = multiplicand * multiplier
void multiplication(int multiplicandCoef[], int multiplicandExpon[], int multiplicandSize,
    int multiplierCoef[], int multiplierExpon[], int multiplierSize,
    int productCoef[], int productExpon[], int& productSize)
{
    // product = 0;
    productSize = 1;
    productCoef[0] = 0;
    productExpon[0] = 0;

    // if( multiplicand != 0 && multiplier != 0 )
    if (!isZero(multiplicandCoef, multiplicandSize) &&
        !isZero(multiplierCoef, multiplierSize))
    {
        int bufferSize = multiplicandSize; //緩衝值的陣列數=被乘數陣列數
        int bufferExpon[arraySize] = {};
        int bufferCoef[arraySize] = {};
        int a; //代表當前乘數正在運算的次方
        int b; //代表當前被乘數正在運算的次方
        for (a = 0; a < multiplierSize; a++)
        {
            for (b = 0; b < multiplicandSize; b++)
            {
                bufferExpon[b] = multiplicandExpon[b] + multiplierExpon[a]; //將次方的總和依序填入
                bufferCoef[b] = multiplicandCoef[b] * multiplierCoef[a]; //將係數的乘積依序填入
            }
            addition(productCoef, productExpon, productSize, bufferCoef, bufferExpon, bufferSize);//將每一輪的乘法結果相加
        }
    }
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ]
void division(int dividendCoef[], int dividendExpon[], int dividendSize,
    int divisorCoef[], int divisorExpon[], int divisorSize,
    int quotientCoef[], int quotientExpon[], int& quotientSize,
    int remainderCoef[], int remainderExpon[], int& remainderSize)
{
    // if( dividend == 0 )
    if (isZero(dividendCoef, dividendSize))
    {
        // quotient = 0
        quotientSize = 1;
        quotientCoef[0] = 0;
        quotientExpon[0] = 0;

        // remainder = 0
        remainderSize = 1;
        remainderCoef[0] = 0;
        remainderExpon[0] = 0;
        return;
    }

    // remainder = dividend
    remainderSize = dividendSize;
    for (int i = 0; i < remainderSize; i++)
    {
        remainderCoef[i] = dividendCoef[i];
        remainderExpon[i] = dividendExpon[i];
    }
    quotientSize = dividendExpon[dividendSize - 1] - divisorExpon[divisorSize - 1] + 1;
    int bufferExpon[arraySize]{};
    int bufferCoef[arraySize]{};
    int bufferSize = divisorSize;
    int monomialExpon[1] = {};
    int monomialCoef[1] = {};
    int monomialSize = 1;
    for (int i = quotientSize - 1; i >= 0; i--)
    {
        quotientExpon[i] = remainderExpon[remainderSize - 1] - divisorExpon[divisorSize - 1]; //商當前的次方=餘式當前的最高次方-除式最高次方
        quotientCoef[i] = remainderCoef[remainderSize - 1] / divisorCoef[divisorSize - 1]; // 商當前的係數=餘式當前最高次方的係數/除式最高次方的係數
        monomialExpon[0] = quotientExpon[i]; //將當前商的最高次方獨立出來，為了在之後做運算
        monomialCoef[0] = quotientCoef[i]; //將當前商最高次方的係數獨立出來，為了在之後做運算
        multiplication(divisorCoef, divisorExpon, divisorSize, monomialCoef, monomialExpon, monomialSize, bufferCoef, bufferExpon, bufferSize);
        subtraction(remainderCoef, remainderExpon, remainderSize, bufferCoef, bufferExpon, bufferSize);
        if (remainderCoef[remainderSize - 1] == 0 || divisorExpon[divisorSize - 1] > remainderExpon[remainderSize - 1]) //若多項式被整除或除式次方>餘式次方
        {
            while (quotientCoef[0] == 0) //若商的0號陣列值為0
            {
                for (int x = 0; x < quotientSize - 1; x++)
                {
                    quotientExpon[x] = quotientExpon[x + 1]; //則商的次方在陣列中的位置全部向右移一格
                    quotientCoef[x] = quotientCoef[x + 1]; //則商的係數在陣列中的位置全部向右移一格
                }
                quotientSize--;
            }
            return; //函式停止
        }
    }
}
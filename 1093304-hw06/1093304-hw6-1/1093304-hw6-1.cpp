// Huge integer addition, subtraction, multiplication and division
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::ios;

// enable user to input a positive huge integer
void input(istream& inFile, int*& hugeInt, int& size);

// perform addition, subtraction, multiplication and division
void perform(ostream& outFile, int* hugeInt1, int* hugeInt2, int*& hugeInt3,
    int*& hugeInt4, int size1, int size2, int size3, int size4);

void reset(int*& hugeInt, int& size);

// outputs hugeInt[ size - 1 .. 0 ]
void output(ostream& outFile, int* hugeInt, int size);

// a recursive function that outputs hugeInt[ last .. 0 ]
void recursiveOutput(ostream& outFile, int* hugeInt, int last);

// returns true if and only if the specified huge integer is zero
bool isZero(int* hugeInt, int size);

// return true if and only if hugeInt1 == hugeInt2
bool equal(int* hugeInt1, int* hugeInt2, int size1, int size2);

// a recursive function that returns true if and only if hugeInt1 == hugeInt2
// provided that size1 == size2
bool recursiveEqual(int* hugeInt1, int* hugeInt2, int last);

// returns true if and only if hugeInt1 < hugeInt2
bool less(int* hugeInt1, int* hugeInt2, int size1, int size2);

// a recursive function that returns true if and only if hugeInt1 < hugeInt2
// provided that size1 == size2
bool recursiveLess(int* hugeInt1, int* hugeInt2, int last);

// sum = addend + adder
void addition(int* addend, int* adder, int*& sum, int addendSize, int adderSize, int& sumSize);

// difference = minuend - subtrahend
void subtraction(int* minuend, int* subtrahend, int*& difference,
    int minuendSize, int subtrahendSize, int& differenceSize);

// product = multiplicand * multiplier
void multiplication(int* multiplicand, int* multiplier, int*& product,
    int multiplicandSize, int multiplierSize, int& productSize);

// quotient = dividend / divisor; remainder = dividend % divisor
void division(int* dividend, int* divisor, int*& quotient, int*& remainder,
    int dividendSize, int divisorSize, int& quotientSize, int& remainderSize);

// hugeInt /= 10
void divideBy10(int* hugeInt, int& size);

const int numTestCases = 22; // the number of test cases
const int arraySize = 200;

int main()
{
    system("mode con cols=122");

    ifstream inFile("Test cases.txt", ios::in);

    // exit program if ifstream could not open file
    if (!inFile)
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    ofstream outFile("Result.txt", ios::out);

    // exit program if ofstream could not open file
    if (!outFile)
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    int* hugeInt1 = new int[1]();
    int* hugeInt2 = new int[1]();
    int* hugeInt3 = new int[1]();
    int* hugeInt4 = new int[1]();
    int size1 = 1;
    int size2 = 1;
    int size3 = 1;
    int size4 = 1;

    for (int i = 0; i < numTestCases; i++)
    {
        input(inFile, hugeInt1, size1);
        input(inFile, hugeInt2, size2);
        perform(cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4, size1, size2, size3, size4);
        perform(outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4, size1, size2, size3, size4);
    }

    delete[] hugeInt1;
    delete[] hugeInt2;
    delete[] hugeInt3;
    delete[] hugeInt4;

    inFile.close();
    outFile.close();

    system("pause");
}

// enable user to input a positive huge integer
void input(istream& inFile, int*& hugeInt, int& size)
{
    char numericString[arraySize];

    inFile >> numericString;

    size = strlen(numericString);
    delete[] hugeInt;
    hugeInt = new int[size];
    for (int i = 0; i < size; ++i)
        hugeInt[i] = numericString[size - i - 1] - '0';
}

// perform addition, subtraction, multiplication and division
void perform(ostream& outFile, int* hugeInt1, int* hugeInt2, int*& hugeInt3,
    int*& hugeInt4, int size1, int size2, int size3, int size4)
{
    output(outFile, hugeInt1, size1);
    output(outFile, hugeInt2, size2);

    // hugeInt3 = hugeInt1 + hugeInt2
    addition(hugeInt1, hugeInt2, hugeInt3, size1, size2, size3);
    output(outFile, hugeInt3, size3);
    reset(hugeInt3, size3);

    // if hugeInt1 < hugeInt2
    if (less(hugeInt1, hugeInt2, size1, size2))
    {
        outFile << '-';
        // hugeInt3 = hugeInt2 - hugeInt1
        subtraction(hugeInt2, hugeInt1, hugeInt3, size2, size1, size3);
        output(outFile, hugeInt3, size3); // outputs n2 - n1
    }
    else
    {
        // hugeInt3 = hugeInt1 - hugeInt2
        subtraction(hugeInt1, hugeInt2, hugeInt3, size1, size2, size3);
        output(outFile, hugeInt3, size3); // outputs n1 - n2
    }
    reset(hugeInt3, size3);

    // hugeInt3 = hugeInt1 * hugeInt2
    multiplication(hugeInt1, hugeInt2, hugeInt3, size1, size2, size3);
    output(outFile, hugeInt3, size3); // outputs n1 * n2
    reset(hugeInt3, size3);

    if (isZero(hugeInt2, size2))
    {
        outFile << "DivideByZero!\n";
        outFile << "DivideByZero!\n";
    }
    else
    {
        division(hugeInt1, hugeInt2, hugeInt3, hugeInt4, size1, size2, size3, size4);
        output(outFile, hugeInt3, size3); // outputs n1 / n2
        output(outFile, hugeInt4, size4); // outputs n1 % n2
        reset(hugeInt3, size3);
        reset(hugeInt4, size4);
    }

    outFile << endl;
}

void reset(int*& hugeInt, int& size)
{
    size = 1;
    delete[] hugeInt;
    hugeInt = new int[1]();
}

// outputs hugeInt[ size - 1 .. 0 ]
void output(ostream& outFile, int* hugeInt, int size)
{
    recursiveOutput(outFile, hugeInt, size - 1);
    outFile << endl;
}

// a recursive function that outputs hugeInt[ last .. 0 ]
void recursiveOutput(ostream& outFile, int* hugeInt, int last)
{
    if (last >= 0) //若last>=0
    {
        outFile << hugeInt[last]; //則印出該編號陣列內的數
        recursiveOutput(outFile, hugeInt, last - 1); //並呼叫函式來印下一位的數
    }
    return;
}

// returns true if and only if the specified huge integer is zero
bool isZero(int* hugeInt, int size)
{
    if (size == 1 && hugeInt[0] == 0)
        return true;
    return false;
}

// return true if and only if hugeInt1 == hugeInt2
bool equal(int* hugeInt1, int* hugeInt2, int size1, int size2)
{
    if (size1 != size2)
        return false;

    return recursiveEqual(hugeInt1, hugeInt2, size1 - 1);
}

// a recursive function that returns true if and only if hugeInt1 == hugeInt2
// provided that size1 == size2
bool recursiveEqual(int* hugeInt1, int* hugeInt2, int last)
{
    if (hugeInt1[last] == hugeInt2[last]) //若該位數的數相等
    {
        if (last == 0) //若2者最後一位的數也相同
        {
            return true; //則此2數必相同，故回傳true
        }
        return recursiveEqual(hugeInt1, hugeInt2, last - 1); //則呼叫函式檢查下一位數是否也相等
    }
    else
    {
        return false; //否則回傳false
    }
}

// returns true if and only if hugeInt1 < hugeInt2
bool less(int* hugeInt1, int* hugeInt2, int size1, int size2)
{
    if (size1 < size2)
        return true;
    if (size1 > size2)
        return false;

    return recursiveLess(hugeInt1, hugeInt2, size1 - 1);
}

// a recursive function that returns true if and only if hugeInt1 < hugeInt2
// provided that size1 == size2
bool recursiveLess(int* hugeInt1, int* hugeInt2, int last)
{
    if (hugeInt1[last] == hugeInt2[last]) //若該位數的數相等
    {
        if (last == 0) //若檢查到最後一位數也相等
        {
            return false; //則此2數相等，回傳false
        }
        return recursiveLess(hugeInt1, hugeInt2, last - 1); //則呼叫函式檢查下一位數
    }
    else if (hugeInt1[last] > hugeInt2[last]) //若在該位數hugeInt1>hugeInt2
    {
        return false; //則回傳false
    }
    else if (hugeInt1[last] < hugeInt2[last]) //若在該位數hugeInt1<hugeInt2
    {
        return true; //則回傳true
    }
}

// sum = addend + adder
void addition(int* addend, int* adder, int*& sum, int addendSize, int adderSize, int& sumSize)
{
    sumSize = (addendSize >= adderSize) ? addendSize + 1 : adderSize + 1;

    delete[] sum;
    sum = new int[sumSize]();

    for (int i = 0; i < addendSize; i++)
        sum[i] = addend[i];

    for (int i = 0; i < adderSize; i++)
        sum[i] += adder[i];

    for (int i = 0; i < sumSize - 1; i++)
        if (sum[i] > 9) // carrying
        {
            sum[i] -= 10;
            sum[i + 1]++;
        }

    if (sum[sumSize - 1] == 0)
        sumSize--;
}

// difference = minuend - subtrahend
void subtraction(int* minuend, int* subtrahend, int*& difference,
    int minuendSize, int subtrahendSize, int& differenceSize)
{
    int x; //代表運算時當前的位數
    differenceSize = minuendSize; //設差值的位數=被減數的位數
    delete[] difference; //釋放在main裡對應的記憶體
    difference = new int[differenceSize](); //重新配置動態陣列
    if (equal(minuend, subtrahend, minuendSize, subtrahendSize) == true) //若被減數和減數相同
    {
        differenceSize = 1; //則差的位數=1
        difference[0] = 0; //其值=0
        return;
    }
    for (x = 0; x < subtrahendSize; x++)
    {
        difference[x] = minuend[x] - subtrahend[x]; //將相減後的值存入difference
    }
    while (x < minuendSize) //若相減後被減數還有剩餘
    {
        difference[x] = minuend[x]; //則把剩餘的數存入difference
        x++;
    }
    for (int y = 0; y < differenceSize - 1; y++) //借位系統
    {
        if (difference[y] < 0) //若該號陣列裡的值為負
        {
            difference[y + 1]--; //則向前借一位
            difference[y] += 10; //該負數+10
        }
    }
    while (difference[differenceSize - 1] == 0) //若差值的最高編號陣列內的數=0 (即當時所設的Size高估)
    {
        differenceSize--; //則Size-1直到符合結果的位數
    }
}

// product = multiplicand * multiplier
void multiplication(int* multiplicand, int* multiplier, int*& product,
    int multiplicandSize, int multiplierSize, int& productSize)
{
    int a; //代表當前乘數正在運算的位數
    int b; //代表當前被乘數正在運算的位數
    productSize = multiplicandSize + multiplierSize; //設積的位數=被乘數的位數+乘數的位數
    delete[] product; //釋放在main裡對應的記憶體
    product = new int[productSize](); //重新配置動態陣列
    if (multiplicand[multiplicandSize - 1] == 0 || multiplier[multiplierSize - 1] == 0) //若被乘數或乘數其中一個的值=0
    {
        productSize = 1; //則積的位數=1
        product[productSize - 1] = 0; //其值=0
        return;
    }
    for (a = 0; a < multiplierSize; a++)
    {
        for (b = 0; b < multiplicandSize; b++)
        {
            product[a + b] += multiplicand[b] * multiplier[a]; //將當前的乘積依序填入
        }
    }
    for (int c = 0; c < productSize - 1; c++) //進位系統
    {
        while (product[c] > 9) //若當前該號陣列內的值>9
        {
            product[c] -= 10; //則該值-10
            product[c + 1]++; //向前進一位
        }
    }
    if (product[productSize - 1] == 0) //若乘積最高編號陣列內的數=0 (即當時所設的Size高估)
    {
        productSize--; //則Size-1
    }
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division(int* dividend, int* divisor, int*& quotient, int*& remainder,
    int dividendSize, int divisorSize, int& quotientSize, int& remainderSize)
{
    if (isZero(dividend, dividendSize))
    {
        reset(quotient, quotientSize);
        reset(remainder, remainderSize);
        return;
    }
    int tempSize;
    int buffer[arraySize]{};
    int bufferSize = dividendSize; //設(偽)除數的空間數=被除數的空間數
    remainderSize = dividendSize; //令初始餘數空間數=被除數空間數
    quotientSize = dividendSize - divisorSize; //商的空間數=被除數的空間數-除數的空間數

    delete[] remainder; //釋放在main裡對應的記憶體
    remainder = new int[remainderSize](); //重新配置動態陣列
    for (int x = 0; x < dividendSize; x++) //將被除數陣列內的數複製給餘數
    {
        remainder[x] = dividend[x];
    }
    if (less(dividend, divisor, dividendSize, divisorSize) == true) //若被除數<除數
    {
        quotientSize = 1; //則商的位數=1
        quotient[quotientSize - 1] = 0; //且該位置的數必為0
        return;
    }
    for (int y = divisorSize - 1; y >= 0; y--) //將除數在陣列中做移位
    {
        buffer[bufferSize - 1] = divisor[y];
        bufferSize--;
    }
    bufferSize = dividendSize; //重置bufferSize的位數
    if (less(dividend, buffer, dividendSize, bufferSize) == false) //若被除數>=(偽)除數
    {
        quotientSize++; //商的空間數+1做修正
    }
    delete[] quotient; //釋放在main裡對應的記憶體
    quotient = new int[quotientSize](); //重新配置動態陣列
    int quotientS = quotientSize; //代替quotientSize在之後做運算(quotientS的值會變)
    while (bufferSize >= divisorSize) //<---從此開始做除法運算
    {
        while (less(remainder, buffer, remainderSize, bufferSize) == true) //若(偽)除數>當前的餘數
        {
            if (less(buffer, dividend, bufferSize, dividendSize) == true) //若(偽)除數<被除數
            {
                quotientS--; //將size-1的條件設為：在最一開始做除法時不能減少其空間數
            }
            divideBy10(buffer, bufferSize); //則(偽)除數向右減少一位
        }
        tempSize = remainderSize; //暫存值的功用為存取減過的餘數，故設其空間數=當前餘數的空間數
        int* temp = new int[tempSize](); //設一動態陣列
        subtraction(remainder, buffer, temp, remainderSize, bufferSize, tempSize); //相減，並將其值存入暫存值
        quotient[quotientS - 1]++; //商當前位數內的值+1
        remainderSize = tempSize; //將暫存值所存的空間數還給餘數
        delete[]remainder; //釋放餘數的記憶體
        remainder = temp; //將暫存值的地址給餘數
        if (bufferSize == divisorSize) //若(偽)除數空間數=原本的除數空間數
        {
            if (less(remainder, divisor, remainderSize, divisorSize) == true) //若除數比餘數大
            {
                return; //則運算完成，結束函式
            }
        }
    }
}

// hugeInt /= 10
void divideBy10(int* hugeInt, int& size)
{
    if (size == 1)
        hugeInt[0] = 0;
    else
    {
        for (int i = 1; i < size; i++)
            hugeInt[i - 1] = hugeInt[i];

        size--;
        hugeInt[size] = 0;
    }
}
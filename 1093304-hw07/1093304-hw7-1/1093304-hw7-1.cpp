// Huge integer addition, subtraction, multiplication and division
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

const int numTestCases = 22;
const int arraySize = 200;

// HugeInt struct definition
struct HugeInt
{
    int size = 1;       // the number of digits of the integer; it can never be zero
    int* elems = new int[1](); // used to store a nonnegative integer, one digit per element
};

// enable user to input a positive huge integer
void input(istream& inFile, HugeInt& hugeInt);

// perform addition, subtraction, multiplication and division
void perform(ostream& outFile, HugeInt& hugeInt1, HugeInt& hugeInt2,
    HugeInt& hugeInt3, HugeInt& hugeInt4);

// outputs hugeInt.elems[ hugeInt.size - 1 .. 0 ]
void output(ostream& outFile, HugeInt& hugeInt);

// a recursive function that outputs hugeInt.elems[ last .. 0 ]
void recursiveOutput(ostream& outFile, HugeInt& hugeInt, int last);

// returns true if and only if the specified huge integer is zero
bool isZero(HugeInt& hugeInt);

// return true if and only if hugeInt1 == hugeInt2
bool equal(HugeInt& hugeInt1, HugeInt& hugeInt2);

// a recursive function that returns true if and only if
// hugeInt1.elems[ 0 .. last ] == hugeInt2.elems[ 0 .. last ]
// provided that hugeInt1.size == hugeInt2.size
bool recursiveEqual(HugeInt& hugeInt1, HugeInt& hugeInt2, int last);

// return true if and only if hugeInt1 < hugeInt2
bool less(HugeInt& hugeInt1, HugeInt& hugeInt2);

// a recursive function that returns true if and only if hugeInt1 < hugeInt2
// provided that hugeInt1.size == hugeInt2.size
bool recursiveLess(HugeInt& hugeInt1, HugeInt& hugeInt2, int last);

// sum = addend + adder
void addition(HugeInt& addend, HugeInt& adder, HugeInt& sum);

// difference = minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void subtraction(HugeInt& minuend,
    HugeInt& subtrahend, HugeInt& difference);

// product = multiplicand * multiplier
void multiplication(HugeInt& multiplicand,
    HugeInt& multiplier, HugeInt& product);

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that the divisor is not equal to 0
void division(HugeInt& dividend, HugeInt& divisor,
    HugeInt& quotient, HugeInt& remainder);

// hugeInt2 = hugeInt1; assignment
void assign(HugeInt& hugeInt1, HugeInt& hugeInt2);

// hugeInt /= 10
void divideByTen(HugeInt& hugeInt);

void reset(HugeInt& hugeInt);

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

    HugeInt hugeInt1;
    HugeInt hugeInt2;
    HugeInt hugeInt3;
    HugeInt hugeInt4;

    for (int i = 0; i < numTestCases; i++)
    {
        input(inFile, hugeInt1);
        input(inFile, hugeInt2);
        perform(cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4);
        perform(outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4);
        reset(hugeInt1);
        reset(hugeInt2);
    }

    delete[] hugeInt1.elems;
    delete[] hugeInt2.elems;
    delete[] hugeInt3.elems;
    delete[] hugeInt4.elems;

    inFile.close();
    outFile.close();

    system("pause");
}

// enable user to input a positive huge integer
void input(istream& inFile, HugeInt& hugeInt)
{
    char numericString[arraySize];

    inFile >> numericString;

    hugeInt.size = strlen(numericString);
    delete[] hugeInt.elems;
    hugeInt.elems = new int[hugeInt.size];
    for (int i = 0; i < hugeInt.size; i++)
        hugeInt.elems[i] = numericString[hugeInt.size - i - 1] - '0';
}

// perform addition, subtraction, multiplication and division
void perform(ostream& outFile, HugeInt& hugeInt1, HugeInt& hugeInt2,
    HugeInt& hugeInt3, HugeInt& hugeInt4)
{
    output(outFile, hugeInt1);
    output(outFile, hugeInt2);

    addition(hugeInt1, hugeInt2, hugeInt3); // hugeInt3 = hugeInt1 + hugeInt2
    output(outFile, hugeInt3);
    reset(hugeInt3);

    if (less(hugeInt1, hugeInt2))
    {
        outFile << '-';
        subtraction(hugeInt2, hugeInt1, hugeInt3); // hugeInt3 = hugeInt2 - hugeInt1
        output(outFile, hugeInt3);
    }
    else
    {
        subtraction(hugeInt1, hugeInt2, hugeInt3); // hugeInt3 = hugeInt1 - hugeInt2
        output(outFile, hugeInt3);
    }
    reset(hugeInt3);

    multiplication(hugeInt1, hugeInt2, hugeInt3); // hugeInt3 = hugeInt1 * hugeInt2
    output(outFile, hugeInt3);
    reset(hugeInt3);

    if (isZero(hugeInt2))
    {
        outFile << "DivideByZero!\n";
        outFile << "DivideByZero!\n";
    }
    else
    {
        // hugeInt3 = hugeInt1 / hugeInt2;   hugeInt4 = hugeInt1 % hugeInt2
        division(hugeInt1, hugeInt2, hugeInt3, hugeInt4);
        output(outFile, hugeInt3);
        output(outFile, hugeInt4);
        reset(hugeInt3);
        reset(hugeInt4);
    }

    outFile << endl;
}

// outputs hugeInt.elems[ hugeInt.size - 1 .. 0 ]
void output(ostream& outFile, HugeInt& hugeInt)
{
    recursiveOutput(outFile, hugeInt, hugeInt.size - 1);
    outFile << endl;
}

// a recursive function that outputs hugeInt.elems[ last .. 0 ]
void recursiveOutput(ostream& outFile, HugeInt& hugeInt, int last)
{
    if (last >= 0) //若last>=0
    {
        outFile << hugeInt.elems[last]; //則印出該編號陣列內的數
        recursiveOutput(outFile, hugeInt, last - 1); //並呼叫函式來印下一位的數
    }
    return;
}

// returns true if and only if the specified huge integer is zero
bool isZero(HugeInt& hugeInt)
{
    if (hugeInt.size == 1 && hugeInt.elems[0] == 0)
        return true;
    return false;
}

// return true if and only if hugeInt1 == hugeInt2
bool equal(HugeInt& hugeInt1, HugeInt& hugeInt2)
{
    if (hugeInt1.size != hugeInt2.size)
        return false;

    return recursiveEqual(hugeInt1, hugeInt2, hugeInt1.size - 1);
}

// a recursive function that returns true if and only if
// hugeInt1.elems[ 0 .. last ] == hugeInt2.elems[ 0 .. last ]
// provided that hugeInt1.size == hugeInt2.size
bool recursiveEqual(HugeInt& hugeInt1, HugeInt& hugeInt2, int last)
{
    if (hugeInt1.elems[last] == hugeInt2.elems[last]) //若該位數的數相等
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
bool less(HugeInt& hugeInt1, HugeInt& hugeInt2)
{
    if (hugeInt1.size < hugeInt2.size)
        return true;
    if (hugeInt1.size > hugeInt2.size)
        return false;

    return recursiveLess(hugeInt1, hugeInt2, hugeInt1.size - 1);
}

// a recursive function that returns true if and only if
// hugeInt1.elems[ 0 .. last ] < hugeInt2.elems[ 0 .. last ]
// provided that hugeInt1.size == hugeInt2.size
bool recursiveLess(HugeInt& hugeInt1, HugeInt& hugeInt2, int last)
{
    if (hugeInt1.elems[last] == hugeInt2.elems[last]) //若該位數的數相等
    {
        if (last == 0) //若檢查到最後一位數也相等
        {
            return false; //則此2數相等，回傳false
        }
        return recursiveLess(hugeInt1, hugeInt2, last - 1); //則呼叫函式檢查下一位數
    }
    else if (hugeInt1.elems[last] > hugeInt2.elems[last]) //若在該位數hugeInt1>hugeInt2
    {
        return false; //則回傳false
    }
    else if (hugeInt1.elems[last] < hugeInt2.elems[last]) //若在該位數hugeInt1<hugeInt2
    {
        return true; //則回傳true
    }
}

// sum = addend + adder
void addition(HugeInt& addend, HugeInt& adder, HugeInt& sum)
{
    sum.size = (addend.size >= adder.size) ? addend.size + 1 : adder.size + 1;

    delete[] sum.elems;
    sum.elems = new int[sum.size]();

    for (int i = 0; i < addend.size; i++)
        sum.elems[i] = addend.elems[i];

    for (int i = 0; i < adder.size; i++)
        sum.elems[i] += adder.elems[i];

    for (int i = 0; i < sum.size - 1; i++)
        if (sum.elems[i] > 9) // determine whether to carry a 1
        {
            sum.elems[i] -= 10; // reduce to 0-9
            sum.elems[i + 1]++;
        }

    if (sum.elems[sum.size - 1] == 0)
        sum.size--;
}

// difference = minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void subtraction(HugeInt& minuend,
    HugeInt& subtrahend, HugeInt& difference)
{
    int x; //代表運算時當前的位數
    difference.size = minuend.size; //設差值的位數=被減數的位數
    delete[] difference.elems; //釋放在struct裡對應的記憶體
    difference.elems = new int[difference.size](); //重新配置動態陣列
    if (equal(minuend, subtrahend) == true) //若被減數和減數相同
    {
        difference.size = 1; //則差的位數=1
        difference.elems[0] = 0; //其值=0
        return;
    }
    for (x = 0; x < subtrahend.size; x++)
    {
        difference.elems[x] = minuend.elems[x] - subtrahend.elems[x]; //將相減後的值存入difference
    }
    while (x < minuend.size) //若相減後被減數還有剩餘
    {
        difference.elems[x] = minuend.elems[x]; //則把剩餘的數存入difference
        x++;
    }
    for (int y = 0; y < difference.size - 1; y++) //借位系統
    {
        if (difference.elems[y] < 0) //若該號陣列裡的值為負
        {
            difference.elems[y + 1]--; //則向前借一位
            difference.elems[y] += 10; //該負數+10
        }
    }
    while (difference.elems[difference.size - 1] == 0) //若差值的最高編號陣列內的數=0 (即當時所設的size高估)
    {
        difference.size--; //則size-1直到符合結果的位數
    }
}

// product = multiplicand * multiplier
void multiplication(HugeInt& multiplicand,
    HugeInt& multiplier, HugeInt& product)
{
    int a; //代表當前乘數正在運算的位數
    int b; //代表當前被乘數正在運算的位數
    product.size = multiplicand.size + multiplier.size; //設積的位數=被乘數的位數+乘數的位數
    delete[] product.elems; //釋放在struct裡對應的記憶體
    product.elems = new int[product.size](); //重新配置動態陣列
    if (multiplicand.elems[multiplicand.size - 1] == 0 || multiplier.elems[multiplier.size - 1] == 0) //若被乘數或乘數其中一個的值=0
    {
        product.size = 1; //則積的位數=1
        product.elems[product.size - 1] = 0; //其值=0
        return;
    }
    for (a = 0; a < multiplier.size; a++)
    {
        for (b = 0; b < multiplicand.size; b++)
        {
            product.elems[a + b] += multiplicand.elems[b] * multiplier.elems[a]; //將當前的乘積依序填入
        }
    }
    for (int c = 0; c < product.size - 1; c++) //進位系統
    {
        while (product.elems[c] > 9) //若當前該號陣列內的值>9
        {
            product.elems[c] -= 10; //則該值-10
            product.elems[c + 1]++; //向前進一位
        }
    }
    if (product.elems[product.size - 1] == 0) //若乘積最高編號陣列內的數=0 (即當時所設的size高估)
    {
        product.size--; //則size-1
    }
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that the divisor is not equal to 0
void division(HugeInt& dividend, HugeInt& divisor,
    HugeInt& quotient, HugeInt& remainder)
{
    if (isZero(dividend))
    {
        reset(quotient);
        reset(remainder);
        return;
    }
    HugeInt buffer;
    buffer.size = dividend.size; //設(偽)除數的空間數=被除數的空間數
    delete[]buffer.elems; //釋放在struct裡對應的記憶體
    buffer.elems = new int[buffer.size](); //重新配置動態陣列
    remainder.size = dividend.size; //令初始餘數空間數=被除數空間數
    quotient.size = dividend.size - divisor.size; //商的空間數=被除數的空間數-除數的空間數

    delete[] remainder.elems; //釋放在struct裡對應的記憶體
    remainder.elems = new int[remainder.size](); //重新配置動態陣列
    for (int x = 0; x < dividend.size; x++) //將被除數陣列內的數複製給餘數
    {
        remainder.elems[x] = dividend.elems[x];
    }
    if (less(dividend, divisor) == true) //若被除數<除數
    {
        quotient.size = 1; //則商的位數=1
        quotient.elems[quotient.size - 1] = 0; //且該位置的數必為0
        return;
    }
    for (int y = divisor.size - 1; y >= 0; y--) //將除數在陣列中做移位
    {
        buffer.elems[buffer.size - 1] = divisor.elems[y];
        buffer.size--;
    }
    buffer.size = dividend.size; //重置buffer.size的位數
    if (less(dividend, buffer) == false) //若被除數>=(偽)除數
    {
        quotient.size++; //商的空間數+1做修正
    }
    delete[] quotient.elems; //釋放在struct裡對應的記憶體
    quotient.elems = new int[quotient.size](); //重新配置動態陣列
    int quotientS = quotient.size; //代替quotient.size在之後做運算(quotientS的值會變)
    while (buffer.size >= divisor.size) //<---從此開始做除法運算
    {
        while (less(remainder, buffer) == true) //若(偽)除數>當前的餘數
        {
            if ( less(buffer, dividend) == true) //若被除數>(偽)除數
            {
                quotientS--; //將size-1的條件設為：在最一開始做除法時不能減少其空間數
            }
            divideByTen(buffer); //則(偽)除數向右減少一位
        }
        HugeInt temp;
        temp.size = remainder.size; //暫存值的功用為存取減過的餘數，故設其空間數=當前餘數的空間數
        delete[]temp.elems; //釋放在struct裡對應的記憶體
        temp.elems = new int[temp.size](); //重新配置動態陣列
        subtraction(remainder, buffer, temp); //相減，並將其值存入暫存值
        quotient.elems[quotientS - 1]++; //商當前位數內的值+1
        remainder.size = temp.size; //將暫存值所存的空間數還給餘數
        for (int z = 0; z < temp.size; z++) //將暫存值內所存的值還給餘數
        {
            remainder.elems[z] = temp.elems[z];
        }
        delete[]temp.elems; //釋放暫存值的記憶體
        if (buffer.size == divisor.size) //若(偽)除數空間數=原本的除數空間數
        {
            if (less(remainder, divisor) == true) //若除數比餘數大
            {
                delete[]buffer.elems; //釋放記憶體
                return; //則運算完成，結束函式
            }
        }
    }
}

// hugeInt2 = hugeInt1; assignment
void assign(HugeInt& hugeInt1, HugeInt& hugeInt2)
{
    hugeInt2.size = hugeInt1.size;
    delete[] hugeInt2.elems;
    hugeInt2.elems = new int[hugeInt2.size];
    for (int i = 0; i < hugeInt2.size; i++)
        hugeInt2.elems[i] = hugeInt1.elems[i];
}

// hugeInt /= 10
void divideByTen(HugeInt& hugeInt)
{
    if (hugeInt.size == 1)
        hugeInt.elems[0] = 0;
    else
    {
        for (int i = 1; i < hugeInt.size; i++)
            hugeInt.elems[i - 1] = hugeInt.elems[i];

        hugeInt.size--;
        hugeInt.elems[hugeInt.size] = 0;
    }
}

void reset(HugeInt& hugeInt)
{
    hugeInt.size = 1;
    delete[] hugeInt.elems;
    hugeInt.elems = new int[1]();
}
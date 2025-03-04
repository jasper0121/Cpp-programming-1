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

// HugeInt class definition
class HugeInt
{
public:
    // enable user to input a positive huge integer
    void input(istream& inFile);

    // outputs elems[ hugeInt.size - 1 .. 0 ]
    void output(ostream& outFile);

    // a recursive function that outputs elems[ last .. 0 ]
    void recursiveOutput(ostream& outFile, int last);

    // returns true if and only if the specified huge integer is zero
    bool isZero();

    // return true if and only if current object == hugeInt2
    bool equal(HugeInt& hugeInt2);

    // a recursive function that returns true if and only if
    // elems[ 0 .. last ] == hugeInt2.elems[ 0 .. last ]
    // provided that size == hugeInt2.size
    bool recursiveEqual(HugeInt& hugeInt2, int last);

    // return true if and only if current object < hugeInt2
    bool less(HugeInt& hugeInt2);

    // a recursive function that returns true if and only if
    // elems[ 0 .. last ] < hugeInt2.elems[ 0 .. last ]
    // provided that size == hugeInt2.size
    bool recursiveLess(HugeInt& hugeInt2, int last);

    // request the current object to reduce its array to fit its size
    void shrink_to_fit();

    // sum = current object + adder
    void addition(HugeInt& adder, HugeInt& sum);

    // difference = current object - subtrahend
    // provided that the current object is greater than or equal to the subtrahend
    void subtraction(HugeInt& subtrahend, HugeInt& difference);

    // product = current object * multiplier
    void multiplication(HugeInt& multiplier, HugeInt& product);

    // quotient = current object / divisor; remainder = current object % divisor
    // provided that the divisor is not equal to 0
    void division(HugeInt& divisor, HugeInt& quotient, HugeInt& remainder);

    // left = current object; assignment
    void assign(HugeInt& left);

    // current object /= 10
    void divideByTen();

    void reset();

    int size = 1; // the number of digits of the integer; it can never be zero
    int* elems = new int[1]();  // used to store a nonnegative integer, one digit per element
}; // end class HugeInt


// enable user to input a positive huge integer
void HugeInt::input(istream& inFile)
{
    char numericString[200];

    inFile >> numericString;

    size = strlen(numericString);
    delete[] elems;
    elems = new int[size];
    for (int i = 0; i < size; i++)
        elems[i] = numericString[size - i - 1] - '0';
}

// output the specified huge integer
void HugeInt::output(ostream& outFile)
{
    recursiveOutput(outFile, size - 1);
    outFile << endl;
}

// a recursive function that outputs hugeInt.elems[ last .. 0 ]
void HugeInt::recursiveOutput(ostream& outFile, int last)
{
    if (last >= 0) //若last>=0
    {
        outFile << elems[last]; //則印出該編號陣列內的數
        recursiveOutput(outFile, last - 1); //並呼叫函式來印下一位的數
    }
    return;
}

// returns true if and only if the specified huge integer is zero
bool HugeInt::isZero()
{
    if (size == 1 && elems[0] == 0)
        return true;
    return false;
}

// return true if and only if current object == hugeInt2
bool HugeInt::equal(HugeInt& hugeInt2)
{
    if (size != hugeInt2.size)
        return false;

    return recursiveEqual(hugeInt2, size - 1);
}

// a recursive function that returns true if and only if
// elems[ 0 .. last ] == hugeInt2.elems[ 0 .. last ]
// provided that size == hugeInt2.size
bool HugeInt::recursiveEqual(HugeInt& hugeInt2, int last)
{
    if (elems[last] == hugeInt2.elems[last]) //若該位數的數相等
    {
        if (last == 0) //若2者最後一位的數也相同
        {
            return true; //則此2數必相同，故回傳true
        }
        return recursiveEqual(hugeInt2, last - 1); //則呼叫函式檢查下一位數是否也相等
    }
    else
    {
        return false; //否則回傳false
    }
}

// returns true if and only if current object < hugeInt2
bool HugeInt::less(HugeInt& hugeInt2)
{
    if (size < hugeInt2.size)
        return true;
    if (size > hugeInt2.size)
        return false;

    return recursiveLess(hugeInt2, size - 1);
}

// a recursive function that returns true if and only if
// elems[ 0 .. last ] < hugeInt2.elems[ 0 .. last ]
// provided that size == hugeInt2.size
bool HugeInt::recursiveLess(HugeInt& hugeInt2, int last)
{
    if (elems[last] == hugeInt2.elems[last]) //若該位數的數相等
    {
        if (last == 0) //若檢查到最後一位數也相等
        {
            return false; //則此2數相等，回傳false
        }
        return recursiveLess(hugeInt2, last - 1); //則呼叫函式檢查下一位數
    }
    else if (elems[last] > hugeInt2.elems[last]) //若在該位數current object>hugeInt2
    {
        return false; //則回傳false
    }
    else if (elems[last] < hugeInt2.elems[last]) //若在該位數current object<hugeInt2
    {
        return true; //則回傳true
    }
}

// request the current object to reduce its array to fit its size
void HugeInt::shrink_to_fit()
{
    int* buffer = new int[size];
    for (int i = 0; i < size; i++)
        buffer[i] = elems[i];
    delete[] elems;
    elems = buffer;
}

// sum = current object + adder
void HugeInt::addition(HugeInt& adder, HugeInt& sum)
{
    sum.size = (size >= adder.size) ? size + 1 : adder.size + 1;

    delete[] sum.elems;
    sum.elems = new int[sum.size]();

    for (int i = 0; i < size; i++)
        sum.elems[i] = elems[i];

    for (int i = 0; i < adder.size; i++)
        sum.elems[i] += adder.elems[i];

    for (int i = 0; i < sum.size - 1; i++)
        if (sum.elems[i] > 9) // determine whether to carry a 1
        {
            sum.elems[i] -= 10; // reduce to 0-9
            sum.elems[i + 1]++;
        }

    if (sum.elems[sum.size - 1] == 0)
    {
        sum.size--;
        sum.shrink_to_fit();
    }
}

// difference = current object - subtrahend
// provided that the current object is greater than or equal to the subtrahend
void HugeInt::subtraction(HugeInt& subtrahend, HugeInt& difference)
{
    int x; //代表運算時當前的位數
    difference.size = size; //設差值的位數=被減數(current object)的位數
    delete[] difference.elems; //釋放在class裡對應的記憶體
    difference.elems = new int[difference.size](); //重新配置動態陣列
    if (equal(subtrahend) == true) //若被減數(current object)和減數相同
    {
        difference.size = 1; //則差的位數=1
        difference.elems[0] = 0; //其值=0
        return;
    }
    for (x = 0; x < subtrahend.size; x++)
    {
        difference.elems[x] = elems[x] - subtrahend.elems[x]; //將相減後的值存入difference
    }
    while (x < size) //若相減後被減數(current object)還有剩餘
    {
        difference.elems[x] = elems[x]; //則把剩餘的數存入difference
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
        difference.shrink_to_fit();
    }
}

// product = current object * multiplier
void HugeInt::multiplication(HugeInt& multiplier, HugeInt& product)
{
    product.size = size + multiplier.size; //設積的位數=被乘數(current object)的位數+乘數的位數
    delete[] product.elems; //釋放在class裡對應的記憶體
    product.elems = new int[product.size](); //重新配置動態陣列
    if (elems[size - 1] == 0 || multiplier.elems[multiplier.size - 1] == 0) //若被乘數(current object)或乘數其中一個的值=0
    {
        product.size = 1; //則積的位數=1
        product.elems[product.size - 1] = 0; //其值=0
        return;
    }
    for (int a = 0; a < multiplier.size; a++) //代表當前乘數正在運算的位數
    {
        for (int b = 0; b < size; b++) //代表當前被乘數(current object)正在運算的位數
        {
            product.elems[a + b] += elems[b] * multiplier.elems[a]; //將當前的乘積依序填入
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
        product.shrink_to_fit();
    }
}

// quotient = current object / divisor; remainder = current object % divisor
// provided that the divisor is not equal to 0
void HugeInt::division(HugeInt& divisor, HugeInt& quotient, HugeInt& remainder)
{
    if (isZero())
    {
        quotient.reset();
        remainder.reset();
        return;
    }
    HugeInt buffer;
    buffer.size = size; //設(偽)除數的空間數=被除數(current object)的空間數
    delete[]buffer.elems; //釋放在class裡對應的記憶體
    buffer.elems = new int[buffer.size](); //重新配置動態陣列
    remainder.size = size; //令初始餘數空間數=被除數(current object)空間數
    quotient.size = size - divisor.size; //商的空間數=被除數(current object)的空間數-除數的空間數

    delete[] remainder.elems; //釋放在class裡對應的記憶體
    remainder.elems = new int[remainder.size](); //重新配置動態陣列
    for (int x = 0; x < size; x++) //將被除數(current object)陣列內的數複製給餘數
    {
        remainder.elems[x] = elems[x];
    }
    if (less(divisor) == true) //若被除數(current object)<除數
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
    buffer.size = size; //重置buffer.size的位數
    if (less(buffer) == false) //若被除數(current object)>=(偽)除數
    {
        quotient.size++; //商的空間數+1做修正
    }
    delete[] quotient.elems; //釋放在class裡對應的記憶體
    quotient.elems = new int[quotient.size](); //重新配置動態陣列
    int quotientS = quotient.size; //代替quotient.size在之後做運算(quotientS的值會變)
    while (buffer.size >= divisor.size) //<---從此開始做除法運算
    {
        while (remainder.less(buffer) == true) //若當前的餘數(current object)<(偽)除數
        {
            if (less(buffer) == false) //若被除數(current object)>(偽)除數
            {
                quotientS--; //若一開始運算的(偽)除數>被除數，則此size不減
            }
            buffer.divideByTen(); //則(偽)除數(current object)向右減少一位
        }
        HugeInt temp;
        temp.size = remainder.size; //暫存值的功用為存取減過的餘數，故設其空間數=當前餘數的空間數
        delete[]temp.elems; //釋放在class裡對應的記憶體
        temp.elems = new int[temp.size](); //重新配置動態陣列
        remainder.subtraction(buffer, temp); //相減，並將其值存入暫存值
        quotient.elems[quotientS - 1]++; //商當前位數內的值+1
        remainder.size = temp.size; //將暫存值所存的空間數還給餘數
        delete[]remainder.elems; //釋放舊的remainder.elems
        remainder = temp; //將temp所存的地址給remainder，讓remainder指向temp的陣列
        if (buffer.size == divisor.size) //若(偽)除數空間數=原本的除數空間數
        {
            if (remainder.less(divisor) == true) //若除數比餘數(current object)大
            {
                delete[]buffer.elems; //釋放記憶體
                return; //則運算完成，結束函式
            }
        }
    }
}

// left = current object; assignment
void HugeInt::assign(HugeInt& left)
{
    left.size = size;
    delete[] left.elems;
    left.elems = new int[left.size];
    for (int i = 0; i < left.size; i++)
        left.elems[i] = elems[i];
}

// current object /= 10
void HugeInt::divideByTen()
{
    if (size == 1)
        elems[0] = 0;
    else
    {
        for (int i = 1; i < size; i++)
            elems[i - 1] = elems[i];

        size--;
        elems[size] = 0;
        shrink_to_fit();
    }
}

void HugeInt::reset()
{
    size = 1;
    delete[] elems;
    elems = new int[1]();
}


void perform(ostream& outFile, HugeInt& hugeInt1, HugeInt& hugeInt2,
    HugeInt& hugeInt3, HugeInt& hugeInt4)
{
    hugeInt1.output(outFile);
    hugeInt2.output(outFile);

    hugeInt1.addition(hugeInt2, hugeInt3); // hugeInt3 = hugeInt1 + hugeInt2
    hugeInt3.output(outFile);
    hugeInt3.reset();

    if (hugeInt1.less(hugeInt2))
    {
        outFile << '-';
        hugeInt2.subtraction(hugeInt1, hugeInt3); // hugeInt3 = hugeInt2 - hugeInt1
        hugeInt3.output(outFile);
    }
    else
    {
        hugeInt1.subtraction(hugeInt2, hugeInt3); // hugeInt3 = hugeInt1 - hugeInt2
        hugeInt3.output(outFile);
    }
    hugeInt3.reset();

    hugeInt1.multiplication(hugeInt2, hugeInt3); // hugeInt3 = hugeInt1 * hugeInt2
    hugeInt3.output(outFile);
    hugeInt3.reset();

    if (hugeInt2.isZero())
    {
        outFile << "DivideByZero!\n";
        outFile << "DivideByZero!\n";
    }
    else
    {
        // hugeInt3 = hugeInt1 / hugeInt2; // hugeInt4 = hugeInt1 % hugeInt2
        hugeInt1.division(hugeInt2, hugeInt3, hugeInt4);
        hugeInt3.output(outFile);
        hugeInt4.output(outFile);
        hugeInt3.reset();
        hugeInt4.reset();
    }

    outFile << endl;
}

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
        hugeInt1.input(inFile);
        hugeInt2.input(inFile);
        perform(cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4);
        perform(outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4);
        hugeInt1.reset();
        hugeInt2.reset();
    }

    delete[] hugeInt1.elems;
    delete[] hugeInt2.elems;
    delete[] hugeInt3.elems;
    delete[] hugeInt4.elems;

    inFile.close();
    outFile.close();

    system("pause");
}
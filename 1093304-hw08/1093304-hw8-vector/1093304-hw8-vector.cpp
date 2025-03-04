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

#include <vector>
using std::vector;

const unsigned int numTestCases = 22;
const unsigned int arraySize = 200;

// enable user to input a positive huge integer
void input(istream& inFile, vector< int >& hugeInt);

// performs addition, subtraction, multiplication, division and modulus
void perform(ostream& outFile, vector< int >& hugeInt1, vector< int >& hugeInt2);

// outputs hugeInt[ hugeInt.size() - 1 .. 0 ]
void output(ostream& outFile, vector< int >& hugeInt);

// a recursive function that outputs hugeInt[ last .. 0 ]
void recursiveOutput(ostream& outFile, vector< int >& hugeInt, size_t last);

// returns true if and only if the specified huge integer is zero
bool isZero(vector< int >& hugeInt);

// returns true if and only if hugeInt1 == hugeInt2
bool equal(vector< int >& hugeInt1, vector< int >& hugeInt2);

// a recursive function that returns true if and only if
// hugeInt1[ 0 .. last ] == hugeInt2[ 0 .. last ]
// provided that hugeInt1.size() == hugeInt2.size()
bool recursiveEqual(vector< int >& hugeInt1, vector< int >& hugeInt2, size_t last);

// returns true if and only if hugeInt1 < hugeInt2
bool less(vector< int >& hugeInt1, vector< int >& hugeInt2);

// a recursive function that returns true if and only if
// hugeInt1[ 0 .. last ] < hugeInt2[ 0 .. last ]
// provided that hugeInt1.size() == hugeInt2.size()
bool recursiveLess(vector< int >& hugeInt1, vector< int >& hugeInt2, size_t last);

// returns addend + adder
vector< int > addition(vector< int >& addend, vector< int >& adder);

// returns minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
vector< int > subtraction(vector< int >& minuend, vector< int >& subtrahend);

// returns multiplicand * multiplier
vector< int > multiplication(vector< int >& multiplicand, vector< int >& multiplier);

// returns dividend / divisor
// provided that the divisor is not equal to 0
vector< int > division(vector< int >& dividend, vector< int >& divisor);

// returns dividend % divisor
// provided that the divisor is not equal to 0
vector< int > modulus(vector< int >& dividend, vector< int >& divisor);

// hugeInt /= 10
void divideByTen(vector< int >& hugeInt);

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

    for (int i = 0; i < numTestCases; i++)
    {
        vector< int > hugeInt1;
        vector< int > hugeInt2;
        input(inFile, hugeInt1);
        input(inFile, hugeInt2);
        perform(cout, hugeInt1, hugeInt2);
        perform(outFile, hugeInt1, hugeInt2);
    }

    inFile.close();
    outFile.close();

    system("pause");
}

// enable user to input a positive huge integer
void input(istream& inFile, vector< int >& hugeInt)
{
    char numericString[arraySize];

    inFile >> numericString;

    hugeInt.resize(strlen(numericString));
    for (size_t i = 0; i < hugeInt.size(); i++)
        hugeInt[hugeInt.size() - i - 1] = numericString[i] - '0';
}

// performs addition, subtraction, multiplication and division
void perform(ostream& outFile, vector< int >& hugeInt1, vector< int >& hugeInt2)
{
    output(outFile, hugeInt1);
    output(outFile, hugeInt2);

    vector< int > hugeInt3 = addition(hugeInt1, hugeInt2); // hugeInt3 = hugeInt1 + hugeInt2
    output(outFile, hugeInt3);

    if (less(hugeInt1, hugeInt2))
    {
        outFile << '-';
        hugeInt3 = subtraction(hugeInt2, hugeInt1); // hugeInt3 = hugeInt2 - hugeInt1
        output(outFile, hugeInt3);
    }
    else
    {
        hugeInt3 = subtraction(hugeInt1, hugeInt2); // hugeInt3 = hugeInt1 - hugeInt2
        output(outFile, hugeInt3);
    }

    hugeInt3 = multiplication(hugeInt1, hugeInt2); // hugeInt3 = hugeInt1 * hugeInt2
    output(outFile, hugeInt3);

    if (isZero(hugeInt2))
    {
        outFile << "DivideByZero!\n";
        outFile << "DivideByZero!\n";
    }
    else
    {
        hugeInt3 = division(hugeInt1, hugeInt2); // hugeInt3 = hugeInt1 / hugeInt2
        output(outFile, hugeInt3);

        hugeInt3 = modulus(hugeInt1, hugeInt2); // hugeInt3 = hugeInt1 % hugeInt2
        output(outFile, hugeInt3);
    }

    outFile << endl;
}

// outputs hugeInt[ hugeInt.size() - 1 .. 0 ]
void output(ostream& outFile, vector< int >& hugeInt)
{
    recursiveOutput(outFile, hugeInt, hugeInt.size() - 1);
    outFile << endl;
}

// a recursive function that outputs hugeInt[ last .. 0 ]
void recursiveOutput(ostream& outFile, vector< int >& hugeInt, size_t last)
{
    outFile << hugeInt[last]; //印出該編號陣列內的數
    if (last > 0) //last的值不能為負(因型別為size_t)
    {
        recursiveOutput(outFile, hugeInt, last - 1); //呼叫函式來印下一位的數
    }
    return;
}

// returns true if and only if the specified huge integer is zero
bool isZero(vector< int >& hugeInt)
{
    for (size_t i = 0; i < hugeInt.size(); i++)
        if (hugeInt[i] != 0)
            return false;
    return true;
}

// returns true if and only if hugeInt1 == hugeInt2
bool equal(vector< int >& hugeInt1, vector< int >& hugeInt2)
{
    if (hugeInt1.size() != hugeInt2.size())
        return false;

    return recursiveEqual(hugeInt1, hugeInt2, hugeInt1.size() - 1);
}

// a recursive function that returns true if and only if
// hugeInt1[ 0 .. last ] == hugeInt2[ 0 .. last ]
// provided that hugeInt1.size() == hugeInt2.size()
bool recursiveEqual(vector< int >& hugeInt1, vector< int >& hugeInt2, size_t last)
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
bool less(vector< int >& hugeInt1, vector< int >& hugeInt2)
{
    if (hugeInt1.size() < hugeInt2.size())
        return true;
    if (hugeInt1.size() > hugeInt2.size())
        return false;

    return recursiveLess(hugeInt1, hugeInt2, hugeInt1.size() - 1);
}

// a recursive function that returns true if and only if
// hugeInt1[ 0 .. last ] < hugeInt2[ 0 .. last ]
// provided that hugeInt1.size() == hugeInt2.size()
bool recursiveLess(vector< int >& hugeInt1, vector< int >& hugeInt2, size_t last)
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

// returns addend + adder
vector< int > addition(vector< int >& addend, vector< int >& adder)
{
    size_t sumSize = (addend.size() >= adder.size()) ? addend.size() + 1 : adder.size() + 1;
    vector< int > sum(sumSize);

    for (size_t i = 0; i < addend.size(); i++)
        sum[i] = addend[i];

    for (size_t i = 0; i < adder.size(); i++)
        sum[i] += adder[i];

    for (size_t i = 0; i < sum.size() - 1; i++)
        if (sum[i] > 9) // determine whether to carry a 1
        {
            sum[i] -= 10; // reduce to 0-9
            sum[i + 1]++;
        }

    if (sum[sum.size() - 1] == 0)
        sum.pop_back();

    return sum;
}

// returns minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
vector< int > subtraction(vector< int >& minuend, vector< int >& subtrahend)
{
    if (equal(minuend, subtrahend))
    {
        vector< int > zero(1);
        return zero;
    }
    vector< int > difference(minuend);
    for (size_t x = 0; x < subtrahend.size(); x++) //代表運算時當前的位數
    {
        difference[x] -= subtrahend[x]; //將相減後的值存入difference
    }
    for (size_t y = 0; y < difference.size() - 1; y++) //借位系統
    {
        if (difference[y] < 0) //若該號陣列裡的值為負
        {
            difference[y + 1]--; //則向前借一位
            difference[y] += 10; //該負數+10
        }
    }
    while (difference[difference.size() - 1] == 0) //若差值的最高編號陣列內的數=0 (即當時所設的size高估)
    {
        difference.pop_back(); //則size-1直到符合結果的位數
    }
    return difference;
}

// returns multiplicand * multiplier
vector< int > multiplication(vector< int >& multiplicand, vector< int >& multiplier)
{
    if (isZero(multiplicand) || isZero(multiplier))
    {
        vector< int > zero(1);
        return zero;
    }
    vector< int > product(multiplicand.size() + multiplier.size());
    for (size_t a = 0; a < multiplier.size(); a++) //代表當前乘數正在運算的位數
    {
        for (size_t b = 0; b < multiplicand.size(); b++) //代表當前被乘數正在運算的位數
        {
            product[a + b] += multiplicand[b] * multiplier[a]; //將當前的乘積依序填入
        }
    }
    for (size_t c = 0; c < product.size() - 1; c++) //進位系統
    {
        while (product[c] > 9) //若當前該號陣列內的值>9
        {
            product[c] -= 10; //則該值-10
            product[c + 1]++; //向前進一位
        }
    }
    if (product[product.size() - 1] == 0) //若乘積最高編號陣列內的數=0 (即當時所設的size高估)
    {
        product.pop_back(); //則size-1
    }
    return product;
}

// returns dividend / divisor
// provided that the divisor is not equal to 0
vector< int > division(vector< int >& dividend, vector< int >& divisor)
{
    if (isZero(dividend) || less(dividend, divisor))
    {
        vector< int > zero(1);
        return zero;
    }
    vector< int > remainder(dividend);
    vector< int > buffer(dividend.size());
    size_t bufferSize = buffer.size(); //作為buffer.size()的計數器
    size_t quotientSize = dividend.size() - divisor.size(); //商的空間數=被除數的空間數-除數的空間數
    for (int y = divisor.size() - 1; y >= 0; y--) //將除數在陣列中做移位
    {
        buffer[bufferSize - 1] = divisor[y];
        bufferSize--;
    }
    if (less(dividend, buffer) == false) //若被除數>=(偽)除數
    {
        quotientSize++; //商的空間數+1做修正
    }
    vector< int > quotient(quotientSize);
    while (buffer.size() >= divisor.size()) //<---從此開始做除法運算
    {
        while (less(remainder, buffer) == true) //若當前的餘數<(偽)除數
        {
            if (less(buffer, dividend) == true) //若(偽)除數<被除數
            {
                quotientSize--; //若一開始運算的(偽)除數>被除數，則此size不減
            }
            divideByTen(buffer); //則(偽)除數向右減少一位
        }
        remainder = subtraction(remainder, buffer); //相減，並將其值存入餘數
        quotient[quotientSize - 1]++; //商當前位數內的值+1
        if (buffer.size() == divisor.size()) //若(偽)除數空間數=原本的除數空間數
        {
            if (less(remainder, divisor) == true) //若除數比餘數大
            {
                return quotient; //則運算完成，結束函式
            }
        }
    }
}

// returns dividend % divisor
// provided that the divisor is not equal to 0
vector< int > modulus(vector< int >& dividend, vector< int >& divisor)
{
    vector< int > quotient = division(dividend, divisor);      // quotient = dividend / divisor
    vector< int > product = multiplication(quotient, divisor); // product = quotient * divisor
    vector< int > remainder = subtraction(dividend, product);  // remainder = dividend - product
    return remainder;
}

// hugeInt /= 10
void divideByTen(vector< int >& hugeInt)
{
    if (hugeInt.size() == 1)
        hugeInt[0] = 0;
    else
    {
        for (size_t i = 1; i < hugeInt.size(); i++)
            hugeInt[i - 1] = hugeInt[i];
        hugeInt[hugeInt.size() - 1] = 0;
        hugeInt.pop_back();
    }
}
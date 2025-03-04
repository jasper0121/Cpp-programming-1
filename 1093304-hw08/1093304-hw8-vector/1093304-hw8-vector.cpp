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
    outFile << hugeInt[last]; //�L�X�ӽs���}�C������
    if (last > 0) //last���Ȥ��ର�t(�]���O��size_t)
    {
        recursiveOutput(outFile, hugeInt, last - 1); //�I�s�禡�ӦL�U�@�쪺��
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
    if (hugeInt1[last] == hugeInt2[last]) //�Y�Ӧ�ƪ��Ƭ۵�
    {
        if (last == 0) //�Y2�̳̫�@�쪺�Ƥ]�ۦP
        {
            return true; //�h��2�ƥ��ۦP�A�G�^��true
        }
        return recursiveEqual(hugeInt1, hugeInt2, last - 1); //�h�I�s�禡�ˬd�U�@��ƬO�_�]�۵�
    }
    else
    {
        return false; //�_�h�^��false
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
    if (hugeInt1[last] == hugeInt2[last]) //�Y�Ӧ�ƪ��Ƭ۵�
    {
        if (last == 0) //�Y�ˬd��̫�@��Ƥ]�۵�
        {
            return false; //�h��2�Ƭ۵��A�^��false
        }
        return recursiveLess(hugeInt1, hugeInt2, last - 1); //�h�I�s�禡�ˬd�U�@���
    }
    else if (hugeInt1[last] > hugeInt2[last]) //�Y�b�Ӧ��hugeInt1>hugeInt2
    {
        return false; //�h�^��false
    }
    else if (hugeInt1[last] < hugeInt2[last]) //�Y�b�Ӧ��hugeInt1<hugeInt2
    {
        return true; //�h�^��true
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
    for (size_t x = 0; x < subtrahend.size(); x++) //�N��B��ɷ�e�����
    {
        difference[x] -= subtrahend[x]; //�N�۴�᪺�Ȧs�Jdifference
    }
    for (size_t y = 0; y < difference.size() - 1; y++) //�ɦ�t��
    {
        if (difference[y] < 0) //�Y�Ӹ��}�C�̪��Ȭ��t
        {
            difference[y + 1]--; //�h�V�e�ɤ@��
            difference[y] += 10; //�ӭt��+10
        }
    }
    while (difference[difference.size() - 1] == 0) //�Y�t�Ȫ��̰��s���}�C������=0 (�Y��ɩҳ]��size����)
    {
        difference.pop_back(); //�hsize-1����ŦX���G�����
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
    for (size_t a = 0; a < multiplier.size(); a++) //�N���e���ƥ��b�B�⪺���
    {
        for (size_t b = 0; b < multiplicand.size(); b++) //�N���e�Q���ƥ��b�B�⪺���
        {
            product[a + b] += multiplicand[b] * multiplier[a]; //�N��e�����n�̧Ƕ�J
        }
    }
    for (size_t c = 0; c < product.size() - 1; c++) //�i��t��
    {
        while (product[c] > 9) //�Y��e�Ӹ��}�C������>9
        {
            product[c] -= 10; //�h�ӭ�-10
            product[c + 1]++; //�V�e�i�@��
        }
    }
    if (product[product.size() - 1] == 0) //�Y���n�̰��s���}�C������=0 (�Y��ɩҳ]��size����)
    {
        product.pop_back(); //�hsize-1
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
    size_t bufferSize = buffer.size(); //�@��buffer.size()���p�ƾ�
    size_t quotientSize = dividend.size() - divisor.size(); //�Ӫ��Ŷ���=�Q���ƪ��Ŷ���-���ƪ��Ŷ���
    for (int y = divisor.size() - 1; y >= 0; y--) //�N���Ʀb�}�C��������
    {
        buffer[bufferSize - 1] = divisor[y];
        bufferSize--;
    }
    if (less(dividend, buffer) == false) //�Y�Q����>=(��)����
    {
        quotientSize++; //�Ӫ��Ŷ���+1���ץ�
    }
    vector< int > quotient(quotientSize);
    while (buffer.size() >= divisor.size()) //<---�q���}�l�����k�B��
    {
        while (less(remainder, buffer) == true) //�Y��e���l��<(��)����
        {
            if (less(buffer, dividend) == true) //�Y(��)����<�Q����
            {
                quotientSize--; //�Y�@�}�l�B�⪺(��)����>�Q���ơA�h��size����
            }
            divideByTen(buffer); //�h(��)���ƦV�k��֤@��
        }
        remainder = subtraction(remainder, buffer); //�۴�A�ñN��Ȧs�J�l��
        quotient[quotientSize - 1]++; //�ӷ�e��Ƥ�����+1
        if (buffer.size() == divisor.size()) //�Y(��)���ƪŶ���=�쥻�����ƪŶ���
        {
            if (less(remainder, divisor) == true) //�Y���Ƥ�l�Ƥj
            {
                return quotient; //�h�B�⧹���A�����禡
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
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
    if (last >= 0) //�Ylast>=0
    {
        outFile << hugeInt.elems[last]; //�h�L�X�ӽs���}�C������
        recursiveOutput(outFile, hugeInt, last - 1); //�éI�s�禡�ӦL�U�@�쪺��
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
    if (hugeInt1.elems[last] == hugeInt2.elems[last]) //�Y�Ӧ�ƪ��Ƭ۵�
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
    if (hugeInt1.elems[last] == hugeInt2.elems[last]) //�Y�Ӧ�ƪ��Ƭ۵�
    {
        if (last == 0) //�Y�ˬd��̫�@��Ƥ]�۵�
        {
            return false; //�h��2�Ƭ۵��A�^��false
        }
        return recursiveLess(hugeInt1, hugeInt2, last - 1); //�h�I�s�禡�ˬd�U�@���
    }
    else if (hugeInt1.elems[last] > hugeInt2.elems[last]) //�Y�b�Ӧ��hugeInt1>hugeInt2
    {
        return false; //�h�^��false
    }
    else if (hugeInt1.elems[last] < hugeInt2.elems[last]) //�Y�b�Ӧ��hugeInt1<hugeInt2
    {
        return true; //�h�^��true
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
    int x; //�N��B��ɷ�e�����
    difference.size = minuend.size; //�]�t�Ȫ����=�Q��ƪ����
    delete[] difference.elems; //����bstruct�̹������O����
    difference.elems = new int[difference.size](); //���s�t�m�ʺA�}�C
    if (equal(minuend, subtrahend) == true) //�Y�Q��ƩM��ƬۦP
    {
        difference.size = 1; //�h�t�����=1
        difference.elems[0] = 0; //���=0
        return;
    }
    for (x = 0; x < subtrahend.size; x++)
    {
        difference.elems[x] = minuend.elems[x] - subtrahend.elems[x]; //�N�۴�᪺�Ȧs�Jdifference
    }
    while (x < minuend.size) //�Y�۴��Q����٦��Ѿl
    {
        difference.elems[x] = minuend.elems[x]; //�h��Ѿl���Ʀs�Jdifference
        x++;
    }
    for (int y = 0; y < difference.size - 1; y++) //�ɦ�t��
    {
        if (difference.elems[y] < 0) //�Y�Ӹ��}�C�̪��Ȭ��t
        {
            difference.elems[y + 1]--; //�h�V�e�ɤ@��
            difference.elems[y] += 10; //�ӭt��+10
        }
    }
    while (difference.elems[difference.size - 1] == 0) //�Y�t�Ȫ��̰��s���}�C������=0 (�Y��ɩҳ]��size����)
    {
        difference.size--; //�hsize-1����ŦX���G�����
    }
}

// product = multiplicand * multiplier
void multiplication(HugeInt& multiplicand,
    HugeInt& multiplier, HugeInt& product)
{
    int a; //�N���e���ƥ��b�B�⪺���
    int b; //�N���e�Q���ƥ��b�B�⪺���
    product.size = multiplicand.size + multiplier.size; //�]�n�����=�Q���ƪ����+���ƪ����
    delete[] product.elems; //����bstruct�̹������O����
    product.elems = new int[product.size](); //���s�t�m�ʺA�}�C
    if (multiplicand.elems[multiplicand.size - 1] == 0 || multiplier.elems[multiplier.size - 1] == 0) //�Y�Q���Ʃέ��ƨ䤤�@�Ӫ���=0
    {
        product.size = 1; //�h�n�����=1
        product.elems[product.size - 1] = 0; //���=0
        return;
    }
    for (a = 0; a < multiplier.size; a++)
    {
        for (b = 0; b < multiplicand.size; b++)
        {
            product.elems[a + b] += multiplicand.elems[b] * multiplier.elems[a]; //�N��e�����n�̧Ƕ�J
        }
    }
    for (int c = 0; c < product.size - 1; c++) //�i��t��
    {
        while (product.elems[c] > 9) //�Y��e�Ӹ��}�C������>9
        {
            product.elems[c] -= 10; //�h�ӭ�-10
            product.elems[c + 1]++; //�V�e�i�@��
        }
    }
    if (product.elems[product.size - 1] == 0) //�Y���n�̰��s���}�C������=0 (�Y��ɩҳ]��size����)
    {
        product.size--; //�hsize-1
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
    buffer.size = dividend.size; //�](��)���ƪ��Ŷ���=�Q���ƪ��Ŷ���
    delete[]buffer.elems; //����bstruct�̹������O����
    buffer.elems = new int[buffer.size](); //���s�t�m�ʺA�}�C
    remainder.size = dividend.size; //�O��l�l�ƪŶ���=�Q���ƪŶ���
    quotient.size = dividend.size - divisor.size; //�Ӫ��Ŷ���=�Q���ƪ��Ŷ���-���ƪ��Ŷ���

    delete[] remainder.elems; //����bstruct�̹������O����
    remainder.elems = new int[remainder.size](); //���s�t�m�ʺA�}�C
    for (int x = 0; x < dividend.size; x++) //�N�Q���ư}�C�����ƽƻs���l��
    {
        remainder.elems[x] = dividend.elems[x];
    }
    if (less(dividend, divisor) == true) //�Y�Q����<����
    {
        quotient.size = 1; //�h�Ӫ����=1
        quotient.elems[quotient.size - 1] = 0; //�B�Ӧ�m���ƥ���0
        return;
    }
    for (int y = divisor.size - 1; y >= 0; y--) //�N���Ʀb�}�C��������
    {
        buffer.elems[buffer.size - 1] = divisor.elems[y];
        buffer.size--;
    }
    buffer.size = dividend.size; //���mbuffer.size�����
    if (less(dividend, buffer) == false) //�Y�Q����>=(��)����
    {
        quotient.size++; //�Ӫ��Ŷ���+1���ץ�
    }
    delete[] quotient.elems; //����bstruct�̹������O����
    quotient.elems = new int[quotient.size](); //���s�t�m�ʺA�}�C
    int quotientS = quotient.size; //�N��quotient.size�b���ᰵ�B��(quotientS���ȷ|��)
    while (buffer.size >= divisor.size) //<---�q���}�l�����k�B��
    {
        while (less(remainder, buffer) == true) //�Y(��)����>��e���l��
        {
            if ( less(buffer, dividend) == true) //�Y�Q����>(��)����
            {
                quotientS--; //�Nsize-1������]���G�b�̤@�}�l�����k�ɤ����֨�Ŷ���
            }
            divideByTen(buffer); //�h(��)���ƦV�k��֤@��
        }
        HugeInt temp;
        temp.size = remainder.size; //�Ȧs�Ȫ��\�ά��s����L���l�ơA�G�]��Ŷ���=��e�l�ƪ��Ŷ���
        delete[]temp.elems; //����bstruct�̹������O����
        temp.elems = new int[temp.size](); //���s�t�m�ʺA�}�C
        subtraction(remainder, buffer, temp); //�۴�A�ñN��Ȧs�J�Ȧs��
        quotient.elems[quotientS - 1]++; //�ӷ�e��Ƥ�����+1
        remainder.size = temp.size; //�N�Ȧs�ȩҦs���Ŷ����ٵ��l��
        for (int z = 0; z < temp.size; z++) //�N�Ȧs�Ȥ��Ҧs�����ٵ��l��
        {
            remainder.elems[z] = temp.elems[z];
        }
        delete[]temp.elems; //����Ȧs�Ȫ��O����
        if (buffer.size == divisor.size) //�Y(��)���ƪŶ���=�쥻�����ƪŶ���
        {
            if (less(remainder, divisor) == true) //�Y���Ƥ�l�Ƥj
            {
                delete[]buffer.elems; //����O����
                return; //�h�B�⧹���A�����禡
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
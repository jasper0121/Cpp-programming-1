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
    if (last >= 0) //�Ylast>=0
    {
        outFile << hugeInt[last]; //�h�L�X�ӽs���}�C������
        recursiveOutput(outFile, hugeInt, last - 1); //�éI�s�禡�ӦL�U�@�쪺��
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
    int x; //�N��B��ɷ�e�����
    differenceSize = minuendSize; //�]�t�Ȫ����=�Q��ƪ����
    delete[] difference; //����bmain�̹������O����
    difference = new int[differenceSize](); //���s�t�m�ʺA�}�C
    if (equal(minuend, subtrahend, minuendSize, subtrahendSize) == true) //�Y�Q��ƩM��ƬۦP
    {
        differenceSize = 1; //�h�t�����=1
        difference[0] = 0; //���=0
        return;
    }
    for (x = 0; x < subtrahendSize; x++)
    {
        difference[x] = minuend[x] - subtrahend[x]; //�N�۴�᪺�Ȧs�Jdifference
    }
    while (x < minuendSize) //�Y�۴��Q����٦��Ѿl
    {
        difference[x] = minuend[x]; //�h��Ѿl���Ʀs�Jdifference
        x++;
    }
    for (int y = 0; y < differenceSize - 1; y++) //�ɦ�t��
    {
        if (difference[y] < 0) //�Y�Ӹ��}�C�̪��Ȭ��t
        {
            difference[y + 1]--; //�h�V�e�ɤ@��
            difference[y] += 10; //�ӭt��+10
        }
    }
    while (difference[differenceSize - 1] == 0) //�Y�t�Ȫ��̰��s���}�C������=0 (�Y��ɩҳ]��Size����)
    {
        differenceSize--; //�hSize-1����ŦX���G�����
    }
}

// product = multiplicand * multiplier
void multiplication(int* multiplicand, int* multiplier, int*& product,
    int multiplicandSize, int multiplierSize, int& productSize)
{
    int a; //�N���e���ƥ��b�B�⪺���
    int b; //�N���e�Q���ƥ��b�B�⪺���
    productSize = multiplicandSize + multiplierSize; //�]�n�����=�Q���ƪ����+���ƪ����
    delete[] product; //����bmain�̹������O����
    product = new int[productSize](); //���s�t�m�ʺA�}�C
    if (multiplicand[multiplicandSize - 1] == 0 || multiplier[multiplierSize - 1] == 0) //�Y�Q���Ʃέ��ƨ䤤�@�Ӫ���=0
    {
        productSize = 1; //�h�n�����=1
        product[productSize - 1] = 0; //���=0
        return;
    }
    for (a = 0; a < multiplierSize; a++)
    {
        for (b = 0; b < multiplicandSize; b++)
        {
            product[a + b] += multiplicand[b] * multiplier[a]; //�N��e�����n�̧Ƕ�J
        }
    }
    for (int c = 0; c < productSize - 1; c++) //�i��t��
    {
        while (product[c] > 9) //�Y��e�Ӹ��}�C������>9
        {
            product[c] -= 10; //�h�ӭ�-10
            product[c + 1]++; //�V�e�i�@��
        }
    }
    if (product[productSize - 1] == 0) //�Y���n�̰��s���}�C������=0 (�Y��ɩҳ]��Size����)
    {
        productSize--; //�hSize-1
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
    int bufferSize = dividendSize; //�](��)���ƪ��Ŷ���=�Q���ƪ��Ŷ���
    remainderSize = dividendSize; //�O��l�l�ƪŶ���=�Q���ƪŶ���
    quotientSize = dividendSize - divisorSize; //�Ӫ��Ŷ���=�Q���ƪ��Ŷ���-���ƪ��Ŷ���

    delete[] remainder; //����bmain�̹������O����
    remainder = new int[remainderSize](); //���s�t�m�ʺA�}�C
    for (int x = 0; x < dividendSize; x++) //�N�Q���ư}�C�����ƽƻs���l��
    {
        remainder[x] = dividend[x];
    }
    if (less(dividend, divisor, dividendSize, divisorSize) == true) //�Y�Q����<����
    {
        quotientSize = 1; //�h�Ӫ����=1
        quotient[quotientSize - 1] = 0; //�B�Ӧ�m���ƥ���0
        return;
    }
    for (int y = divisorSize - 1; y >= 0; y--) //�N���Ʀb�}�C��������
    {
        buffer[bufferSize - 1] = divisor[y];
        bufferSize--;
    }
    bufferSize = dividendSize; //���mbufferSize�����
    if (less(dividend, buffer, dividendSize, bufferSize) == false) //�Y�Q����>=(��)����
    {
        quotientSize++; //�Ӫ��Ŷ���+1���ץ�
    }
    delete[] quotient; //����bmain�̹������O����
    quotient = new int[quotientSize](); //���s�t�m�ʺA�}�C
    int quotientS = quotientSize; //�N��quotientSize�b���ᰵ�B��(quotientS���ȷ|��)
    while (bufferSize >= divisorSize) //<---�q���}�l�����k�B��
    {
        while (less(remainder, buffer, remainderSize, bufferSize) == true) //�Y(��)����>��e���l��
        {
            if (less(buffer, dividend, bufferSize, dividendSize) == true) //�Y(��)����<�Q����
            {
                quotientS--; //�Nsize-1������]���G�b�̤@�}�l�����k�ɤ����֨�Ŷ���
            }
            divideBy10(buffer, bufferSize); //�h(��)���ƦV�k��֤@��
        }
        tempSize = remainderSize; //�Ȧs�Ȫ��\�ά��s����L���l�ơA�G�]��Ŷ���=��e�l�ƪ��Ŷ���
        int* temp = new int[tempSize](); //�]�@�ʺA�}�C
        subtraction(remainder, buffer, temp, remainderSize, bufferSize, tempSize); //�۴�A�ñN��Ȧs�J�Ȧs��
        quotient[quotientS - 1]++; //�ӷ�e��Ƥ�����+1
        remainderSize = tempSize; //�N�Ȧs�ȩҦs���Ŷ����ٵ��l��
        delete[]remainder; //����l�ƪ��O����
        remainder = temp; //�N�Ȧs�Ȫ��a�}���l��
        if (bufferSize == divisorSize) //�Y(��)���ƪŶ���=�쥻�����ƪŶ���
        {
            if (less(remainder, divisor, remainderSize, divisorSize) == true) //�Y���Ƥ�l�Ƥj
            {
                return; //�h�B�⧹���A�����禡
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
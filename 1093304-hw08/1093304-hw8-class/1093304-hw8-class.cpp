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
    if (last >= 0) //�Ylast>=0
    {
        outFile << elems[last]; //�h�L�X�ӽs���}�C������
        recursiveOutput(outFile, last - 1); //�éI�s�禡�ӦL�U�@�쪺��
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
    if (elems[last] == hugeInt2.elems[last]) //�Y�Ӧ�ƪ��Ƭ۵�
    {
        if (last == 0) //�Y2�̳̫�@�쪺�Ƥ]�ۦP
        {
            return true; //�h��2�ƥ��ۦP�A�G�^��true
        }
        return recursiveEqual(hugeInt2, last - 1); //�h�I�s�禡�ˬd�U�@��ƬO�_�]�۵�
    }
    else
    {
        return false; //�_�h�^��false
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
    if (elems[last] == hugeInt2.elems[last]) //�Y�Ӧ�ƪ��Ƭ۵�
    {
        if (last == 0) //�Y�ˬd��̫�@��Ƥ]�۵�
        {
            return false; //�h��2�Ƭ۵��A�^��false
        }
        return recursiveLess(hugeInt2, last - 1); //�h�I�s�禡�ˬd�U�@���
    }
    else if (elems[last] > hugeInt2.elems[last]) //�Y�b�Ӧ��current object>hugeInt2
    {
        return false; //�h�^��false
    }
    else if (elems[last] < hugeInt2.elems[last]) //�Y�b�Ӧ��current object<hugeInt2
    {
        return true; //�h�^��true
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
    int x; //�N��B��ɷ�e�����
    difference.size = size; //�]�t�Ȫ����=�Q���(current object)�����
    delete[] difference.elems; //����bclass�̹������O����
    difference.elems = new int[difference.size](); //���s�t�m�ʺA�}�C
    if (equal(subtrahend) == true) //�Y�Q���(current object)�M��ƬۦP
    {
        difference.size = 1; //�h�t�����=1
        difference.elems[0] = 0; //���=0
        return;
    }
    for (x = 0; x < subtrahend.size; x++)
    {
        difference.elems[x] = elems[x] - subtrahend.elems[x]; //�N�۴�᪺�Ȧs�Jdifference
    }
    while (x < size) //�Y�۴��Q���(current object)�٦��Ѿl
    {
        difference.elems[x] = elems[x]; //�h��Ѿl���Ʀs�Jdifference
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
        difference.shrink_to_fit();
    }
}

// product = current object * multiplier
void HugeInt::multiplication(HugeInt& multiplier, HugeInt& product)
{
    product.size = size + multiplier.size; //�]�n�����=�Q����(current object)�����+���ƪ����
    delete[] product.elems; //����bclass�̹������O����
    product.elems = new int[product.size](); //���s�t�m�ʺA�}�C
    if (elems[size - 1] == 0 || multiplier.elems[multiplier.size - 1] == 0) //�Y�Q����(current object)�έ��ƨ䤤�@�Ӫ���=0
    {
        product.size = 1; //�h�n�����=1
        product.elems[product.size - 1] = 0; //���=0
        return;
    }
    for (int a = 0; a < multiplier.size; a++) //�N���e���ƥ��b�B�⪺���
    {
        for (int b = 0; b < size; b++) //�N���e�Q����(current object)���b�B�⪺���
        {
            product.elems[a + b] += elems[b] * multiplier.elems[a]; //�N��e�����n�̧Ƕ�J
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
    buffer.size = size; //�](��)���ƪ��Ŷ���=�Q����(current object)���Ŷ���
    delete[]buffer.elems; //����bclass�̹������O����
    buffer.elems = new int[buffer.size](); //���s�t�m�ʺA�}�C
    remainder.size = size; //�O��l�l�ƪŶ���=�Q����(current object)�Ŷ���
    quotient.size = size - divisor.size; //�Ӫ��Ŷ���=�Q����(current object)���Ŷ���-���ƪ��Ŷ���

    delete[] remainder.elems; //����bclass�̹������O����
    remainder.elems = new int[remainder.size](); //���s�t�m�ʺA�}�C
    for (int x = 0; x < size; x++) //�N�Q����(current object)�}�C�����ƽƻs���l��
    {
        remainder.elems[x] = elems[x];
    }
    if (less(divisor) == true) //�Y�Q����(current object)<����
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
    buffer.size = size; //���mbuffer.size�����
    if (less(buffer) == false) //�Y�Q����(current object)>=(��)����
    {
        quotient.size++; //�Ӫ��Ŷ���+1���ץ�
    }
    delete[] quotient.elems; //����bclass�̹������O����
    quotient.elems = new int[quotient.size](); //���s�t�m�ʺA�}�C
    int quotientS = quotient.size; //�N��quotient.size�b���ᰵ�B��(quotientS���ȷ|��)
    while (buffer.size >= divisor.size) //<---�q���}�l�����k�B��
    {
        while (remainder.less(buffer) == true) //�Y��e���l��(current object)<(��)����
        {
            if (less(buffer) == false) //�Y�Q����(current object)>(��)����
            {
                quotientS--; //�Y�@�}�l�B�⪺(��)����>�Q���ơA�h��size����
            }
            buffer.divideByTen(); //�h(��)����(current object)�V�k��֤@��
        }
        HugeInt temp;
        temp.size = remainder.size; //�Ȧs�Ȫ��\�ά��s����L���l�ơA�G�]��Ŷ���=��e�l�ƪ��Ŷ���
        delete[]temp.elems; //����bclass�̹������O����
        temp.elems = new int[temp.size](); //���s�t�m�ʺA�}�C
        remainder.subtraction(buffer, temp); //�۴�A�ñN��Ȧs�J�Ȧs��
        quotient.elems[quotientS - 1]++; //�ӷ�e��Ƥ�����+1
        remainder.size = temp.size; //�N�Ȧs�ȩҦs���Ŷ����ٵ��l��
        delete[]remainder.elems; //�����ª�remainder.elems
        remainder = temp; //�Ntemp�Ҧs���a�}��remainder�A��remainder���Vtemp���}�C
        if (buffer.size == divisor.size) //�Y(��)���ƪŶ���=�쥻�����ƪŶ���
        {
            if (remainder.less(divisor) == true) //�Y���Ƥ�l��(current object)�j
            {
                delete[]buffer.elems; //����O����
                return; //�h�B�⧹���A�����禡
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
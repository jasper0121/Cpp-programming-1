#include <iostream>
#include <fstream>
#include <vector>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the vector program
void load(vector< char* >& program);

// deletes the comment beginning with "//" from sourceLine if any
void delComment(char sourceLine[]);

// deletes all string constants from sourceLine
void delStrConsts(char sourceLine[]);

// deletes all character constants from sourceLine
void delCharConsts(char sourceLine[]);

// extracts all identifiers from sourceLine, and put them into the vector identifiers
void extractIdentifiers(char sourceLine[], vector< char* >& identifiers);

// stores all non-keyword strings in the vector identifiers into a text file
void store(vector< char* >& identifiers);

// returns true if and only if str is a C++ keyword
bool keyword(char str[]);

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(vector< char* >& identifiers, int pos);

const char keywords[][20] = { "auto", "break", "case", "char", "const",
                                "continue", "default", "define","do", "double",
                                "else", "enum", "extern", "float", "for",
                                "goto", "if", "int", "long", "register",
                                "return", "short", "signed", "sizeof",
                                "static", "struct", "switch", "typedef",
                                "union", "unsigned", "void", "volatile",
                                "while", "bool", "catch", "class",
                                "const_cast", "delete", "dynamic_cast",
                                "explicit", "false", "friend", "inline",
                                "mutable", "namespace", "new", "operator",
                                "private", "protected", "public",
                                "reinterpret_cast", "static_cast", "template",
                                "this", "throw", "true", "try", "typeid",
                                "typename", "using", "virtual", "include" };

int main()
{
    vector< char* > program;

    // reads in a C++ program from a cpp file, and put it to the vector program
    load(program);

    vector< char* > identifiers;
    for (size_t i = 0; i < program.size(); i++)
    {
        delComment(program[i]); // deletes the comment beginning with "//" from program[ i ]
        delStrConsts(program[i]); // deletes all string constants from program[ i ]
        delCharConsts(program[i]); // deletes all character constants from program[ i ]

        if (strcmp(program[i], "") != 0)
            extractIdentifiers(program[i], identifiers);
        // extracts all identifiers from program[ i ], and put them into the vector identifiers
    }

    // stores all non-keyword strings in the vector identifiers into a text file
    store(identifiers);

    for (int k = 0; k < program.size(); k++) //����program�̪��O����
    {
        delete[]program[k];
    }

    for (int k = 0; k < identifiers.size(); k++) //����identifiers�̪��O����
    {
        delete[] identifiers[k];
    }

    system("pause");
}

void load(vector< char* >& program)
{
    ifstream inFile("test.cpp", ios::in); //Ū��

    if (!inFile) //�Y�SŪ����
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    while (!inFile.eof()) //�Y�٥����ɮ׵���
    {
        char* str = new char[100]; //�]�m�ʺA�}�C
        inFile.getline(str, 100, '\n'); //�h�@��@��a�qinFileŪ�Jstr
        program.push_back(str); //program�W�[1��æs�Jstr���a�}�A�ϱoprogram���Vstr�}�C
    }

    inFile.close(); //Ū������
    return;
}

void delComment(char sourceLine[])
{
    for (int i = 0; sourceLine[i + 1] != '\0'; i++)
        if ((sourceLine[i] == '/' || sourceLine[i + 1] == '/'))
        {
            sourceLine[i] = '\0';
            return;
        }
}

void delStrConsts(char sourceLine[])
{
    for (int k = 0; sourceLine[k] != '\0'; k++)
    {
        if (sourceLine[k] == '"') //�Y�Ӯ椺�����޸�
        {
            do //�����Ӯ椺�אּ�ť���A�ñq�U�@���~���ˬd
            {
                sourceLine[k] = ' ';
                k++;
            } while (sourceLine[k] != '"'); //�b�J��U�@�����޸��e�A���N�o�q�}�C�����e�אּ�ť���
            sourceLine[k] = ' '; //�J��ĤG�����޸��h���Xwhile�A�ñN�����޸��אּ�ť���
        }
    }
    return;
}

void delCharConsts(char sourceLine[])
{
    for (int k = 0; sourceLine[k] != '\0'; k++)
    {
        //�Y�Ӯ椺�D�Ʀr�B�^��r���B���u�ΪŦr���A�h�N�Ӯ椺�אּ�ť��� (���u�i�ର�զ�identifiers���@���A�G���i�R)
        if (!(('0' <= sourceLine[k] && sourceLine[k] <= '9') || ('A' <= sourceLine[k] && sourceLine[k] <= 'Z')
            || ('a' <= sourceLine[k] && sourceLine[k] <= 'z') || sourceLine[k] == '_' || sourceLine[k] == '\0'))
        {
            sourceLine[k] = ' ';
        }
        //�Y�Ʀr�e�S���^��r���A�h�N�ӼƧאּ�ť��� (identifiers�����줣��O�Ʀr)
        if (('0' <= sourceLine[k] && sourceLine[k] <= '9') &&
            !(('A' <= sourceLine[k - 1] && sourceLine[k - 1] <= 'Z') || ('a' <= sourceLine[k - 1] && sourceLine[k - 1] <= 'z')))
        {
            sourceLine[k] = ' ';
        }
    }
    return;
}

void extractIdentifiers(char sourceLine[], vector< char* >& identifiers)
{
    char* str = new char[20]; //�إߦr�����ʺA�}�C�Ӧs��identifiers
    int number = 0; //�N��ʺA�}�C���}�C�s��

    for (int k = 0; sourceLine[k] != '\0'; k++) //�Y�J��Ŧr���A�h�N���ᬰ���ѩΦr�굲���A�G���X�j��
    {
        //�Y�Ӯ椺���Ʀr�B�^��r���Ω��u
        if (('0' <= sourceLine[k] && sourceLine[k] <= '9') || ('A' <= sourceLine[k] && sourceLine[k] <= 'Z')
            || ('a' <= sourceLine[k] && sourceLine[k] <= 'z') || sourceLine[k] == '_')
        {
            str[number] = sourceLine[k]; //�h�N�Ӧr���s�J�ʺA�}�C
            number++;

            //�Y�U�@�椺���O�Ʀr�B�^��r���Ω��u
            if (!(('0' <= sourceLine[k + 1] && sourceLine[k + 1] <= '9') || ('A' <= sourceLine[k + 1] && sourceLine[k + 1] <= 'Z')
                || ('a' <= sourceLine[k + 1] && sourceLine[k + 1] <= 'z') || sourceLine[k + 1] == '_'))
            {
                str[number] = '\0'; //�h�N��r�괣�������A�b�ʺA�}�C�[�W�Ŧr��

                if (keyword(str) == false) //�Y��str���O�W���ҦC������r
                {
                    identifiers.push_back(str); //identifiers�W�[1��æs�Jstr���a�}�A�ϱoidentifiers���Vstr�}�C
                    str = new char[20]; //�]�°ʺA�}�C�w����identifiers���@�����A�G�A�s�W�@�ʺA�}�C
                }
                number = 0; //���m
            }
        }
    }
    delete[]str; //����O����
    return;
}

void store(vector< char* >& identifiers)
{
    ofstream outFile("identifiers.txt", ios::out); //�g��

    for (int k = 0; k < identifiers.size(); k++)
    {
        if (duplicate(identifiers, k) == false) //�Y�n�g�J��identifiers������
        {
            outFile << identifiers[k] << endl; //�h��X�ӵ����
        }
    }

    outFile.close(); //�g������
    return;
}

bool keyword(char str[])
{
    const int numKeywords = sizeof(keywords) / 20;
    for (int i = 0; i < numKeywords; i++)
        if (strcmp(keywords[i], str) == 0)
            return true;

    return false;
}

bool duplicate(vector< char* >& identifiers, int pos)
{
    for (int i = 0; i < pos; i++)
        if (strcmp(identifiers[i], identifiers[pos]) == 0)
            return true;

    return false;
}
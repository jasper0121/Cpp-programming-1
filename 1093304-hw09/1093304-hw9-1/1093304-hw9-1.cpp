#include <iostream>
#include <fstream>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load(char(*program)[100], int& numLines);

// deletes the comment beginning with "//" from sourceLine if any
void delComment(char sourceLine[]);

// deletes all string constants from sourceLine
void delStrConsts(char sourceLine[]);

// deletes all character constants from sourceLine
void delCharConsts(char sourceLine[]);

// extracts all identifiers from sourceLine, and put them into the array identifiers
void extractIdentifiers(char sourceLine[], char identifiers[][32], int& numIdentifiers);

// stores all non-keyword strings in the array identifiers into a text file
void store(char(*identifiers)[32], int numIdentifiers);

// returns true if and only if str is a C++ keyword
bool keyword(char str[]);

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(char(*identifiers)[32], int pos);

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
    char(*program)[100] = new char[500][100];
    int numLines = 0;

    // reads in a C++ program from a cpp file, and put it to the array program
    load(program, numLines);

    char(*identifiers)[32] = new char[500][32];
    int numIdentifiers = 0;

    for (int i = 0; i < numLines; i++)
    {
        delComment(program[i]); // deletes the comment beginning with "//" from program[ i ]
        delStrConsts(program[i]); // deletes all string constants from program[ i ]
        delCharConsts(program[i]); // deletes all character constants from program[ i ]

        if (strcmp(program[i], "") != 0)
            extractIdentifiers(program[i], identifiers, numIdentifiers);
        // extracts all identifiers from program[ i ], and put them into the array identifiers
    }

    // stores all non-keyword strings in the array identifiers into a text file
    store(identifiers, numIdentifiers);

    delete[]program; //����program�̪��O����
    delete[]identifiers; //����identifiers�̪��O����

    system("pause");
}

void load(char(*program)[100], int& numLines)
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
        inFile.getline(program[numLines], 100, '\n'); //�h�@��@��aŪ�Jprogram
        numLines++;
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

void extractIdentifiers(char line[], char identifiers[][32], int& numIdentifiers)
{
    char* str = new char[20]; //�إߦr�����ʺA�}�C�Ӧs��identifiers
    int number = 0; //�N��ʺA�}�C���}�C�s��

    for (int k = 0; line[k] != '\0'; k++) //�Y�J��Ŧr���A�h�N���ᬰ���ѩΦr�굲���A�G���X�j��
    {
        //�Y�Ӯ椺���Ʀr�B�^��r���Ω��u
        if (('0' <= line[k] && line[k] <= '9') || ('A' <= line[k] && line[k] <= 'Z') || ('a' <= line[k] && line[k] <= 'z') || line[k] == '_')
        {
            str[number] = line[k]; //�h�N�Ӧr���s�J�ʺA�}�C
            number++;

            //�Y�U�@�椺���O�Ʀr�B�^��r���Ω��u
            if (!(('0' <= line[k + 1] && line[k + 1] <= '9') || ('A' <= line[k + 1] && line[k + 1] <= 'Z')
                || ('a' <= line[k + 1] && line[k + 1] <= 'z') || line[k + 1] == '_'))
            {
                str[number] = '\0'; //�h�N��r�괣�������A�b�ʺA�}�C�[�W�Ŧr��

                if (keyword(str) == false) //�Y��str���O�W���ҦC������r
                {
                    for (int r = 0; r < 20; r++) //�h�Nstr�r��ƻs�s�Jidentifiers�}�C
                    {
                        identifiers[numIdentifiers][r] = str[r];
                    }
                    numIdentifiers++;
                }
                //���m
                number = 0;
                delete[]str;
                str = new char[20];
            }
        }
    }
    delete[]str; //����O����
    return;
}

void store(char(*identifiers)[32], int numIdentifiers)
{
    ofstream outFile("identifiers.txt", ios::out); //�g��

    for (int k = 0; k < numIdentifiers; k++)
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

bool duplicate(char(*identifiers)[32], int pos)
{
    for (int i = 0; i < pos; i++)
        if (strcmp(identifiers[i], identifiers[pos]) == 0)
            return true;

    return false;
}
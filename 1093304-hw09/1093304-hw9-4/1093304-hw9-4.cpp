#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the vector program
void load(vector< string >& program);

// deletes the comment beginning with "//" from sourceLine if any
void delComment(string& sourceLine);

// deletes all string constants from sourceLine
void delStrConsts(string& sourceLine);

// deletes all character constants from sourceLine
void delCharConsts(string& sourceLine);

// extracts all identifiers from sourceLine, and put them into the vector identifiers
void extractIdentifiers(string& sourceLine, vector< string >& identifiers);

// stores all non-keyword strings in the vector identifiers into a text file
void store(vector< string >& identifiers);

// return true if and only if "str" is a C++ keyword
bool keyword(string str);

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(vector< string >& identifiers, int pos);

const string keywords[] = { "auto", "break", "case", "char", "const",
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
    vector< string > program;

    // reads in a C++ program from a cpp file, and put it to the vector program
    load(program);

    vector< string > identifiers;
    string null;

    for (size_t i = 0; i < program.size(); i++)
    {
        delComment(program[i]); // deletes the comment beginning with "//" from program[ i ]
        delStrConsts(program[i]); // deletes all string constants from program[ i ]
        delCharConsts(program[i]); // deletes all character constants from program[ i ]

        if (program[i] != null)
            extractIdentifiers(program[i], identifiers);
        // extracts all identifiers from program[ i ], and put them into the vector identifiers
    }

    // stores all non-keyword strings in the vector identifiers into a text file
    store(identifiers);

    system("pause");
}

void load(vector< string >& program)
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
        string str; //�h�]�m�r��}�C�ӦsŪ�i�Ӫ����
        getline(inFile, str, '\n'); //�@��@��a�qinFileŪ�Jstr
        program.push_back(str); //�A��str������Ʀs�Jprogram
    }

    inFile.close(); //Ū������
    return;
}

void delComment(string& sourceLine)
{
    unsigned len = sourceLine.size();
    if (len > 1)
        for (unsigned int i = 0; i < len - 1; i++)
            if (sourceLine[i] == '/' && sourceLine[i + 1] == '/')
            {
                sourceLine.erase(i, len);
                break;
            }
}

void delStrConsts(string& sourceLine)
{
    size_t begin, finish, length; //�]�m�_�I�B���I�B����

    while ((begin = sourceLine.find('"', 0)) && begin != string::npos) //�Y�b�Ӧr�ꤺ�����Ĥ@�����޸�(�q0�}�l��)
    {
        finish = sourceLine.find('"', begin + 1); //�h�M��ĤG�����޸�(�q�Ĥ@�����޸����U�@��}�C�}�l��)
        length = finish - begin + 1; //�r�ꪺ���׬��G���I-�_�I+1
        sourceLine.erase(begin, length); //�����Ӧr��
    }
    return;
}

void delCharConsts(string& sourceLine)
{
    for (int k = 0; sourceLine[k] != '\0'; k++)
    {
        //�Y�Ӯ椺�D�Ʀr�B�^��r���B���u�ΪŦr���A�h�N�Ӯ椺�אּ�ť��� (���u�i�ର�զ�identifiers���@���A�G���i�R)
        if (!(('0' <= sourceLine[k] && sourceLine[k] <= '9') || ('A' <= sourceLine[k] && sourceLine[k] <= 'Z')
            || ('a' <= sourceLine[k] && sourceLine[k] <= 'z') || sourceLine[k] == '_'))
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

void extractIdentifiers(string& sourceLine, vector< string >& identifiers)
{
    string str; //�]�m�Ŧr��

    for (int k = 0; sourceLine[k] != '\0'; k++) //�Y�J��Ŧr���A�h�N���ᬰ���ѩΦr�굲���A�G���X�j��
    {
        //�Y�Ӯ椺���Ʀr�B�^��r���Ω��u
        if (('0' <= sourceLine[k] && sourceLine[k] <= '9') || ('A' <= sourceLine[k] && sourceLine[k] <= 'Z')
            || ('a' <= sourceLine[k] && sourceLine[k] <= 'z') || sourceLine[k] == '_')
        {
            str.push_back(sourceLine[k]); //�hstr�W�[�@��Ŷ��A�ñN�Ȧs�J�䤤

            //�Y�U�@�椺���O�Ʀr�B�^��r���Ω��u
            if (!(('0' <= sourceLine[k + 1] && sourceLine[k + 1] <= '9') || ('A' <= sourceLine[k + 1] && sourceLine[k + 1] <= 'Z')
                || ('a' <= sourceLine[k + 1] && sourceLine[k + 1] <= 'z') || sourceLine[k + 1] == '_'))
            {
                if (keyword(str) == false) //�Y��str���O�W���ҦC������r
                {
                    identifiers.push_back(str); //�h�Nstr������Ʀs�Jidentifiers
                }
                str.clear(); //�r�꭫�m
            }
        }
    }
    return;
}

void store(vector< string >& identifiers)
{
    ofstream outFile("identifiers.txt", ios::out); //�g��

    for (int k = 0; k < identifiers.size(); k++)
    {
        if (duplicate(identifiers, k) == false) //�Y�n�g�J��identifiers������
        {
            outFile << identifiers[k] << endl; //�h�Nstr�r��ƻs�s�Jidentifiers�}�C
        }
    }

    outFile.close(); //�g������
    return;
}

bool keyword(string str)
{
    const int numKeywords = sizeof(keywords) / 20;
    for (int i = 0; i < numKeywords; i++)
        if (keywords[i] == str)
            return true;

    return false;
}

bool duplicate(vector< string >& identifiers, int pos)
{
    for (int i = 0; i < pos; i++)
        if (identifiers[i] == identifiers[pos])
            return true;

    return false;
}
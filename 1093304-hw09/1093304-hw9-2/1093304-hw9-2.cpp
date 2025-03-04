#include <iostream>
#include <fstream>
#include <string>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load(string* program, int& numLines);

// deletes the comment beginning with "//" from sourceLine if any
void delComment(string& sourceLine);

// deletes all string constants from sourceLine
void delStrConsts(string& sourceLine);

// deletes all character constants from sourceLine
void delCharConsts(string& sourceLine);

// extracts all identifiers from sourceLine, and put them into the array identifiers
void extractIdentifiers(string& sourceLine, string* identifiers, int& numIdentifiers);

// stores all non-keyword strings in the array identifiers into a text file
void store(string* identifiers, int numIdentifiers);

// return true if and only if "str" is a C++ keyword
bool keyword(string str);

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(string* identifiers, int pos);

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
    string* program = new string[500];
    int numLines = 0;

    // reads in a C++ program from a cpp file, and put it to the array program
    load(program, numLines);

    string* identifiers = new string[500];
    string null;
    int numIdentifiers = 0;

    for (int i = 0; i < numLines; i++)
    {
        delComment(program[i]); // deletes the comment beginning with "//" from program[ i ]
        delStrConsts(program[i]); // deletes all string constants from program[ i ]
        delCharConsts(program[i]); // deletes all character constants from program[ i ]

        if (program[i] != null)
            extractIdentifiers(program[i], identifiers, numIdentifiers);
        // extracts all identifiers from program[ i ], and put them into the array identifiers
    }
    // stores all non-keyword strings in the array identifiers into a text file
    store(identifiers, numIdentifiers);

    delete[] program; //釋放program裡的記憶體
    delete[] identifiers; //釋放identifiers裡的記憶體

    system("pause");
}

void load(string* program, int& numLines)
{
    ifstream inFile("test.cpp", ios::in); //讀檔

    if (!inFile) //若沒讀到檔
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    while (!inFile.eof()) //若還未到檔案結尾
    {
        getline(inFile, program[numLines], '\n'); //則一行一行地從inFile讀入program
        numLines++;
    }

    inFile.close(); //讀檔關閉
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
    size_t begin, finish, length; //設置起點、終點、長度

    while ((begin = sourceLine.find('"', 0)) && begin != string::npos) //若在該字串內有找到第一個雙引號(從0開始找)
    {
        finish = sourceLine.find('"', begin + 1); //則尋找第二個雙引號(從第一個雙引號的下一格陣列開始找)
        length = finish - begin + 1; //字串的長度為：終點-起點+1
        sourceLine.erase(begin, length); //擦除該字串
    }
    return;
}

void delCharConsts(string& sourceLine)
{
    for (int k = 0; sourceLine[k] != '\0'; k++)
    {
        //若該格內非數字、英文字母、底線或空字元，則將該格內改為空白鍵 (底線可能為組成identifiers的一員，故不可刪)
        if (!(('0' <= sourceLine[k] && sourceLine[k] <= '9') || ('A' <= sourceLine[k] && sourceLine[k] <= 'Z')
            || ('a' <= sourceLine[k] && sourceLine[k] <= 'z') || sourceLine[k] == '_'))
        {
            sourceLine[k] = ' ';
        }

        //若數字前沒有英文字母，則將該數改為空白鍵 (identifiers的首位不能是數字)
        if (('0' <= sourceLine[k] && sourceLine[k] <= '9') &&
            !(('A' <= sourceLine[k - 1] && sourceLine[k - 1] <= 'Z') || ('a' <= sourceLine[k - 1] && sourceLine[k - 1] <= 'z')))
        {
            sourceLine[k] = ' ';
        }
    }
    return;
}

void extractIdentifiers(string& sourceLine, string* identifiers, int& numIdentifiers)
{
    string str; //設置空字串

    for (int k = 0; sourceLine[k] != '\0'; k++) //若遇到空字元，則代表之後為註解或字串結束，故跳出迴圈
    {
        //若該格內為數字、英文字母或底線
        if (('0' <= sourceLine[k] && sourceLine[k] <= '9') || ('A' <= sourceLine[k] && sourceLine[k] <= 'Z')
            || ('a' <= sourceLine[k] && sourceLine[k] <= 'z') || sourceLine[k] == '_')
        {
            str.push_back(sourceLine[k]); //則str增加一格空間，並將值存入其中

            //若下一格內不是數字、英文字母或底線
            if (!(('0' <= sourceLine[k + 1] && sourceLine[k + 1] <= '9') || ('A' <= sourceLine[k + 1] && sourceLine[k + 1] <= 'Z')
                || ('a' <= sourceLine[k + 1] && sourceLine[k + 1] <= 'z') || sourceLine[k + 1] == '_'))
            {
                if (keyword(str) == false) //若此str不是上面所列的關鍵字
                {
                    identifiers[numIdentifiers] = str; //則將str字串複製存入identifiers陣列
                    numIdentifiers++;
                }
                str.clear(); //字串重置
            }
        }
    }
    return;
}

void store(string* identifiers, int numIdentifiers)
{
    ofstream outFile("identifiers.txt", ios::out); //寫檔

    for (int k = 0; k < numIdentifiers; k++)
    {
        if (duplicate(identifiers, k) == false) //若要輸出的identifiers不重複
        {
            outFile << identifiers[k] << endl; //則輸出該筆資料
        }
    }

    outFile.close(); //寫檔關閉
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

bool duplicate(string* identifiers, int pos)
{
    for (int i = 0; i < pos; i++)
        if (identifiers[i] == identifiers[pos])
            return true;

    return false;
}
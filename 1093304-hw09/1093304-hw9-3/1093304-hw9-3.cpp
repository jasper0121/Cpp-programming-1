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

    for (int k = 0; k < program.size(); k++) //釋放program裡的記憶體
    {
        delete[]program[k];
    }

    for (int k = 0; k < identifiers.size(); k++) //釋放identifiers裡的記憶體
    {
        delete[] identifiers[k];
    }

    system("pause");
}

void load(vector< char* >& program)
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
        char* str = new char[100]; //設置動態陣列
        inFile.getline(str, 100, '\n'); //則一行一行地從inFile讀入str
        program.push_back(str); //program增加1格並存入str的地址，使得program指向str陣列
    }

    inFile.close(); //讀檔關閉
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
        if (sourceLine[k] == '"') //若該格內為雙引號
        {
            do //先讓該格內改為空白鍵，並從下一格繼續檢查
            {
                sourceLine[k] = ' ';
                k++;
            } while (sourceLine[k] != '"'); //在遇到下一個雙引號前，都將這段陣列的內容改為空白鍵
            sourceLine[k] = ' '; //遇到第二個雙引號則跳出while，並將該雙引號改為空白鍵
        }
    }
    return;
}

void delCharConsts(char sourceLine[])
{
    for (int k = 0; sourceLine[k] != '\0'; k++)
    {
        //若該格內非數字、英文字母、底線或空字元，則將該格內改為空白鍵 (底線可能為組成identifiers的一員，故不可刪)
        if (!(('0' <= sourceLine[k] && sourceLine[k] <= '9') || ('A' <= sourceLine[k] && sourceLine[k] <= 'Z')
            || ('a' <= sourceLine[k] && sourceLine[k] <= 'z') || sourceLine[k] == '_' || sourceLine[k] == '\0'))
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

void extractIdentifiers(char sourceLine[], vector< char* >& identifiers)
{
    char* str = new char[20]; //建立字元的動態陣列來存取identifiers
    int number = 0; //代表動態陣列的陣列編號

    for (int k = 0; sourceLine[k] != '\0'; k++) //若遇到空字元，則代表之後為註解或字串結束，故跳出迴圈
    {
        //若該格內為數字、英文字母或底線
        if (('0' <= sourceLine[k] && sourceLine[k] <= '9') || ('A' <= sourceLine[k] && sourceLine[k] <= 'Z')
            || ('a' <= sourceLine[k] && sourceLine[k] <= 'z') || sourceLine[k] == '_')
        {
            str[number] = sourceLine[k]; //則將該字元存入動態陣列
            number++;

            //若下一格內不是數字、英文字母或底線
            if (!(('0' <= sourceLine[k + 1] && sourceLine[k + 1] <= '9') || ('A' <= sourceLine[k + 1] && sourceLine[k + 1] <= 'Z')
                || ('a' <= sourceLine[k + 1] && sourceLine[k + 1] <= 'z') || sourceLine[k + 1] == '_'))
            {
                str[number] = '\0'; //則代表字串提取完畢，在動態陣列加上空字元

                if (keyword(str) == false) //若此str不是上面所列的關鍵字
                {
                    identifiers.push_back(str); //identifiers增加1格並存入str的地址，使得identifiers指向str陣列
                    str = new char[20]; //因舊動態陣列已成為identifiers的一部份，故再新增一動態陣列
                }
                number = 0; //重置
            }
        }
    }
    delete[]str; //釋放記憶體
    return;
}

void store(vector< char* >& identifiers)
{
    ofstream outFile("identifiers.txt", ios::out); //寫檔

    for (int k = 0; k < identifiers.size(); k++)
    {
        if (duplicate(identifiers, k) == false) //若要寫入的identifiers不重複
        {
            outFile << identifiers[k] << endl; //則輸出該筆資料
        }
    }

    outFile.close(); //寫檔關閉
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
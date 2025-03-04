#include <iostream>
#include <fstream>
using namespace::std;

struct Member
{
    char email[40];
    char password[24];
    char IDNumber[12];
    char name[12];
    char phone[12];
};

void loadMemberInfo(ifstream& inMemberFile, Member memberDetails[], int& numMembers);

// input an integer from the keyboard, and
// returns the integer if it belongs to [ begin, end ], returns -1 otherwise.
int inputAnInteger(int begin, int end);

void login(Member memberDetails[], int numMembers);

// returns true if there is a member
// whose email and password are equal to the specified email and password, respectively
bool legal(char email[], char password[], Member memberDetails[], int numMembers, int& recordNumber);

void accountInfor(Member memberDetails[], int numMembers, int recordNumber);

void newMember(Member memberDetails[], int& numMembers);

// returns true if there is a member whose IDNumber is equal to newIDNumber
bool existingID(char newIDNumber[], Member memberDetails[], int& numMembers);

// returns true if there is a member whose email is equal to newEmail
bool existingEmail(char newEmail[], Member memberDetails[], int& numMembers);

void saveMemberInfo(ofstream& outMemberFile, Member memberDetails[], int numMembers);

int main()
{
    Member memberDetails[100] = { "", "", "", "", "" };
    int numMembers = 0;

    ifstream inMemberFile;
    ofstream outMemberFile;

    loadMemberInfo(inMemberFile, memberDetails, numMembers);

    cout << "Welcome to Vieshow Cinemas member system\n\n";

    int choice;

    while (true)
    {
        cout << "Enter your choice:" << endl;
        cout << "1. Sign In\n";
        cout << "2. New Member\n";
        cout << "3. Sign Out\n? ";

        choice = inputAnInteger(1, 3);
        cout << endl;

        switch (choice)
        {
        case 1:
            login(memberDetails, numMembers);
            break;

        case 2:
            newMember(memberDetails, numMembers);
            break;

        case 3:
            saveMemberInfo(outMemberFile, memberDetails, numMembers);
            cout << "Thank you...\n\n";
            system("pause");
            return 0;

        default:
            cout << "Input Error!\n\n";
            break;
        }
    }

    system("pause");
}

//讀MemberInfo.dat裡的檔
void loadMemberInfo(ifstream& inMemberFile, Member memberDetails[], int& numMembers)
{
    inMemberFile.open("MemberInfo.dat", ios::binary); //讀檔 

    while (!inMemberFile.eof()) //若還未到檔案結尾
    {
        //從dat檔內依序讀取並存入各自所屬字串陣列
        inMemberFile.read(memberDetails[numMembers].email, 40);
        inMemberFile.read(memberDetails[numMembers].password, 24);
        inMemberFile.read(memberDetails[numMembers].IDNumber, 12);
        inMemberFile.read(memberDetails[numMembers].name, 12);
        inMemberFile.read(memberDetails[numMembers].phone, 12);
        numMembers++;
    }

    inMemberFile.close(); //讀檔關閉
}

//回傳所輸入的數字
int inputAnInteger(int begin, int end)
{
    int choice;
    cin >> choice; //輸入數字
    if (begin <= choice && choice <= end) //若該數介於begin和end之間
    {
        return choice; //則回傳該數
    }
    else
    {
        return -1; //否則回傳-1
    }
}

//登入，輸入電子信箱及密碼
void login(Member memberDetails[], int numMembers)
{
    Member buffer; //設一暫存來存輸入進來的數
    int recordNumber = 0; //用來紀錄電子信箱及密碼是在memberDetails的哪一列陣列符合
    cout << "Enter email address: ";
    cin >> buffer.email;
    cout << "Enter password: ";
    cin >> buffer.password;
    cout << endl;

    //若輸入的email及password在memberDetails內沒有與之符合的字串
    while (legal(buffer.email, buffer.password, memberDetails, numMembers, recordNumber) == false)
    {
        //則代表輸入錯誤，故再輸入一次
        cout << "Sorry, unrecognized email or password." << endl << endl;
        cout << "Enter email address: ";
        cin >> buffer.email;
        cout << "Enter password: ";
        cin >> buffer.password;
        cout << endl;
    }

    //若以上輸入正確，則代表登入成功，進入以下迴圈
    int choice;
    while (true)
    {
        cout << "Enter your choice:" << endl;
        cout << "1. Account Information\n";
        cout << "2. Buy Tickets\n";
        cout << "3. End\n? ";

        choice = inputAnInteger(1, 3);
        cout << endl;

        switch (choice)
        {
        case 1:
            accountInfor(memberDetails, numMembers, recordNumber);
            break;

        case 2:
            break;

        case 3:
            return;

        default:
            cout << "Input Error!\n\n";
            break;
        }
    }
}

//判斷輸入的電子信箱及密碼是否正確
bool legal(char email[], char password[], Member memberDetails[], int numMembers, int& recordNumber)
{
    for (int k = 0; k < numMembers; k++)
    {
        //若在memberDetails裡某個字串中的email及password皆與傳進來的數值符合
        if (strcmp(email, memberDetails[k].email) == 0 && strcmp(password, memberDetails[k].password) == 0)
        {
            recordNumber = k; //則紀錄該字串所在的陣列編號
            return true; //並且回傳true
        }
    }
    return false; //否則回傳false
}

//印出struct內的資料並處理是否修改資料
void accountInfor(Member memberDetails[], int numMembers, int recordNumber)
{
    cout << "1. Name: " << memberDetails[recordNumber].name << endl;
    cout << "2. Email Address: " << memberDetails[recordNumber].email << endl;
    cout << "3. Phone Number: " << memberDetails[recordNumber].phone << endl;
    cout << "4. ID Number: " << memberDetails[recordNumber].IDNumber << endl;
    cout << "5. Password: " << memberDetails[recordNumber].password << endl;

    int choice;
    cout <<endl<< "Which one do you want to modify (0 – not modify)? ";
    while (true)
    {
        choice = inputAnInteger(0, 5);
        cout << endl;

        //修改資料
        switch (choice)
        {
        case 0:
            return;

        case 1:
            cout << "Enter correct data: ";
            cin >> memberDetails[recordNumber].name;
            cout << endl << "Successful!" << endl << endl;
            return;

        case 2:
            cout << "Enter correct data: ";
            cin >> memberDetails[recordNumber].email;
            cout << endl << "Successful!" << endl << endl;
            return;

        case 3:
            cout << "Enter correct data: ";
            cin >> memberDetails[recordNumber].phone;
            cout << endl << "Successful!" << endl << endl;
            return;

        case 4:
            cout << "Enter correct data: ";
            cin >> memberDetails[recordNumber].IDNumber;
            cout << endl << "Successful!" << endl << endl;
            return;

        case 5:
            cout << "Enter correct data: ";
            cin >> memberDetails[recordNumber].password;
            cout << endl << "Successful!" << endl << endl;
            return;

        default:
            cout << "Input Error! Please try again: ";
            break;
        }
    }
}

//註冊新會員
void newMember(Member memberDetails[], int& numMembers)
{
    Member temp; //設一暫存來存輸入進來的數

    cout << "Enter your ID number: ";
    cin >> temp.IDNumber;

    //若輸入的ID已經存在，則結束函式
    if (existingID(temp.IDNumber, memberDetails, numMembers) == true)
    {
        cout << endl << "An account already exists with the ID number!" << endl << endl;
        return;
    }

    cout << "Enter your name: ";
    cin >> temp.name;

    //若輸入的電子信箱已經存在，則再輸入一次直到該電子信箱沒被註冊過
    do
    {
        cout << "Enter an email address: ";
        cin >> temp.email;
    } while (existingEmail(temp.email, memberDetails, numMembers) == true);

    cout << "Enter a password: ";
    cin >> temp.password;

    cout << "Enter your phone number: ";
    cin >> temp.phone;
    cout << endl;

    memberDetails[numMembers] = temp; //將暫存內的資料存入memberDetails
    numMembers++;
    cout << "Successful!" << endl << endl;
    return;
}

//判別IDNumber是否存在
bool existingID(char newIDNumber[], Member memberDetails[], int& numMembers)
{
    for (int k = 0; k < numMembers; k++)
    {
        //若傳進來的新ID與memberDetails內newIDNumber部分的某筆字串相同
        if (strcmp(memberDetails[k].IDNumber, newIDNumber) == 0)
        {
            return true; //則代表該ID已存在，回傳true
        }
    }
    return false; //否則回傳false
}

//判別Email是否存在
bool existingEmail(char newEmail[], Member memberDetails[], int& numMembers)
{
    for (int k = 0; k < numMembers; k++)
    {
        //若傳進來的新email與memberDetails內email部分的某筆字串相同
        if (strcmp(memberDetails[k].email, newEmail) == 0)
        {
            return true; //則代表該email已存在，回傳true
        }
    }
    return false; //否則回傳false
}

//存檔
void saveMemberInfo(ofstream& outMemberFile, Member memberDetails[], int numMembers)
{
    outMemberFile.open("MemberInfo.dat", ios::binary); //寫檔

    for (int k = 0; k < numMembers; k++)
    {
        //轉換memberDetails的型態後存檔
        outMemberFile.write(reinterpret_cast<const char*>(&memberDetails[k]), sizeof(memberDetails[k]));
    }

    outMemberFile.close(); //寫檔關閉
}
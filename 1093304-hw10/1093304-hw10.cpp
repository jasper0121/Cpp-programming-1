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

//ŪMemberInfo.dat�̪���
void loadMemberInfo(ifstream& inMemberFile, Member memberDetails[], int& numMembers)
{
    inMemberFile.open("MemberInfo.dat", ios::binary); //Ū�� 

    while (!inMemberFile.eof()) //�Y�٥����ɮ׵���
    {
        //�qdat�ɤ��̧�Ū���æs�J�U�۩��ݦr��}�C
        inMemberFile.read(memberDetails[numMembers].email, 40);
        inMemberFile.read(memberDetails[numMembers].password, 24);
        inMemberFile.read(memberDetails[numMembers].IDNumber, 12);
        inMemberFile.read(memberDetails[numMembers].name, 12);
        inMemberFile.read(memberDetails[numMembers].phone, 12);
        numMembers++;
    }

    inMemberFile.close(); //Ū������
}

//�^�ǩҿ�J���Ʀr
int inputAnInteger(int begin, int end)
{
    int choice;
    cin >> choice; //��J�Ʀr
    if (begin <= choice && choice <= end) //�Y�ӼƤ���begin�Mend����
    {
        return choice; //�h�^�ǸӼ�
    }
    else
    {
        return -1; //�_�h�^��-1
    }
}

//�n�J�A��J�q�l�H�c�αK�X
void login(Member memberDetails[], int numMembers)
{
    Member buffer; //�]�@�Ȧs�Ӧs��J�i�Ӫ���
    int recordNumber = 0; //�ΨӬ����q�l�H�c�αK�X�O�bmemberDetails�����@�C�}�C�ŦX
    cout << "Enter email address: ";
    cin >> buffer.email;
    cout << "Enter password: ";
    cin >> buffer.password;
    cout << endl;

    //�Y��J��email��password�bmemberDetails���S���P���ŦX���r��
    while (legal(buffer.email, buffer.password, memberDetails, numMembers, recordNumber) == false)
    {
        //�h�N���J���~�A�G�A��J�@��
        cout << "Sorry, unrecognized email or password." << endl << endl;
        cout << "Enter email address: ";
        cin >> buffer.email;
        cout << "Enter password: ";
        cin >> buffer.password;
        cout << endl;
    }

    //�Y�H�W��J���T�A�h�N��n�J���\�A�i�J�H�U�j��
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

//�P�_��J���q�l�H�c�αK�X�O�_���T
bool legal(char email[], char password[], Member memberDetails[], int numMembers, int& recordNumber)
{
    for (int k = 0; k < numMembers; k++)
    {
        //�Y�bmemberDetails�̬Y�Ӧr�ꤤ��email��password�һP�Ƕi�Ӫ��ƭȲŦX
        if (strcmp(email, memberDetails[k].email) == 0 && strcmp(password, memberDetails[k].password) == 0)
        {
            recordNumber = k; //�h�����Ӧr��Ҧb���}�C�s��
            return true; //�åB�^��true
        }
    }
    return false; //�_�h�^��false
}

//�L�Xstruct������ƨóB�z�O�_�ק���
void accountInfor(Member memberDetails[], int numMembers, int recordNumber)
{
    cout << "1. Name: " << memberDetails[recordNumber].name << endl;
    cout << "2. Email Address: " << memberDetails[recordNumber].email << endl;
    cout << "3. Phone Number: " << memberDetails[recordNumber].phone << endl;
    cout << "4. ID Number: " << memberDetails[recordNumber].IDNumber << endl;
    cout << "5. Password: " << memberDetails[recordNumber].password << endl;

    int choice;
    cout <<endl<< "Which one do you want to modify (0 �V not modify)? ";
    while (true)
    {
        choice = inputAnInteger(0, 5);
        cout << endl;

        //�ק���
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

//���U�s�|��
void newMember(Member memberDetails[], int& numMembers)
{
    Member temp; //�]�@�Ȧs�Ӧs��J�i�Ӫ���

    cout << "Enter your ID number: ";
    cin >> temp.IDNumber;

    //�Y��J��ID�w�g�s�b�A�h�����禡
    if (existingID(temp.IDNumber, memberDetails, numMembers) == true)
    {
        cout << endl << "An account already exists with the ID number!" << endl << endl;
        return;
    }

    cout << "Enter your name: ";
    cin >> temp.name;

    //�Y��J���q�l�H�c�w�g�s�b�A�h�A��J�@������ӹq�l�H�c�S�Q���U�L
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

    memberDetails[numMembers] = temp; //�N�Ȧs������Ʀs�JmemberDetails
    numMembers++;
    cout << "Successful!" << endl << endl;
    return;
}

//�P�OIDNumber�O�_�s�b
bool existingID(char newIDNumber[], Member memberDetails[], int& numMembers)
{
    for (int k = 0; k < numMembers; k++)
    {
        //�Y�Ƕi�Ӫ��sID�PmemberDetails��newIDNumber�������Y���r��ۦP
        if (strcmp(memberDetails[k].IDNumber, newIDNumber) == 0)
        {
            return true; //�h�N���ID�w�s�b�A�^��true
        }
    }
    return false; //�_�h�^��false
}

//�P�OEmail�O�_�s�b
bool existingEmail(char newEmail[], Member memberDetails[], int& numMembers)
{
    for (int k = 0; k < numMembers; k++)
    {
        //�Y�Ƕi�Ӫ��semail�PmemberDetails��email�������Y���r��ۦP
        if (strcmp(memberDetails[k].email, newEmail) == 0)
        {
            return true; //�h�N���email�w�s�b�A�^��true
        }
    }
    return false; //�_�h�^��false
}

//�s��
void saveMemberInfo(ofstream& outMemberFile, Member memberDetails[], int numMembers)
{
    outMemberFile.open("MemberInfo.dat", ios::binary); //�g��

    for (int k = 0; k < numMembers; k++)
    {
        //�ഫmemberDetails�����A��s��
        outMemberFile.write(reinterpret_cast<const char*>(&memberDetails[k]), sizeof(memberDetails[k]));
    }

    outMemberFile.close(); //�g������
}
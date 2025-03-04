#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;

struct MemberRecord
{
    char email[40];
    char password[24];
    char IDNumber[12];
    char name[12];
    char phone[12];
};

struct Movie
{
    int movieCode;
    int prices[4]; // prices[0]:adult, prices[1]:concession, prices[2]:disability, prices[3]:elderly
    bool dates[9]; // dates[i] is true if and only if the movie is available on i-th date
    bool sessionTimes[17]; // sessionTimes[i] is true if and only if the movie is available on i-th session
    bool occupiedSeats[9][17][8][12]; // occupiedSeats[i][j] is the occupied Seats for all accounts
};                                           // at j-th session time on i-th date

struct BookingInfo
{
    char email[40];
    int movieCode;
    int dateCode;
    int sessionTimeCode;
    int numTickets[4]; // numTickets[0]: the number of adult tickets,
                         // numTickets[1]: the number of concession tickets,
                         // numTickets[2]: the number of disability tickets,
                         // numTickets[3]: the number of elderly tickets
    char seletedSeats[24][4]; // seleted seats for the user with the specified email
};

char hours[17][8] = { "09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00", "17:00",
                          "18:00", "19:00", "20:00", "21:00", "22:00", "23:00", "00:00", "01:00" };

void loadMemberInfo(MemberRecord memberDetails[], int& numMembers);
void loadBookingHistories(BookingInfo bookingHistories[], int& numBookings);
void loadMovies(Movie movies[], int& numMovies);
void loadMovieNames(char movieNames[][60], int numMovies);
void loadAvailableDates(char availableDates[][12], int& numDates);

int inputAnInteger(int begin, int end);
void signIn(MemberRecord memberDetails[], int numMembers, Movie movies[], char movieNames[][60], int numMovies,
    BookingInfo bookingHistories[], int& numBookings, char availableDates[][12], int numDates);
bool illegal(char email[], char password[], MemberRecord memberDetails[], int numMembers, int& recordNumber);
void accountInfor(MemberRecord memberDetails[], int numMembers, int recordNumber);

void buyTickets(BookingInfo bookingHistories[], int& numBookings, Movie movies[], char movieNames[][60],
    int numMovies, char availableDates[][12], int numDates, char email[]);
void selectSeats(BookingInfo bookingHistories[], int numBookings, Movie movies[]);

void displaySessionTimes(Movie movies[], char movieNames[][60], int numMovies,
    char availableDates[][12], int numDates);
void display(Movie movies[], BookingInfo bookingHistory);
void displayBookingHistory(BookingInfo bookingHistories[], int numBookings, Movie movies[],
    char movieNames[][60], char availableDates[][12], char email[]);

void newMember(MemberRecord memberDetails[], int& numMembers);
bool existingID(char newIDNumber[], MemberRecord memberDetails[], int& numMembers);
bool existingEmail(char newEmail[], MemberRecord memberDetails[], int& numMembers);

void saveMemberInfo(MemberRecord memberDetails[], int numMembers);
void saveMovies(Movie movies[], int numMovies);
void saveBookingHistories(BookingInfo bookingHistories[], int numBookings);

int main()
{
    MemberRecord memberDetails[100] = {};
    int numMembers = 0;
    loadMemberInfo(memberDetails, numMembers);

    BookingInfo bookingHistories[1000] = {};
    int numBookings = 0;
    loadBookingHistories(bookingHistories, numBookings);

    Movie movies[30] = {};
    int numMovies = 0;
    loadMovies(movies, numMovies);

    char movieNames[30][60] = {};
    loadMovieNames(movieNames, numMovies);

    char availableDates[10][12];
    int numDates;
    loadAvailableDates(availableDates, numDates);

    cout << "Welcome to Vieshow Cinemas Taipei QSquare system\n";

    int choice;

    while (true)
    {
        cout << "\n1. Sign In\n";
        cout << "2. New Member\n";
        cout << "3. End\n";

        do cout << "\nEnter your choice (1~3): ";
        while ((choice = inputAnInteger(1, 3)) == -1);
        cout << endl;

        switch (choice)
        {
        case 1:
            signIn(memberDetails, numMembers, movies, movieNames, numMovies,
                bookingHistories, numBookings, availableDates, numDates);
            break;

        case 2:
            newMember(memberDetails, numMembers);
            break;

        case 3:
            saveMemberInfo(memberDetails, numMembers);
            saveMovies(movies, numMovies);
            saveBookingHistories(bookingHistories, numBookings);
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

//(1)�qMember Info.dat��Ū���ӤH���
void loadMemberInfo(MemberRecord memberDetails[], int& numMembers)
{
    ifstream inFile("Member Info.dat", ios::binary); //Ū�� 

    if (!inFile) //�Y�SŪ����
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    //�qdat�ɤ�Ū����ơA�ഫ���A��s�JmemberDetails
    while (inFile.read(reinterpret_cast<char*>(&memberDetails[numMembers]), sizeof(memberDetails[numMembers])))
    {
        numMembers++;
    }

    inFile.close(); //Ū������
}

//(2)�qBooking Histories.dat��Ū���q�����v����
void loadBookingHistories(BookingInfo bookingHistories[], int& numBookings)
{
    ifstream inFile("Booking Histories.dat", ios::binary); //Ū�� 

    if (!inFile) //�Y�SŪ����
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    //�qdat�ɤ�Ū����ơA�ഫ���A��s�JbookingHistories
    while (inFile.read(reinterpret_cast<char*>(&bookingHistories[numBookings]), sizeof(bookingHistories[numBookings])))
    {
        numBookings++;
    }

    inFile.close(); //Ū������
}

//(3)�qMovies.dat��Ū���q�v������T
void loadMovies(Movie movies[], int& numMovies)
{
    ifstream inFile("Movies.dat", ios::binary); //Ū�� 

    if (!inFile) //�Y�SŪ����
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    //�qdat�ɤ�Ū����ơA�ഫ���A��s�JbookingHistories
    while (inFile.read(reinterpret_cast<char*>(&movies[numMovies]), sizeof(movies[numMovies])))
    {
        numMovies++;
    }

    inFile.close(); //Ū������
}

//(4)�qMovie Names.txt��Ū���q�v�W��
void loadMovieNames(char movieNames[][60], int numMovies)
{
    ifstream inFile("Movie Names.txt"); //Ū��

    if (!inFile) //�Y�SŪ����
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    for (int number = 0; number < numMovies; number++)
    {
        inFile.getline(movieNames[number], 60, '\n'); //�N�q�v�W�٤@��@��aŪ�JmovieNames
    }

    inFile.close(); //Ū������
}

//(5)�qAvailable Dates.txt��Ū������B����άP��
void loadAvailableDates(char availableDates[][12], int& numDates)
{
    ifstream inFile("Available Dates.txt"); //Ū��

    if (!inFile) //�Y�SŪ����
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    numDates = 0; //��l��(�]�bmain�̫ŧi�ɥ���l��)
    while (inFile.getline(availableDates[numDates], 12, '\n')) //�N����B����άP���@��@��aŪ�JavailableDates
    {
        numDates++;
    }

    inFile.close(); //Ū������
}

//(6)���b����
int inputAnInteger(int begin, int end)
{
    char choice[10]; //�s��J�i�Ӫ����
    int number = 0; //�schoice�̪��Ʀr�r��

    cin.getline(choice, 10, '\n'); //�Ͽ�J���Ů�i�H�Q�s�J�r���}�C

    if (choice[0] == '\0') //�Y����J�r���Ӫ�����Enter
    {
        return -1; //�h��J���w���~�A�G�^��-1
    }

    for (int k = 0; choice[k] != '\0'; k++)
    {
        //�Y�Ӯ�}�C���D�Ʀr�r���ΪŦr���e�}�C��Ƥj��2��(�]�H�W���Ψ즹�禡�ҶǶi�Ӫ�end�̦h��Q���)
        if (!('0' <= choice[k] && choice[k] <= '9') || strlen(choice) > 2)
        {
            return -1; //�h��J���w���~�A�G�^��-1
        }

        if (choice[k + 1] != '\0') //�Y�U�@��D�Ŧr��
        {
            number += (choice[k] - '0') * 10; //�h�N���欰�Q��ơA�Nchar�ରint�᭼10�s�Jnumber
        }
        else
        {
            number += choice[k] - '0'; //�_�h�N���欰�Ӧ�ơA�Nchar�ରint��s�Jnumber
        }
    }

    if (begin <= number && number <= end) //�Y��J�i�Ӫ���(number)����begin�Mend����
    {
        return number; //�h�^��number
    }
    else
    {
        return -1; //�_�h�^��-1
    }
}

//(7)�n�J
void signIn(MemberRecord memberDetails[], int numMembers, Movie movies[], char movieNames[][60], int numMovies,
    BookingInfo bookingHistories[], int& numBookings, char availableDates[][12], int numDates)
{
    MemberRecord temp; //�]�@�Ȧs�Ӧs��J�i�Ӫ���
    int recordNumber = 0; //�ΨӬ����q�l�H�c�αK�X�O�bmemberDetails�����@�C�}�C�ŦX

    do //�Y��J��email��password�bmemberDetails���S���P���ŦX���r��A�h�N���J���~�A�G�A��J�@��
    {
        do //�Y����J�r���Ӫ�����Enter�A�h���s��J
        {
            cout << "Enter email address: ";
            cin.getline(temp.email, 40, '\n');
        } while (temp.email[0] == '\0');

        do //�Y����J�r���Ӫ�����Enter�A�h���s��J
        {
            cout << "Enter password: ";
            cin.getline(temp.password, 24, '\n');
        } while (temp.password[0] == '\0');
        cout << endl;
    } while (illegal(temp.email, temp.password, memberDetails, numMembers, recordNumber) == false);

    //�Y�H�W��J���T�A�h�N��n�J���\�A�i�J�H�U�j��
    int choice;
    while (true)
    {
        cout << "1. Account Information" << endl;
        cout << "2. Buy Tickets" << endl;
        cout << "3. My Bookings" << endl;
        cout << "4. Sign Out" << endl;

        do
        {
            cout << endl << "Enter your choice (1~4): ";
        } while ((choice = inputAnInteger(1, 4)) == -1);

        switch (choice)
        {
        case 1:
            cout << endl;
            accountInfor(memberDetails, numMembers, recordNumber); //�L�X�ӤH��ƨóB�z�O�_�ק���
            break;

        case 2:
            cout << endl;
            buyTickets(bookingHistories, numBookings, movies, movieNames, numMovies, availableDates, numDates, temp.email); //�q���t��
            break;

        case 3:
            cout << endl;
            displayBookingHistory(bookingHistories, numBookings, movies, movieNames, availableDates, temp.email); //�L�X�q�L�h��{�b���Ҧ��ʲ�����
            break;

        case 4:
            return; //�n�X
        }
    }
}

//(8)�P�_��J���q�l�H�c�αK�X�O�_���T
bool illegal(char email[], char password[], MemberRecord memberDetails[], int numMembers, int& recordNumber)
{
    for (int k = 0; k < numMembers; k++)
    {
        //�Y�bmemberDetails�̬Y�C�}�C����email��password�һP�Ƕi�Ӫ��r��ŦX
        if (strcmp(email, memberDetails[k].email) == 0 && strcmp(password, memberDetails[k].password) == 0)
        {
            recordNumber = k; //�h�����Ӧr��Ҧb���}�C�s��
            return true; //�åB�^��true
        }
    }
    cout << "Sorry, unrecognized email or password." << endl << endl;
    return false; //�_�h�^��false
}

//(9)�L�X�ӤH��ƨóB�z�O�_�ק���
void accountInfor(MemberRecord memberDetails[], int numMembers, int recordNumber)
{
    //�L�X�ӤH���
    cout << "1. Name: " << memberDetails[recordNumber].name << endl;
    cout << "2. Email Address: " << memberDetails[recordNumber].email << endl;
    cout << "3. Phone Number: " << memberDetails[recordNumber].phone << endl;
    cout << "4. ID Number: " << memberDetails[recordNumber].IDNumber << endl;
    cout << "5. Password: " << memberDetails[recordNumber].password << endl;

    int choice;
    cout << endl << "Which one do you want to modify (0 �V not modify)? ";
    while (true)
    {
        choice = inputAnInteger(0, 5);
        cout << endl;

        //�ק�ӤH���
        switch (choice)
        {
        case 0:
            return;

        case 1:
            do //�Y����J�r���Ӫ�����Enter�A�h���s��J
            {
                cout << "Enter correct data: ";
                cin.getline(memberDetails[recordNumber].name, 12, '\n');
            } while (memberDetails[recordNumber].name[0] == '\0');
            cout << endl << "Successful!" << endl << endl;
            return;

        case 2:
            do //�Y����J�r���Ӫ�����Enter�A�h���s��J
            {
                cout << "Enter correct data: ";
                cin.getline(memberDetails[recordNumber].email, 40, '\n');
            } while (memberDetails[recordNumber].email[0] == '\0');
            cout << endl << "Successful!" << endl << endl;
            return;

        case 3:
            do //�Y����J�r���Ӫ�����Enter�A�h���s��J
            {
                cout << "Enter correct data: ";
                cin.getline(memberDetails[recordNumber].phone, 12, '\n');
            } while (memberDetails[recordNumber].phone[0] == '\0');
            cout << endl << "Successful!" << endl << endl;
            return;

        case 4:
            do //�Y����J�r���Ӫ�����Enter�A�h���s��J
            {
                cout << "Enter correct data: ";
                cin.getline(memberDetails[recordNumber].IDNumber, 12, '\n');
            } while (memberDetails[recordNumber].IDNumber[0] == '\0');
            cout << endl << "Successful!" << endl << endl;
            return;

        case 5:
            do //�Y����J�r���Ӫ�����Enter�A�h���s��J
            {
                cout << "Enter correct data: ";
                cin.getline(memberDetails[recordNumber].password, 24, '\n');
            } while (memberDetails[recordNumber].password[0] == '\0');
            cout << endl << "Successful!" << endl << endl;
            return;

        default:
            cout << "Input Error! Please try again: ";
            break;
        }
    }
}

//(10)�q���t��
void buyTickets(BookingInfo bookingHistories[], int& numBookings, Movie movies[], char movieNames[][60],
    int numMovies, char availableDates[][12], int numDates, char email[])
{
    displaySessionTimes(movies, movieNames, numMovies, availableDates, numDates); //�L�X�Ҧ��q�v�W�١B����ήɶ�

    int choice_movie; //��ܹq�v
    int choice_date; //��ܤ��
    int choice_time; //��ܮɶ�

    do //�Y��ܪ��q�v�N�����b�d�򤺡A�h���s��J
    {
        cout << "Enter movie code (0 - 11): ";
    } while ((choice_movie = inputAnInteger(0, 11)) == -1);
    bookingHistories[numBookings].movieCode = choice_movie; //�N�ҿ諸�q�v�N���g�J�q��������
    cout << endl;

    do //�Y��ܪ�����N�����b�d��or�ҿ諸����ӹq�v����M�A�h���s��J
    {
        cout << "Enter date code (0 - 8): ";
    } while ((choice_date = inputAnInteger(0, 8)) == -1 || movies[choice_movie].dates[choice_date] == false);
    bookingHistories[numBookings].dateCode = choice_date; //�N�ҿ諸����N���g�J�q��������
    cout << endl;

    do //�Y��ܪ��ɶ��N�����b�d��or�ҿ諸�ɶ��ӹq�v����M�A�h���s��J
    {
        cout << "Enter session time code (0 - 16): ";
    } while ((choice_time = inputAnInteger(0, 16)) == -1 || movies[choice_movie].sessionTimes[choice_time] == false);
    bookingHistories[numBookings].sessionTimeCode = choice_time; //�N�ҿ諸�ɶ��N���g�J�q��������
    cout << endl;

    //�L�X�ҿ諸�q�v�B����M�ɶ��B�æL�X�i�諸4�ز���
    cout << "Movie: " << movieNames[choice_movie] << endl;
    cout << "Date: " << availableDates[choice_date] << endl;
    cout << "Show Time: " << hours[choice_time] << endl;
    cout << "Price: Adult-" << movies[choice_movie].prices[0] << ", Concession-" << movies[choice_movie].prices[1]
        << ", Disability-" << movies[choice_movie].prices[2] << ", Elderly-" << movies[choice_movie].prices[3] << endl << endl;

    int total_movie_tickets = 0; //�����@�R�F�X�i��
    do
    {
        for (int k = 0; k < 4; k++) //�̧Ǹ߰ݸӲ��حn�R�X�i
        {
            do //�Y�ҿ�ܪ����Ƥ��b�d�򤺡A�h���s��J
            {
                if (k == 0)
                {
                    cout << "Enter the number of adult tickets (0 - 6): ";
                }
                if (k == 1)
                {
                    cout << "Enter the number of concession tickets (0 - 6): ";
                }
                if (k == 2)
                {
                    cout << "Enter the number of disability tickets (0 - 6): ";
                }
                if (k == 3)
                {
                    cout << "Enter the number of elderly tickets (0 - 6): ";
                }
            } while ((bookingHistories[numBookings].numTickets[k] = inputAnInteger(0, 6)) == -1);
            total_movie_tickets += bookingHistories[numBookings].numTickets[k]; //������e�@�R�F�X�i��
        }
        cout << endl;
    } while (total_movie_tickets == 0); //�Y�`�@�R�F0�i���A�h���s��J

    display(movies, bookingHistories[numBookings]); //�L�X�Ӧ��ʶR�����ؤλ���
    selectSeats(bookingHistories, numBookings, movies); //��ܮy��

    for (int i = 0; i < strlen(email) + 1; i++) //�N�����q����email�b���g�J�ʲ�������(strlen(email) + 1==�r�����+1��'\0')
    {
        bookingHistories[numBookings].email[i] = email[i];
    }
    numBookings++; //�]�W�[�F�@���q�������A�GnumBookings+1
}

//(11)��ܮy��
void selectSeats(BookingInfo bookingHistories[], int numBookings, Movie movies[])
{
    int total_movie_tickets = 0; //�N��@�R�F�X�i��
    char row[8]{ '0','1','2','3','4','5','6','7' }; //����
    char column[12]{ 'A','B','C' ,'D' ,'E' ,'F' ,'G' ,'H' ,'I' ,'J' ,'K' ,'L' }; //��C

    for (int k = 0; k < 4; k++) //��X�@�R�F�X�i��
    {
        total_movie_tickets += bookingHistories[numBookings].numTickets[k];
    }

    cout << " ";
    for (int i = 0; i < 12; i++) //�L�XA~L��
    {
        cout << " " << column[i];
    }
    cout << endl;

    for (int r = 0; r < 8; r++)
    {
        cout << row[r]; //�L�X0~7��
        for (int c = 0; c < 12; c++) //�L�X�y���
        {
            //movies[�q�v�N��].occupiedSeats[���][�ɶ�][��][�C]
            cout << " " << movies[bookingHistories[numBookings].movieCode].occupiedSeats
                [bookingHistories[numBookings].dateCode][bookingHistories[numBookings].sessionTimeCode][r][c];
        }
        cout << endl;
    }

    //��ܮy��
    cout << endl << "Select " << total_movie_tickets << " seats (e.g. 0A):" << endl;
    for (int s = 0; s < total_movie_tickets; s++) //�R�X�i���N��X�Ӧ�m
    {
        cout << "? ";
        while (true)
        {
            cin.getline(bookingHistories[numBookings].seletedSeats[s], 4, '\n'); //��J�y��

            //�Y�Ŧr���e�r�����==2(�y������1�Ʀr+1�j�g�^��r��)�A�B��J���Ȧb�d��(�^�Ƥ��i�A��)
            if (strlen(bookingHistories[numBookings].seletedSeats[s]) == 2
                && ('0' <= bookingHistories[numBookings].seletedSeats[s][0] && bookingHistories[numBookings].seletedSeats[s][0] <= '7'
                    && 'A' <= bookingHistories[numBookings].seletedSeats[s][1] && bookingHistories[numBookings].seletedSeats[s][1] <= 'L'))
            {
                //�Y��ܪ��y���٥��Q�q��
                if (movies[bookingHistories[numBookings].movieCode].occupiedSeats
                    [bookingHistories[numBookings].dateCode][bookingHistories[numBookings].sessionTimeCode]
                    [bookingHistories[numBookings].seletedSeats[s][0] - '0'][bookingHistories[numBookings].seletedSeats[s][1] - 'A'] == 0)
                {
                    //�h�N�Ӯy������m�אּ1(�Y�����q�즨�\)
                    movies[bookingHistories[numBookings].movieCode].occupiedSeats
                        [bookingHistories[numBookings].dateCode][bookingHistories[numBookings].sessionTimeCode]
                        [bookingHistories[numBookings].seletedSeats[s][0] - '0'][bookingHistories[numBookings].seletedSeats[s][1] - 'A'] = 1;
                    break; //�Ӧ��q�즨�\��Y���Xwhile�j��
                }
                else
                {
                    cout << endl << "This seat has been occupied. Please select another seat." << endl << "? "; //�_�h�|�bwhile�j�餺�A��J�@�������J���T
                }
            }
            else
            {
                cout << endl << "Input Error! Please try again: " << endl << "? "; //�_�h�|�bwhile�j�餺�A��J�@�������J���T
            }
        }
    }
    cout << endl << "Successful!" << endl << endl;
}

//(12)�L�X�Ҧ��q�v�W�١B����ήɶ�
void displaySessionTimes(Movie movies[], char movieNames[][60], int numMovies,
    char availableDates[][12], int numDates)
{
    for (int movie = 0; movie < numMovies; movie++)
    {
        if (movie < 10)
        {
            cout << " " << movie << ". Movie: " << movieNames[movie] << endl;
        }
        else
        {
            cout << movie << ". Movie: " << movieNames[movie] << endl;
        }

        cout << "    Date:";
        for (int date = 0; date < numDates; date++)
        {
            if (movies[movie].dates[date] == true)
            {
                cout << "  " << date << ". " << availableDates[date] << ", ";
            }
        }

        cout << endl << "    Session Time:";
        for (int time = 0; time < 17; time++)
        {
            if (movies[movie].sessionTimes[time] == true)
            {
                cout << "  " << time << ". " << hours[time] << ",";
            }
        }
        cout << endl << endl;
    }
}

//(13)�L�X�ʶR�����ؤλ���
void display(Movie movies[], BookingInfo bookingHistory)
{
    int total = 0; //�N��q���`���B
    cout << "             No. of Tickets  Price  Subtotal" << endl;
    for (int i = 0; i < 4; i++)
    {
        if (bookingHistory.numTickets[i] != 0)
        {
            if (i == 0)
            {
                cout << "Adult ticket              " << bookingHistory.numTickets[i] << "    ";
            }
            if (i == 1)
            {
                cout << "Concession ticket         " << bookingHistory.numTickets[i] << "    ";
            }
            if (i == 2)
            {
                cout << "Disability ticket         " << bookingHistory.numTickets[i] << "    ";
            }
            if (i == 3)
            {
                cout << "Elderly ticket            " << bookingHistory.numTickets[i] << "    ";
            }
            cout << movies[bookingHistory.movieCode].prices[i] << "       "; //�L�X�ҿ�q�v�����س��
            cout << bookingHistory.numTickets[i] * movies[bookingHistory.movieCode].prices[i] << endl; //�L�X�Ӳ��ؤp�p
            total += bookingHistory.numTickets[i] * movies[bookingHistory.movieCode].prices[i]; //�N�Ӳ��ؤp�p�[�J�q���`���B��
        }
    }
    cout << endl << "Total Amount For Tickets: " << total << endl << endl; //�L�X�`���B
}

//(14)�L�X�ӱb��(email)�q�L�h��{�b���Ҧ��ʲ�����
void displayBookingHistory(BookingInfo bookingHistories[], int numBookings, Movie movies[],
    char movieNames[][60], char availableDates[][12], char email[])
{
    int counter = 0; //�p�ƾ��A�p���email�b���b�L�h���X���q������

    for (int n = 0; n < numBookings; n++)
    {
        if (strcmp(bookingHistories[n].email, email) == 0) //�Y�n�J��email�b���ŦX�ӵ��q����������email�b��
        {
            //�h�C�X�ӵ��q������
            cout << "Booking History:" << endl << endl;
            cout << "Movie: " << movieNames[bookingHistories[n].movieCode] << endl;
            cout << "Date: " << availableDates[bookingHistories[n].dateCode] << endl;
            cout << "Show Time: " << hours[bookingHistories[n].sessionTimeCode] << endl;
            cout << "Seats: ";
            for (int s = 0; s < 24; s++)
            {
                cout << bookingHistories[n].seletedSeats[s] << "  ";
            }
            cout << endl << endl;
            display(movies, bookingHistories[n]); //�L�X�ʶR�����ؤλ���
            cout << "----------------------------------------------" << endl << endl;
            counter++; //�p�ƾ�+1
        }
    }

    if (counter == 0) //�Y�p�ƾ�==0�A�h�N��email�b���S���q������
    {
        cout << "No bookings!" << endl << endl;
    }
}

//(15)�[�J�s�|��
void newMember(MemberRecord memberDetails[], int& numMembers)
{
    do //�Y����J�r���Ӫ�����Enter�A�h���s��J
    {
        cout << "Enter your ID number: ";
        cin.getline(memberDetails[numMembers].IDNumber, 12, '\n');
    } while (memberDetails[numMembers].IDNumber[0] == '\0');

    if (existingID(memberDetails[numMembers].IDNumber, memberDetails, numMembers) == true) //�Y��J��ID�w�g�s�b�A�h�����禡
    {
        cout << endl << "An account already exists with the ID number!" << endl;
        return;
    }

    do //�Y����J�r���Ӫ�����Enter�A�h���s��J
    {
        cout << "Enter your name: ";
        cin.getline(memberDetails[numMembers].name, 12, '\n');
    } while (memberDetails[numMembers].name[0] == '\0');


    while (true) //�Y��J���q�l�H�c�w�g�s�b�A�h�A��J�@������ӹq�l�H�c�S�Q���U�L
    {
        do //�Y����J�r���Ӫ�����Enter�A�h���s��J
        {
            cout << "Enter an email address: ";
            cin.getline(memberDetails[numMembers].email, 40, '\n');
        } while (memberDetails[numMembers].email[0] == '\0');

        if (existingEmail(memberDetails[numMembers].email, memberDetails, numMembers) == true)
        {
            cout << endl << "An account already exists with the e-mail!" << endl << endl;
        }
        else
        {
            break;
        }
    }

    do //�Y����J�r���Ӫ�����Enter�A�h���s��J
    {
        cout << "Enter a password: ";
        cin.getline(memberDetails[numMembers].password, 24, '\n');
    } while (memberDetails[numMembers].password[0] == '\0');

    do //�Y����J�r���Ӫ�����Enter�A�h���s��J
    {
        cout << "Enter your phone number: ";
        cin.getline(memberDetails[numMembers].phone, 12, '\n');
    } while (memberDetails[numMembers].phone[0] == '\0');

    numMembers++; //�]�W�[�F�@���s�|����ơA�GnumMembers+1
    cout << endl << "Successful!" << endl;
}

//(16)�P�OIDNumber�O�_�s�b
bool existingID(char newIDNumber[], MemberRecord memberDetails[], int& numMembers)
{
    for (int k = 0; k < numMembers; k++)
    {
        if (strcmp(memberDetails[k].IDNumber, newIDNumber) == 0) //�Y�Ƕi�Ӫ��sID�PmemberDetails��newIDNumber�������Y���r��ۦP
        {
            return true; //�h�N���ID�w�s�b�A�^��true
        }
    }
    return false; //�_�h�^��false
}

//(17)�P�OEmail�O�_�s�b
bool existingEmail(char newEmail[], MemberRecord memberDetails[], int& numMembers)
{
    for (int k = 0; k < numMembers; k++)
    {
        if (strcmp(memberDetails[k].email, newEmail) == 0) //�Y�Ƕi�Ӫ��semail�PmemberDetails��email�������Y���r��ۦP
        {
            return true; //�h�N���email�w�s�b�A�^��true
        }
    }
    return false; //�_�h�^��false
}

//(18)�s���|�����
void saveMemberInfo(MemberRecord memberDetails[], int numMembers)
{
    ofstream outFile("Member Info.dat", ios::binary); //�g��

    for (int k = 0; k < numMembers; k++)
    {
        outFile.write(reinterpret_cast<const char*>(&memberDetails[k]), sizeof(memberDetails[k])); //�ഫmemberDetails�����A��s��
    }

    outFile.close(); //�g������
}

//(19)�s���q�v������T
void saveMovies(Movie movies[], int numMovies)
{
    ofstream outFile("Movies.dat", ios::binary); //�g��

    for (int k = 0; k < numMovies; k++)
    {
        outFile.write(reinterpret_cast<const char*>(&movies[k]), sizeof(movies[k])); //�ഫmovies�����A��s��
    }

    outFile.close(); //�g������
}

//(20)�s���q�����v����
void saveBookingHistories(BookingInfo bookingHistories[], int numBookings)
{
    ofstream outFile("Booking Histories.dat", ios::binary); //�g��

    for (int k = 0; k < numBookings; k++)
    {
        outFile.write(reinterpret_cast<const char*>(&bookingHistories[k]), sizeof(bookingHistories[k])); //�ഫbookingHistories�����A��s��
    }
    outFile.close(); //�g������
}

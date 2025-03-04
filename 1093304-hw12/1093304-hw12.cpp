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

//(1)從Member Info.dat內讀取個人資料
void loadMemberInfo(MemberRecord memberDetails[], int& numMembers)
{
    ifstream inFile("Member Info.dat", ios::binary); //讀檔 

    if (!inFile) //若沒讀到檔
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    //從dat檔內讀取資料，轉換型態後存入memberDetails
    while (inFile.read(reinterpret_cast<char*>(&memberDetails[numMembers]), sizeof(memberDetails[numMembers])))
    {
        numMembers++;
    }

    inFile.close(); //讀檔關閉
}

//(2)從Booking Histories.dat內讀取訂票歷史紀錄
void loadBookingHistories(BookingInfo bookingHistories[], int& numBookings)
{
    ifstream inFile("Booking Histories.dat", ios::binary); //讀檔 

    if (!inFile) //若沒讀到檔
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    //從dat檔內讀取資料，轉換型態後存入bookingHistories
    while (inFile.read(reinterpret_cast<char*>(&bookingHistories[numBookings]), sizeof(bookingHistories[numBookings])))
    {
        numBookings++;
    }

    inFile.close(); //讀檔關閉
}

//(3)從Movies.dat內讀取電影相關資訊
void loadMovies(Movie movies[], int& numMovies)
{
    ifstream inFile("Movies.dat", ios::binary); //讀檔 

    if (!inFile) //若沒讀到檔
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    //從dat檔內讀取資料，轉換型態後存入bookingHistories
    while (inFile.read(reinterpret_cast<char*>(&movies[numMovies]), sizeof(movies[numMovies])))
    {
        numMovies++;
    }

    inFile.close(); //讀檔關閉
}

//(4)從Movie Names.txt內讀取電影名稱
void loadMovieNames(char movieNames[][60], int numMovies)
{
    ifstream inFile("Movie Names.txt"); //讀檔

    if (!inFile) //若沒讀到檔
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    for (int number = 0; number < numMovies; number++)
    {
        inFile.getline(movieNames[number], 60, '\n'); //將電影名稱一行一行地讀入movieNames
    }

    inFile.close(); //讀檔關閉
}

//(5)從Available Dates.txt內讀取月份、日期及星期
void loadAvailableDates(char availableDates[][12], int& numDates)
{
    ifstream inFile("Available Dates.txt"); //讀檔

    if (!inFile) //若沒讀到檔
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    numDates = 0; //初始化(因在main裡宣告時未初始化)
    while (inFile.getline(availableDates[numDates], 12, '\n')) //將月份、日期及星期一行一行地讀入availableDates
    {
        numDates++;
    }

    inFile.close(); //讀檔關閉
}

//(6)防呆機制
int inputAnInteger(int begin, int end)
{
    char choice[10]; //存輸入進來的資料
    int number = 0; //存choice裡的數字字元

    cin.getline(choice, 10, '\n'); //使輸入的空格可以被存入字元陣列

    if (choice[0] == '\0') //若不輸入字元而直接按Enter
    {
        return -1; //則輸入必定錯誤，故回傳-1
    }

    for (int k = 0; choice[k] != '\0'; k++)
    {
        //若該格陣列內非數字字元或空字元前陣列格數大於2格(因以上須用到此函式所傳進來的end最多到十位數)
        if (!('0' <= choice[k] && choice[k] <= '9') || strlen(choice) > 2)
        {
            return -1; //則輸入必定錯誤，故回傳-1
        }

        if (choice[k + 1] != '\0') //若下一格非空字元
        {
            number += (choice[k] - '0') * 10; //則代表此格為十位數，將char轉為int後乘10存入number
        }
        else
        {
            number += choice[k] - '0'; //否則代表此格為個位數，將char轉為int後存入number
        }
    }

    if (begin <= number && number <= end) //若輸入進來的數(number)介於begin和end之間
    {
        return number; //則回傳number
    }
    else
    {
        return -1; //否則回傳-1
    }
}

//(7)登入
void signIn(MemberRecord memberDetails[], int numMembers, Movie movies[], char movieNames[][60], int numMovies,
    BookingInfo bookingHistories[], int& numBookings, char availableDates[][12], int numDates)
{
    MemberRecord temp; //設一暫存來存輸入進來的數
    int recordNumber = 0; //用來紀錄電子信箱及密碼是在memberDetails的哪一列陣列符合

    do //若輸入的email及password在memberDetails內沒有與之符合的字串，則代表輸入錯誤，故再輸入一次
    {
        do //若不輸入字元而直接按Enter，則重新輸入
        {
            cout << "Enter email address: ";
            cin.getline(temp.email, 40, '\n');
        } while (temp.email[0] == '\0');

        do //若不輸入字元而直接按Enter，則重新輸入
        {
            cout << "Enter password: ";
            cin.getline(temp.password, 24, '\n');
        } while (temp.password[0] == '\0');
        cout << endl;
    } while (illegal(temp.email, temp.password, memberDetails, numMembers, recordNumber) == false);

    //若以上輸入正確，則代表登入成功，進入以下迴圈
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
            accountInfor(memberDetails, numMembers, recordNumber); //印出個人資料並處理是否修改資料
            break;

        case 2:
            cout << endl;
            buyTickets(bookingHistories, numBookings, movies, movieNames, numMovies, availableDates, numDates, temp.email); //訂票系統
            break;

        case 3:
            cout << endl;
            displayBookingHistory(bookingHistories, numBookings, movies, movieNames, availableDates, temp.email); //印出從過去到現在的所有購票紀錄
            break;

        case 4:
            return; //登出
        }
    }
}

//(8)判斷輸入的電子信箱及密碼是否正確
bool illegal(char email[], char password[], MemberRecord memberDetails[], int numMembers, int& recordNumber)
{
    for (int k = 0; k < numMembers; k++)
    {
        //若在memberDetails裡某列陣列中的email及password皆與傳進來的字串符合
        if (strcmp(email, memberDetails[k].email) == 0 && strcmp(password, memberDetails[k].password) == 0)
        {
            recordNumber = k; //則紀錄該字串所在的陣列編號
            return true; //並且回傳true
        }
    }
    cout << "Sorry, unrecognized email or password." << endl << endl;
    return false; //否則回傳false
}

//(9)印出個人資料並處理是否修改資料
void accountInfor(MemberRecord memberDetails[], int numMembers, int recordNumber)
{
    //印出個人資料
    cout << "1. Name: " << memberDetails[recordNumber].name << endl;
    cout << "2. Email Address: " << memberDetails[recordNumber].email << endl;
    cout << "3. Phone Number: " << memberDetails[recordNumber].phone << endl;
    cout << "4. ID Number: " << memberDetails[recordNumber].IDNumber << endl;
    cout << "5. Password: " << memberDetails[recordNumber].password << endl;

    int choice;
    cout << endl << "Which one do you want to modify (0 – not modify)? ";
    while (true)
    {
        choice = inputAnInteger(0, 5);
        cout << endl;

        //修改個人資料
        switch (choice)
        {
        case 0:
            return;

        case 1:
            do //若不輸入字元而直接按Enter，則重新輸入
            {
                cout << "Enter correct data: ";
                cin.getline(memberDetails[recordNumber].name, 12, '\n');
            } while (memberDetails[recordNumber].name[0] == '\0');
            cout << endl << "Successful!" << endl << endl;
            return;

        case 2:
            do //若不輸入字元而直接按Enter，則重新輸入
            {
                cout << "Enter correct data: ";
                cin.getline(memberDetails[recordNumber].email, 40, '\n');
            } while (memberDetails[recordNumber].email[0] == '\0');
            cout << endl << "Successful!" << endl << endl;
            return;

        case 3:
            do //若不輸入字元而直接按Enter，則重新輸入
            {
                cout << "Enter correct data: ";
                cin.getline(memberDetails[recordNumber].phone, 12, '\n');
            } while (memberDetails[recordNumber].phone[0] == '\0');
            cout << endl << "Successful!" << endl << endl;
            return;

        case 4:
            do //若不輸入字元而直接按Enter，則重新輸入
            {
                cout << "Enter correct data: ";
                cin.getline(memberDetails[recordNumber].IDNumber, 12, '\n');
            } while (memberDetails[recordNumber].IDNumber[0] == '\0');
            cout << endl << "Successful!" << endl << endl;
            return;

        case 5:
            do //若不輸入字元而直接按Enter，則重新輸入
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

//(10)訂票系統
void buyTickets(BookingInfo bookingHistories[], int& numBookings, Movie movies[], char movieNames[][60],
    int numMovies, char availableDates[][12], int numDates, char email[])
{
    displaySessionTimes(movies, movieNames, numMovies, availableDates, numDates); //印出所有電影名稱、日期及時間

    int choice_movie; //選擇電影
    int choice_date; //選擇日期
    int choice_time; //選擇時間

    do //若選擇的電影代號不在範圍內，則重新輸入
    {
        cout << "Enter movie code (0 - 11): ";
    } while ((choice_movie = inputAnInteger(0, 11)) == -1);
    bookingHistories[numBookings].movieCode = choice_movie; //將所選的電影代號寫入訂票紀錄中
    cout << endl;

    do //若選擇的日期代號不在範圍內or所選的日期該電影未放映，則重新輸入
    {
        cout << "Enter date code (0 - 8): ";
    } while ((choice_date = inputAnInteger(0, 8)) == -1 || movies[choice_movie].dates[choice_date] == false);
    bookingHistories[numBookings].dateCode = choice_date; //將所選的日期代號寫入訂票紀錄中
    cout << endl;

    do //若選擇的時間代號不在範圍內or所選的時間該電影未放映，則重新輸入
    {
        cout << "Enter session time code (0 - 16): ";
    } while ((choice_time = inputAnInteger(0, 16)) == -1 || movies[choice_movie].sessionTimes[choice_time] == false);
    bookingHistories[numBookings].sessionTimeCode = choice_time; //將所選的時間代號寫入訂票紀錄中
    cout << endl;

    //印出所選的電影、日期和時間、並印出可選的4種票價
    cout << "Movie: " << movieNames[choice_movie] << endl;
    cout << "Date: " << availableDates[choice_date] << endl;
    cout << "Show Time: " << hours[choice_time] << endl;
    cout << "Price: Adult-" << movies[choice_movie].prices[0] << ", Concession-" << movies[choice_movie].prices[1]
        << ", Disability-" << movies[choice_movie].prices[2] << ", Elderly-" << movies[choice_movie].prices[3] << endl << endl;

    int total_movie_tickets = 0; //紀錄共買了幾張票
    do
    {
        for (int k = 0; k < 4; k++) //依序詢問該票種要買幾張
        {
            do //若所選擇的票數不在範圍內，則重新輸入
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
            total_movie_tickets += bookingHistories[numBookings].numTickets[k]; //紀錄當前共買了幾張票
        }
        cout << endl;
    } while (total_movie_tickets == 0); //若總共買了0張票，則重新輸入

    display(movies, bookingHistories[numBookings]); //印出該次購買的票種及價錢
    selectSeats(bookingHistories, numBookings, movies); //選擇座位

    for (int i = 0; i < strlen(email) + 1; i++) //將此次訂票的email帳號寫入購票紀錄中(strlen(email) + 1==字串長度+1個'\0')
    {
        bookingHistories[numBookings].email[i] = email[i];
    }
    numBookings++; //因增加了一筆訂票紀錄，故numBookings+1
}

//(11)選擇座位
void selectSeats(BookingInfo bookingHistories[], int numBookings, Movie movies[])
{
    int total_movie_tickets = 0; //代表共買了幾張票
    char row[8]{ '0','1','2','3','4','5','6','7' }; //直行
    char column[12]{ 'A','B','C' ,'D' ,'E' ,'F' ,'G' ,'H' ,'I' ,'J' ,'K' ,'L' }; //橫列

    for (int k = 0; k < 4; k++) //算出共買了幾張票
    {
        total_movie_tickets += bookingHistories[numBookings].numTickets[k];
    }

    cout << " ";
    for (int i = 0; i < 12; i++) //印出A~L排
    {
        cout << " " << column[i];
    }
    cout << endl;

    for (int r = 0; r < 8; r++)
    {
        cout << row[r]; //印出0~7排
        for (int c = 0; c < 12; c++) //印出座位表
        {
            //movies[電影代號].occupiedSeats[日期][時間][行][列]
            cout << " " << movies[bookingHistories[numBookings].movieCode].occupiedSeats
                [bookingHistories[numBookings].dateCode][bookingHistories[numBookings].sessionTimeCode][r][c];
        }
        cout << endl;
    }

    //選擇座位
    cout << endl << "Select " << total_movie_tickets << " seats (e.g. 0A):" << endl;
    for (int s = 0; s < total_movie_tickets; s++) //買幾張票就選幾個位置
    {
        cout << "? ";
        while (true)
        {
            cin.getline(bookingHistories[numBookings].seletedSeats[s], 4, '\n'); //輸入座號

            //若空字元前字串長度==2(座號必為1數字+1大寫英文字母)，且輸入的值在範圍內(英數不可顛倒)
            if (strlen(bookingHistories[numBookings].seletedSeats[s]) == 2
                && ('0' <= bookingHistories[numBookings].seletedSeats[s][0] && bookingHistories[numBookings].seletedSeats[s][0] <= '7'
                    && 'A' <= bookingHistories[numBookings].seletedSeats[s][1] && bookingHistories[numBookings].seletedSeats[s][1] <= 'L'))
            {
                //若選擇的座號還未被訂走
                if (movies[bookingHistories[numBookings].movieCode].occupiedSeats
                    [bookingHistories[numBookings].dateCode][bookingHistories[numBookings].sessionTimeCode]
                    [bookingHistories[numBookings].seletedSeats[s][0] - '0'][bookingHistories[numBookings].seletedSeats[s][1] - 'A'] == 0)
                {
                    //則將該座號的位置改為1(即此次訂位成功)
                    movies[bookingHistories[numBookings].movieCode].occupiedSeats
                        [bookingHistories[numBookings].dateCode][bookingHistories[numBookings].sessionTimeCode]
                        [bookingHistories[numBookings].seletedSeats[s][0] - '0'][bookingHistories[numBookings].seletedSeats[s][1] - 'A'] = 1;
                    break; //該次訂位成功後即跳出while迴圈
                }
                else
                {
                    cout << endl << "This seat has been occupied. Please select another seat." << endl << "? "; //否則會在while迴圈內再輸入一次直到輸入正確
                }
            }
            else
            {
                cout << endl << "Input Error! Please try again: " << endl << "? "; //否則會在while迴圈內再輸入一次直到輸入正確
            }
        }
    }
    cout << endl << "Successful!" << endl << endl;
}

//(12)印出所有電影名稱、日期及時間
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

//(13)印出購買的票種及價錢
void display(Movie movies[], BookingInfo bookingHistory)
{
    int total = 0; //代表訂票總金額
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
            cout << movies[bookingHistory.movieCode].prices[i] << "       "; //印出所選電影的票種單價
            cout << bookingHistory.numTickets[i] * movies[bookingHistory.movieCode].prices[i] << endl; //印出該票種小計
            total += bookingHistory.numTickets[i] * movies[bookingHistory.movieCode].prices[i]; //將該票種小計加入訂票總金額裡
        }
    }
    cout << endl << "Total Amount For Tickets: " << total << endl << endl; //印出總金額
}

//(14)印出該帳號(email)從過去到現在的所有購票紀錄
void displayBookingHistory(BookingInfo bookingHistories[], int numBookings, Movie movies[],
    char movieNames[][60], char availableDates[][12], char email[])
{
    int counter = 0; //計數器，計算該email帳號在過去有幾筆訂票紀錄

    for (int n = 0; n < numBookings; n++)
    {
        if (strcmp(bookingHistories[n].email, email) == 0) //若登入的email帳號符合該筆訂票紀錄中的email帳號
        {
            //則列出該筆訂票紀錄
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
            display(movies, bookingHistories[n]); //印出購買的票種及價錢
            cout << "----------------------------------------------" << endl << endl;
            counter++; //計數器+1
        }
    }

    if (counter == 0) //若計數器==0，則代表此email帳號沒有訂票紀錄
    {
        cout << "No bookings!" << endl << endl;
    }
}

//(15)加入新會員
void newMember(MemberRecord memberDetails[], int& numMembers)
{
    do //若不輸入字元而直接按Enter，則重新輸入
    {
        cout << "Enter your ID number: ";
        cin.getline(memberDetails[numMembers].IDNumber, 12, '\n');
    } while (memberDetails[numMembers].IDNumber[0] == '\0');

    if (existingID(memberDetails[numMembers].IDNumber, memberDetails, numMembers) == true) //若輸入的ID已經存在，則結束函式
    {
        cout << endl << "An account already exists with the ID number!" << endl;
        return;
    }

    do //若不輸入字元而直接按Enter，則重新輸入
    {
        cout << "Enter your name: ";
        cin.getline(memberDetails[numMembers].name, 12, '\n');
    } while (memberDetails[numMembers].name[0] == '\0');


    while (true) //若輸入的電子信箱已經存在，則再輸入一次直到該電子信箱沒被註冊過
    {
        do //若不輸入字元而直接按Enter，則重新輸入
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

    do //若不輸入字元而直接按Enter，則重新輸入
    {
        cout << "Enter a password: ";
        cin.getline(memberDetails[numMembers].password, 24, '\n');
    } while (memberDetails[numMembers].password[0] == '\0');

    do //若不輸入字元而直接按Enter，則重新輸入
    {
        cout << "Enter your phone number: ";
        cin.getline(memberDetails[numMembers].phone, 12, '\n');
    } while (memberDetails[numMembers].phone[0] == '\0');

    numMembers++; //因增加了一筆新會員資料，故numMembers+1
    cout << endl << "Successful!" << endl;
}

//(16)判別IDNumber是否存在
bool existingID(char newIDNumber[], MemberRecord memberDetails[], int& numMembers)
{
    for (int k = 0; k < numMembers; k++)
    {
        if (strcmp(memberDetails[k].IDNumber, newIDNumber) == 0) //若傳進來的新ID與memberDetails內newIDNumber部分的某筆字串相同
        {
            return true; //則代表該ID已存在，回傳true
        }
    }
    return false; //否則回傳false
}

//(17)判別Email是否存在
bool existingEmail(char newEmail[], MemberRecord memberDetails[], int& numMembers)
{
    for (int k = 0; k < numMembers; k++)
    {
        if (strcmp(memberDetails[k].email, newEmail) == 0) //若傳進來的新email與memberDetails內email部分的某筆字串相同
        {
            return true; //則代表該email已存在，回傳true
        }
    }
    return false; //否則回傳false
}

//(18)存取會員資料
void saveMemberInfo(MemberRecord memberDetails[], int numMembers)
{
    ofstream outFile("Member Info.dat", ios::binary); //寫檔

    for (int k = 0; k < numMembers; k++)
    {
        outFile.write(reinterpret_cast<const char*>(&memberDetails[k]), sizeof(memberDetails[k])); //轉換memberDetails的型態後存檔
    }

    outFile.close(); //寫檔關閉
}

//(19)存取電影相關資訊
void saveMovies(Movie movies[], int numMovies)
{
    ofstream outFile("Movies.dat", ios::binary); //寫檔

    for (int k = 0; k < numMovies; k++)
    {
        outFile.write(reinterpret_cast<const char*>(&movies[k]), sizeof(movies[k])); //轉換movies的型態後存檔
    }

    outFile.close(); //寫檔關閉
}

//(20)存取訂票歷史紀錄
void saveBookingHistories(BookingInfo bookingHistories[], int numBookings)
{
    ofstream outFile("Booking Histories.dat", ios::binary); //寫檔

    for (int k = 0; k < numBookings; k++)
    {
        outFile.write(reinterpret_cast<const char*>(&bookingHistories[k]), sizeof(bookingHistories[k])); //轉換bookingHistories的型態後存檔
    }
    outFile.close(); //寫檔關閉
}

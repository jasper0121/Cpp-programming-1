#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;

struct Movie
{
	int movieCode;
	char dates[12] = "";
	int numSessions;
	char sessionTimes[11][8] = { "" };
};

void loadMovieNames(char movieNames[][40], int& numMovies);
void loadMovies(Movie movies[], int& numRecords);
void buyTickets(char movieNames[][40], Movie movies[], int numMovies, int numRecords);
int inputAnInteger(int begin, int end);

int main()
{
	char movieNames[30][40];
	int numMovies = 0;
	loadMovieNames(movieNames, numMovies);

	Movie movies[110];
	int numRecords = 0;
	loadMovies(movies, numRecords);

	buyTickets(movieNames, movies, numMovies, numRecords);

	system("pause");
}

void loadMovieNames(char movieNames[][40], int& numMovies)
{
	ifstream inFile("Movie Names.txt"); //讀檔

	if (!inFile) //若沒讀到檔
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	while (inFile.getline(movieNames[numMovies], 40, '\n')) //將電影名稱一行一行地讀入movieNames
	{
		if (numMovies < 10)
		{
			cout << " " << numMovies << ". " << movieNames[numMovies] << endl;
		}
		else
		{
			cout << numMovies << ". " << movieNames[numMovies] << endl;
		}
		numMovies++;
	}

	inFile.close(); //讀檔關閉
}

void loadMovies(Movie movies[], int& numRecords)
{
	ifstream inFile("Session Times.dat", ios::binary); //讀檔

	if (!inFile) //若沒讀到檔
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	//從dat檔內讀取資料，轉換型態後存入movies
	while (inFile.read(reinterpret_cast<char*>(&movies[numRecords]), sizeof(movies[numRecords])))
	{
		numRecords++;
	}

	inFile.close(); //讀檔關閉
}

void buyTickets(char movieNames[][40], Movie movies[], int numMovies, int numRecords)
{
	int choice_movie; //選擇電影
	int choice_date; //選擇日期
	int choice_time; //選擇場次
	int date_movie_session = 0; //代表該電影有多少日期可選
	int movieRecords = 0; //紀錄所選電影的初始日期在陣列中的位置

	//選擇電影
	do
	{
		cout << endl << "Enter movie code (0 - 26): ";
	} while ((choice_movie = inputAnInteger(0, 26)) == -1); //若輸入的數不在範圍內，則重新輸入
	cout << endl;

	//印出該電影的所有上映日期
	for (int k = 0; movies[k].movieCode <= choice_movie; k++) //從0開始尋找選擇的電影編號
	{
		if (movies[k].movieCode == choice_movie) //若找到該電影編號
		{
			if (date_movie_session == 0) //若date_movie_session == 0則代表此列陣列是該電影編號的第一筆資料
			{
				movieRecords = k; //故將第一次找到的該陣列編號記錄起來
			}
			cout << " " << date_movie_session << ". " << movies[k].dates << endl;
			date_movie_session++; //記錄該電影可選的日期數
		}
	}

	//選擇日期
	do
	{
		cout << endl << "Enter date code (0 - " << date_movie_session - 1 << "): ";
	} while ((choice_date = inputAnInteger(0, date_movie_session - 1)) == -1); //若輸入的數不在範圍內，則重新輸入
	cout << endl;

	//印出該日期內的所有場次
	for (int number = 0; number < movies[movieRecords + choice_date].numSessions; number++)
	{
		//movieRecords代表此列陣列是該電影編號的第一筆資料，故此陣列的choice_date==0
		if (number < 10)
		{
			cout << " " << number << ". " << movies[movieRecords + choice_date].sessionTimes[number] << endl;
		}
		else
		{
			cout << number << ". " << movies[movieRecords + choice_date].sessionTimes[number] << endl;
		}
	}

	//選擇場次
	do
	{
		cout << endl << "Enter session time code (0 - " << movies[movieRecords + choice_date].numSessions - 1 << "): ";
	} while ((choice_time = inputAnInteger(0, movies[movieRecords + choice_date].numSessions - 1)) == -1); //若輸入的數不在範圍內，則重新輸入

	//購票結束，印出購票資訊(包括電影名稱、日期及場次)
	cout << endl << movieNames[choice_movie] << endl;
	cout << movies[movieRecords + choice_date].dates << " " << movies[movieRecords + choice_date].sessionTimes[choice_time] << endl << endl;
}

int inputAnInteger(int begin, int end)
{
	char choice[10]; //存輸入進來的資料
	int number = 0; //存choice裡的數字字元
	int size = 0; //代表在空字元前有幾格陣列存有資料
	cin.getline(choice, 10, '\n'); //使輸入的空格可以被存入字元陣列

	if (choice[0] == '\0') //若不輸入字元而直接按Enter
	{
		return -1; //則輸入必定錯誤，故回傳-1
	}

	for (int i = 0; choice[i] != '\0'; i++) //計算在空字元前有幾格陣列存有資料
	{
		size++;
	}

	for (int k = 0; choice[k] != '\0'; k++)
	{
		//若該格陣列內非數字字元或空字元前陣列格數大於2格(因以上須用到此函式所傳進來的end最多到十位數)
		if (!('0' <= choice[k] && choice[k] <= '9') || size > 2)
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
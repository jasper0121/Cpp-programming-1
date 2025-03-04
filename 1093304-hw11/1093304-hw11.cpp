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
	ifstream inFile("Movie Names.txt"); //Ū��

	if (!inFile) //�Y�SŪ����
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	while (inFile.getline(movieNames[numMovies], 40, '\n')) //�N�q�v�W�٤@��@��aŪ�JmovieNames
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

	inFile.close(); //Ū������
}

void loadMovies(Movie movies[], int& numRecords)
{
	ifstream inFile("Session Times.dat", ios::binary); //Ū��

	if (!inFile) //�Y�SŪ����
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	//�qdat�ɤ�Ū����ơA�ഫ���A��s�Jmovies
	while (inFile.read(reinterpret_cast<char*>(&movies[numRecords]), sizeof(movies[numRecords])))
	{
		numRecords++;
	}

	inFile.close(); //Ū������
}

void buyTickets(char movieNames[][40], Movie movies[], int numMovies, int numRecords)
{
	int choice_movie; //��ܹq�v
	int choice_date; //��ܤ��
	int choice_time; //��ܳ���
	int date_movie_session = 0; //�N��ӹq�v���h�֤���i��
	int movieRecords = 0; //�����ҿ�q�v����l����b�}�C������m

	//��ܹq�v
	do
	{
		cout << endl << "Enter movie code (0 - 26): ";
	} while ((choice_movie = inputAnInteger(0, 26)) == -1); //�Y��J���Ƥ��b�d�򤺡A�h���s��J
	cout << endl;

	//�L�X�ӹq�v���Ҧ��W�M���
	for (int k = 0; movies[k].movieCode <= choice_movie; k++) //�q0�}�l�M���ܪ��q�v�s��
	{
		if (movies[k].movieCode == choice_movie) //�Y���ӹq�v�s��
		{
			if (date_movie_session == 0) //�Ydate_movie_session == 0�h�N���C�}�C�O�ӹq�v�s�����Ĥ@�����
			{
				movieRecords = k; //�G�N�Ĥ@����쪺�Ӱ}�C�s���O���_��
			}
			cout << " " << date_movie_session << ". " << movies[k].dates << endl;
			date_movie_session++; //�O���ӹq�v�i�諸�����
		}
	}

	//��ܤ��
	do
	{
		cout << endl << "Enter date code (0 - " << date_movie_session - 1 << "): ";
	} while ((choice_date = inputAnInteger(0, date_movie_session - 1)) == -1); //�Y��J���Ƥ��b�d�򤺡A�h���s��J
	cout << endl;

	//�L�X�Ӥ�������Ҧ�����
	for (int number = 0; number < movies[movieRecords + choice_date].numSessions; number++)
	{
		//movieRecords�N���C�}�C�O�ӹq�v�s�����Ĥ@����ơA�G���}�C��choice_date==0
		if (number < 10)
		{
			cout << " " << number << ". " << movies[movieRecords + choice_date].sessionTimes[number] << endl;
		}
		else
		{
			cout << number << ". " << movies[movieRecords + choice_date].sessionTimes[number] << endl;
		}
	}

	//��ܳ���
	do
	{
		cout << endl << "Enter session time code (0 - " << movies[movieRecords + choice_date].numSessions - 1 << "): ";
	} while ((choice_time = inputAnInteger(0, movies[movieRecords + choice_date].numSessions - 1)) == -1); //�Y��J���Ƥ��b�d�򤺡A�h���s��J

	//�ʲ������A�L�X�ʲ���T(�]�A�q�v�W�١B����γ���)
	cout << endl << movieNames[choice_movie] << endl;
	cout << movies[movieRecords + choice_date].dates << " " << movies[movieRecords + choice_date].sessionTimes[choice_time] << endl << endl;
}

int inputAnInteger(int begin, int end)
{
	char choice[10]; //�s��J�i�Ӫ����
	int number = 0; //�schoice�̪��Ʀr�r��
	int size = 0; //�N��b�Ŧr���e���X��}�C�s�����
	cin.getline(choice, 10, '\n'); //�Ͽ�J���Ů�i�H�Q�s�J�r���}�C

	if (choice[0] == '\0') //�Y����J�r���Ӫ�����Enter
	{
		return -1; //�h��J���w���~�A�G�^��-1
	}

	for (int i = 0; choice[i] != '\0'; i++) //�p��b�Ŧr���e���X��}�C�s�����
	{
		size++;
	}

	for (int k = 0; choice[k] != '\0'; k++)
	{
		//�Y�Ӯ�}�C���D�Ʀr�r���ΪŦr���e�}�C��Ƥj��2��(�]�H�W���Ψ즹�禡�ҶǶi�Ӫ�end�̦h��Q���)
		if (!('0' <= choice[k] && choice[k] <= '9') || size > 2)
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
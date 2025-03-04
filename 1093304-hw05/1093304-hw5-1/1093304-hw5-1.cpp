#include <iostream>
using namespace std;

// returns the maximum element in the array relevance
int recursiveMax(int last);

// prints all the URLs of the web pages with the highest relevance
void recursiveOutput(int max, int first);
char webPages[10][101];
int relevance[10];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < 10; j++)
            cin >> webPages[j] >> relevance[j];

        int max = recursiveMax(9);

        cout << "Case #" << i << ":\n";
        recursiveOutput(max, 0);
    }

    system("pause");
}

int recursiveMax(int last)
{
    if (last == 0)
    {
        return relevance[0]; //回傳0號陣列的值給int max = recursiveMax(1-1)
    }
    int max = recursiveMax(last - 1); //若last!=0，則一直呼叫函式直到last==0
    if (max < relevance[last])
    {
        return relevance[last];
    }
    else
    {
        return max;
    }
}

void recursiveOutput(int max, int first)
{
    if (first == 10)
    {
        return;
    }
    else
    {
        if (relevance[first] == max)
        {
            cout << webPages[first] << endl;
        }
        recursiveOutput(max, first + 1);
    }
    return;
}
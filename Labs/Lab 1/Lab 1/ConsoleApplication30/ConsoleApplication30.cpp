#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    srand((int)time(0));

    const int n = 9;
    double a[n][n];
    int b[n][n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = rand() % 9 + 1;
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] > a[i][i]) b[i][j] = 1;
            else b[i][j] = 0;
            cout << b[i][j] << " ";
        }
        cout << endl;
    }
    system("pause");
    return 0;
}
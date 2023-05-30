#include <iostream>
using namespace std;

int main()
{
    double x, y, z, max, min, L;

    cout << "x="; cin >> x;
    cout << "y="; cin >> y;
    cout << "z="; cin >> z;

    max = x;
    if (z > max) max = z;

    min = x;
    if (y < min) min = y;
    if (z < min) min = z;

    L = 2. * max - 3. * min;

    cout << "L=" << L << "\n";

    system("pause");
    return 0;
}
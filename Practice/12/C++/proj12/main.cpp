#include <iostream>
#include <cmath>

using namespace std;

long double fact(int N)
{
    if (N < 0)
        return 0;
    if (N == 0)
        return 1;
    else
        return N * fact(N - 1);
}

int main()
{
    int N;
    cout << "введите число, факториал которого вы хотите получить" << endl;
    cin >> N;
    cout << "Факториал числа: " << N << "=" << fact(N) << endl;
}

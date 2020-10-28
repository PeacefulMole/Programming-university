#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double a;
    int b;
    cout << "введите число, которое вы хотите возвести в степень: ";
    cin >> a;
    cout << "введите степень: ";
    cin >> b;
    cout << "ответ=" << pow(a, b) << endl;
}

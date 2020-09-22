#include <iostream>
using namespace std;
int main()
{
    double x,t,v,g,L;
    g = 9.8;
    cout << "Введите начальное положение: ";
    cin >> x;
    cout << "Введите время движения: " ;
    cin >> t;
    cout << "Введите начальную скорость: ";
    cin >> v;
    L = x + v * t + g * t * t / 2;
    cout << "Расстояние = " << L <<endl;
}

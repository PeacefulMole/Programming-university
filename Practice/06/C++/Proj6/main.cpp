#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    double a,b,c,d,x,m;
    cout << "введите первое число" << endl;
    cin >> a;
    cout << "введите второе число" << endl;
    cin >> b;
    cout << "введите третье число" << endl;
    cin >> c;
    d = b*b-4*a*c; // вычисление дискриминанта
    if (d>0) {
    x = (-b+sqrt(d))/(2*a); // вычисление первого корня выражения
    m = (-b-sqrt(d))/(2*a); // вычисление второго корня выражения
    cout << "x1=" << x << endl << "x2=" << m << endl;
    }
    else {
        if (d<0) {
        cout << "корни уравнения отсутствуют" << endl;
        }
        else if (d==0) {
                cout << "x=" << (-b+0)/(2*a) << endl;
            }
    }
}

#include <iostream>
#include <math.h>

#define MSG() "Вы ввели некоректное число."
#define MSGer() "Такого варианта не существует."

using namespace std;

int main()
{
    int x;
    cout << "Выберите способ нахождения площади треугольника:" <<endl << "Через длину сторон треугольника - 1" << endl << "Через координаты вершин треугольника - 2" << endl << "Ваш выбор: ";
    cin >> x;
    if (x == 1){
        double a, b, c, p;
        cout << "Введите сторону a: ";
        cin >> a;
        if (a <= 0){
            cout << MSG() <<endl;
            return 0;
        }
        cout << "Введите сторону b: ";
        cin >> b;
        if (b <= 0){
            cout << MSG() << endl;
            return 0;
        }
        cout << "Введите сторону c: ";
        cin >> c;
        if (c <= 0){
            cout << MSG() << endl;
            return 0;
        }
        else {
            p = (a + b + c) / 2;
            cout << "S= " << sqrt(p * ((p - a) * (p - b) * (p - c))) << endl;
        }
    }
    else {
        if (x > 2)
            cout << MSGer() << endl;
        else {
            if (x < 1){
                cout << MSGer() << endl;
            }
        }
    }
    if (x == 2){
        double x1, y1, x2, y2, x3, y3;
        cout << "Введите координаты вершины а:" << endl;
        cin >> x1 >> y1;
        cout << "Введите координаты вершины b:" << endl;
        cin >> x2 >> y2;
        cout << "Введите координаты вершины c:" << endl;
        cin >> x3 >> y3;
        int l = 0.5 * (x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3);
        if (l < 0){
            cout << "S= " << l * (-1) << endl;
        }
        else
            cout << "S= " << l << endl;
     }
}

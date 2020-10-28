#include <iostream>
#include <math.h>

using namespace std;

int main () {
    setlocale (LC_ALL, "Russian");
    int h1,m1,h2,m2,h3,m3,l;
    char c;
    cout << "вы пришли в:" << endl;
    cin >>h1>>c>>m1;
    if (c!=':') {
        cout << "An error has occured" << endl;
    }
        if (h1>23) {
            cout << "выберите корректное число часов" << endl;
    }
    else if (m1>59) {
        cout << "введите корректное число минут" << endl;
    }
    else {
    cout << "вы здесь находитесь в:" << endl;
    cin>>h2>>c>>m2;
    if (h2>23) {
        cout << "введите корректное число часов" << endl;
    }
    else if (m2>59) {
        cout << "введите правильное число минут" << endl;
    }
    else {
        h3 = h2-h1;
        m3 = m2-m1;
        if (m3<0) {
            m3=-(m3);
        }
        if (h3>0) {
            cout << "встреча не состоится" << endl;
        }
            else if (m3>15) {
                cout << "встреча не состоится" << endl;
            }
            if (h3==0) {
               cout << "встреча состоится" << endl;
            }
            else if (m3<=15) {
                cout << "встреча состоится" << endl;
            }
    }
    }
}

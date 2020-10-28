#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    char c;
    double a,b;
    cout << "осуществите ввод" << endl;
    cin >>a>>c>>b;
    if (c == '+') {
        cout << "ответ=" << a+b << endl;
    }
    if (c=='-') {
        cout << "ответ=" << a-b << endl;
    }
    if (c=='*') {
    cout << "ответ=" << a*b << endl;
    }
    if (c=='/') {
        cout << "ответ=" << a/b << endl;
    }
}

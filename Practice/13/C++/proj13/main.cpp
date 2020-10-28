#include <iostream>

using namespace std;

int main()
{
    int a;
    cout << "введите число" << endl;
    cin >> a;
    if (a <= 1) {
        cout << "невозможно ввести число меньше чем 2" << endl;
    }
    else if ((a % 2 == 0) || (a % 3 == 0) || (a % 5 == 0)) {
        cout << "составное" << endl;
    }
    else {
        cout << "простое" << endl;
    }
}

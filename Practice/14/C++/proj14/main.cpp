#include <iostream>

using namespace std;

int main() {
    cout << "Введите число\n";

    long long n;
    cin >> n;

    int x = 0;
    if (n >= 1) {
        x++;
    }

    while (n > 1) {
        n /= 2;
        x++;
    }

    cout << x << endl;
}

#include <iostream>
#include <ctime>

using namespace std;

int n, d, v, i;
int main() {
    while (d != 2) {
       srand(time(0));
        n = 1 + rand() % 100;
        cout << "хотите сыграть?\n1 - играть\n2 - закрыть приложение\n";
        cin >> d;
        switch (d) {
        case 1:
        {
            cin >> v;
            if (v != n) {
                for (i = 1; i < 5; i++) {
                    if (v < n) {
                        cout << "загаданное число больше\n";
                    }
                    if (v > n) {
                        cout << "загаданное число меньше\n";
                    }
                    cin >> v;
                }
            }
            if (v != n) {
                cout << "Вы проиграли! Было загадано число:" << n << endl;
                cout << "начать сначала? (1 - да, 2 - нет)\n";
                cin >> d;
            }
            if (v == n) {
                cout << "Поздравляю! Вы угадали!\n";
                cout << "начать сначала? (1 - да, 2 - нет)\n";
                cin >> d;
            }
        }
        case 2:
        {
            break;
        }
        }
    }
}

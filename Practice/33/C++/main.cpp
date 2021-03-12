#include <iostream>

using namespace std;
int *create(const int num, const int start, const int step) {
    int* dynam = new int[num];
    dynam[0] = start;
    for (int i = 1; i < num; i++) {

        *(dynam + i) = *(dynam + i - 1) + step;

    }
    return dynam;
}
void sort(int* dynam,  int num) {
    int temp = 0;
    for (int i = 0; i < num - 1; ++i)
    {
        for (int i2 = 0; i2 < num - 1; ++i2)
        {
            if (dynam[i2 + 1] < dynam[i2])
            {
                temp = dynam[i2 + 1];
                dynam[i2 + 1] = dynam[i2];
                dynam[i2] = temp;
            }
        }
    }
}
void print(int* dynam, int num) {
    cout << "[";
    for (int i = 0; i < num; i++) { cout << dynam[i]; if (i != num - 1) { cout << ", "; } }
    cout << "]";
}
int main()
{
    setlocale(LC_CTYPE, "rus");
    int num, step = 0, start = 0;
    cout << "Введите размер массива\n";
    cin >> num;
    cout << "Введите начальный член\n";
    cin >> start;
    cout << "Введите шаг арифм прогрессии\n";
    cin >> step;
    int* dynamic = create(num, start, step);
    create(num, start, step);
    sort(dynamic, num);
    print(dynamic, num);

    delete[] dynamic;
    return 0;
}

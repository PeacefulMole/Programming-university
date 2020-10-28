#include <iostream>

using namespace std;

int main()
{
    int s, l1, r1, l2, r2,m,n;
    int x1 = l1;
    int x2;
    bool succ = true;
    cout << "введите числа s,l1,r1,l2,r2 (по порядку, через пробел)" << endl;
    cin >> s >> l1 >> r1 >> l2 >> r2;
    if (x1 + r2 < s) {
        x2=r2;
    }
    if (r1 + x2 < s) {
        cout << "-1" << endl;
        succ = false;
    }
    else {
        x1 = s - r2;
    }
    if (s < l1 + l2) {
        cout << "-1" << endl;
        succ = false;
    }
    else {
        x2 = s - x1;
    }
    if (succ) {
        cout << x1 << " " << x2 << endl;
    }
}

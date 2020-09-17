#include <iostream>

using namespace std;

int main()
{
    int vav, lol;
    //int three;
    cin >> vav >> lol;
    //vav = three
    //vav = lol
    //lol = three
    vav = lol - vav;
    lol = lol - vav;
    vav = lol + vav;
    cout << "Первая = " <<vav <<endl << "Вторая = " <<lol <<endl;
    return 0;
}

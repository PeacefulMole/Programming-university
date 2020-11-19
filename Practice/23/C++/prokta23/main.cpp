#include <iostream>
#include <iomanip>
#include "retfrack.h"
#include "teilor.h"
#include "fufe.h"

int main()
{
    int F = 10;
    std::cout << "n" << "\t" << "n!" << std::endl;
    for ( int i = 1; i <= F; i++ ){
        std::cout << i << "\t" << fact(i) << std::endl;
    }
    std::cout << std::endl;
    double x = 0;
    int k = 5;
    std::cout << "x" << "\t" << "sin(x)" << std::endl;
    for ( ;x <= M_PI/4 + M_PI/180; ){
        std::cout << std::setprecision(4) << x << "\t" << std::setprecision(4) << sinx(x, k) << std::endl;
        x += M_PI/180;
    }
    std::cout << "\n";
    int n = 10;
    std::cout << "k" << "\t" << "C(k, 10)" << std::endl;
    for ( int k = 1; k <= 10; k++){
        std::cout << k << "\t" << combi(n, k) << std::endl;
    }
}

#ifndef TEILOR_H
#define TEILOR_H

#include <cmath>
#include "retfrack.h"

double sinx(double x, int k){
    double sum = x;
    for(int i = 1; i <= k; i++){
        sum += pow(-1, i)*((pow(x, 2 * i + 1))/fact(2 * i + 1));
    }
    return sum;
}

#endif // TEILOR_H

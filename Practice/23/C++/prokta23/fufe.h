#ifndef FUFE_H
#define FUFE_H

#include "retfrack.h"

int combi(int n, int k){
    return (fact(n) / (fact(k)*fact(n - k)));
}

#endif // FUFE_H

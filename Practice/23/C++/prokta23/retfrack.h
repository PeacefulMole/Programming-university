#pragma once

int fact(int F)
{
    if (F < 0)
        return 0;
    if (F == 0)
        return 1;
    else return F * fact( F - 1 );
}

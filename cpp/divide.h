#ifndef DIVIDE_H
#define DIVIDE_H

// doing the division but checking for zero
inline double divide(double a, double b, bool &ok) {
    // math breaks if we divide by 0 so check that first
    if (b == 0) {
        ok = false;
        return 0;
    }
    
    // all good to go
    ok = true;
    return a / b;
}

#endif
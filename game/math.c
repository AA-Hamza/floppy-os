#include "math.h"
#define PI 3.1415926535897932384650288
#define TERMS 3     // No difference if you choose a higher value

double absd(double a) {
    if (a < 0)
        return -a;
    return a;
}

double power(float base, s32int exp) 
{
    if(exp < 0) {
        if(base == 0)
            return -0; // Error!!
        return 1 / (base * power(base, (-exp) - 1));
    }
    if(exp == 0)
        return 1;
    if(exp == 1)
        return base;
    return base * power(base, exp - 1);
}

static s32int fact(s32int n) 
{
    return n <= 0 ? 1 : n * fact(n-1);
}

double sine(double rad) {
    double sin = 0;

    s32int i;
    for(i = 0; i < TERMS; i++) { // That's Taylor series!!
        sin += power(-1, i) * power(rad, 2 * i + 1) / fact(2 * i + 1);
    }
    return sin;
}

double cosine(double rad) {
    double cos = 0;

    s32int i;
    for(i = 0; i < TERMS; i++) { // That's also Taylor series!!
        cos += power(-1, i) * power(rad, 2 * i) / fact(2 * i);
    }
    return cos;
}

// Psuedo-Random function to generate the heights of the tunnels
u32int rand()
{
    static u32int next = 42;
    next = next * 1103515243 + 12345;
    return (u32int)(next / 65536) % 32768;
}

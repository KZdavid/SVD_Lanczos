#include <math.h>
#include <iostream>
#include "ShowBinary.h"
using namespace std;
void cutoff(float *f, const uint32_t n) {
    uint32_t *     p   = (uint32_t *) f;
    const uint32_t cut = (0xffffffff) << (32 - n);
    *p                 = (*p) & cut;
    f                  = (float *) p;
}

int main(int argc, char const *argv[]) {
    float a = 2.2;
    showfloatbinary(a);
    cout << endl;
    cutoff(&a, 24);
    showfloatbinary(a);
    cout << endl;
    cout << a << endl;
    return 0;
}
#include <math.h>
#include <iostream>
#include "ShowBinary.h"
int main() {
    float c = (1 + pow(2, -22)) * pow(2, 0);
    // unsigned int *p = (unsigned int *) &c;
    // ShowBinary(&p)
    showfloatbinary(c);
    cout << endl;
    // float              a, b, c;
    // a               = 1 + pow(2, -22);
    // b               = pow(2, -150);
    // c               = a * b;
    // cout << "sign=\t\t" << bitset<sizeof(float) * 8>(sign) << endl;
    // cout << "expoment=\t" << bitset<sizeof(float) * 8>(expoment) << endl;
    // cout << "mantissa=\t" << bitset<sizeof(float) * 8>(mantissa) << endl;
    // cout << "value=\t\t" << bitset<32>(*p) << endl;
    // cout << "sign=\t\t" << bitset<1>((sign & *p) >> 31) << endl;
    // cout << "expoment=\t " << bitset<8>((expoment & *p) >> 23) << endl;
    // cout << "mantissa=\t         " << bitset<23>((mantissa & *p)) << endl;
    return 0;
}

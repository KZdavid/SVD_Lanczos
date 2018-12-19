#include <math.h>
#include <iostream>
#include "ShowBinary.h"
#include "datatype.h"
using namespace std;
int main(int argc, char const *argv[]) {
    limitedfloat f1, f2 = 2.1;
    f1 = f2;
    limitedcomplex z(f1, f2);
    cout << z << endl;
    z = -f1;
    cout << z << endl;
    return 0;
}
#ifndef SHOWBINARY_H
#define SHOWBINARY_H
#include <bitset>
#include <string>
using namespace std;
void showbinary(uint32_t &p) {
    string output = bitset<32>(p).to_string();
    cout << output[0] << " ";
    for (int i = 1; i < 9; ++i) cout << output[i];
    cout << " ";
    for (int i = 9; i < 32; ++i) cout << output[i];
}
void showfloatbinary(float &f) {
    unsigned int *p = (unsigned int *) &f;
    showbinary(*p);
}
#endif
#ifndef LIMITEDFLOAT_H
#define LIMITEDFLOAT_H
#include <math.h>
using namespace std;

const uint8_t bitwidth = 32;

class limitedfloat {
   public:
    float   value;
    uint8_t length;

    //
    limitedfloat() : value(0), length(bitwidth){};
    limitedfloat(float v) : value(v), length(bitwidth) { this->cutoff(); };
    limitedfloat(float v, uint8_t l) : value(v), length(l) { this->cutoff(); };

    limitedfloat operator+(const limitedfloat &b) {
        return limitedfloat(this->value + b.value, minlength(*this, b));
    }
    limitedfloat operator-(const limitedfloat &b) {
        return limitedfloat(this->value - b.value, minlength(*this, b));
    }
    limitedfloat operator*(const limitedfloat &b) {
        return limitedfloat(this->value * b.value, minlength(*this, b));
    }
    limitedfloat operator/(const limitedfloat &b) {
        return limitedfloat(this->value / b.value, minlength(*this, b));
    }
    operator float() const { return this->value; }
    operator float &() { return this->value; }

    uint8_t minlength(const limitedfloat &a, const limitedfloat &b) {
        if (this->length > b.length)
            return b.length;
        else
            return this->length;
    }
    limitedfloat pow(const limitedfloat &a, const limitedfloat &b) {
        return limitedfloat(pow(a, b), minlength(a, b));
    }

   private:
    void cutoff(void) {
        if (this->length ~ = 32) {
            uint32_t *     p   = (uint32_t *) &(this->value);
            const uint32_t cut = (0xffffffff) << (32 - this->length);
            *p                 = (*p) & cut;
        }
    }
};
#endif
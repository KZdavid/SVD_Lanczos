#ifndef DATATYPE_H
#define DATATYPE_H
#include <math.h>
#include <cassert>
#include <iostream>
using namespace std;
//固定位宽的浮点型的位宽
const uint8_t  bitwidth     = 24;
const uint32_t cut          = (0xffffffff) << (32 - bitwidth);
const float    RELATIVE_TOL = pow(2, -10);

class limitedfloat {
   public:
    float value;
    //构造函数
    limitedfloat(){};
    limitedfloat(const limitedfloat &v) : value(v.value){};
    limitedfloat(float v) : value(v) { cutoff(); };
    //重载一元运算符
    limitedfloat operator-() const {
        limitedfloat f(-value);
        return f;
    };
    //转换为float型
    operator float() const { return value; }
    operator float &() { return value; }
    //截断函数
    void cutoff(void) {
        uint32_t *p = (uint32_t *) &(value);
        *p          = (*p) & cut;
    }
};

class limitedcomplex {
   public:
    limitedfloat real, image;
    limitedcomplex(){};

    limitedcomplex(limitedfloat re) : real(re){};  //实数可以转为复数
    limitedcomplex(limitedfloat re, limitedfloat im) : real(re), image(im){};
    limitedcomplex(const limitedcomplex &r) : real(r.real), image(r.image){};
    limitedcomplex(float re) : real(re){};
    limitedcomplex(float re, float im) : real(re), image(im){};
    //虚部比较小的时候可隐式转为实数
    operator limitedfloat() const {
        assert(image / real < RELATIVE_TOL);
        return real;
    }
    operator limitedfloat &() {
        assert(image / real < RELATIVE_TOL);
        return real;
    }
    //重载复数加减乘除,复数作分母实数作分子时需要先把实数转为复数
    limitedcomplex operator+(const limitedcomplex &b) const {
        limitedcomplex r(*this);
        r.real += b.real;
        r.image += b.image;
        return r;
    };
    limitedcomplex operator-(const limitedcomplex &b) const {
        limitedcomplex r(*this);
        r.real -= b.real;
        r.image -= b.image;
        return r;
    };
    limitedcomplex operator*(const limitedcomplex &b) const {
        limitedcomplex r(*this);
        r.real  = r.real * b.real + r.image + b.image;
        r.image = r.real * b.image + r.image * b.real;
        return r;
    };
    limitedcomplex operator/(const limitedcomplex &b) const {
        limitedcomplex r(*this);
        limitedfloat   den = b.moudle();
        r.real             = (r.real * b.real + r.image * b.image) / den;
        r.image            = (r.image * b.real - r.real * b.image) / den;
        return r;
    };
    //重载一元运算符
    limitedcomplex operator-() const {
        limitedcomplex r(-real, -image);
        return r;
    };
    //重载相等
    bool operator==(const limitedcomplex &b) const {
        return (real == b.real) && (image == b.image);
    };
    bool operator!=(const limitedcomplex &b) const { return !(*this == b); };
    //复数的模
    limitedfloat moudle() const { return real * real + image * image; };
    //复数比较模长
    bool operator<(const limitedcomplex &b) const {
        return moudle() < b.moudle();
    };
    bool operator>(const limitedcomplex &b) const {
        return moudle() > b.moudle();
    };
    bool operator<=(const limitedcomplex &b) const {
        return moudle() <= b.moudle();
    };
    bool operator>=(const limitedcomplex &b) const {
        return moudle() >= b.moudle();
    };
    /*输入输出运算符重载的声明*/
    friend istream &operator>>(istream &in, limitedcomplex &b);
    friend ostream &operator<<(ostream &out, limitedcomplex &b);
    // friend limitedcomplex operator+(const limitedfloat &  a,
    //                                 const limitedcomplex &b);
    // friend limitedcomplex operator-(const limitedfloat &  a,
    //                                 const limitedcomplex &b);
    // friend limitedcomplex operator*(const limitedfloat &  a,
    //                                 const limitedcomplex &b);
    // friend limitedcomplex operator/(const limitedfloat &  a,
    //                                 const limitedcomplex &b);
};
//应对实数在运算符前面的情况
// limitedcomplex operator+(const limitedfloat &a, const limitedcomplex &b) {
//     limitedcomplex r(b);
//     r.real += a;
//     return r;
// };
// limitedcomplex operator-(const limitedfloat &a, const limitedcomplex &b) {
//     limitedcomplex r(b);
//     r.real -= a;
//     return r;
// };
// limitedcomplex operator*(const limitedfloat &a, const limitedcomplex &b) {
//     limitedcomplex r(b);
//     r.real  = r.real * a;
//     r.image = r.image * a;
//     return r;
// };
// limitedcomplex operator/(const limitedfloat &a, const limitedcomplex &b) {
//     limitedcomplex r(b);
//     limitedfloat   den = b.moudle();
//     r.real             = r.real / den;
//     r.image            = -a * r.image / den;
//     return r;
// };

istream &operator>>(istream &in, limitedcomplex &b) {
    in >> b.real >> b.image;
    return in;
};

ostream &operator<<(ostream &out, limitedcomplex &b) {
    if (b.image < 0)
        out << b.real << "-" << -b.image << "i";
    else
        out << b.real << "+" << b.image << "i";
    return out;
};

template <class T>
class XMatrix {
   public:
    //
    XMatrix() : m_Col(0), m_Row(0), m_Data(0) {}

    XMatrix(int parmaRow, int paramCol) : m_Col(0), m_Row(0), m_Data(0) {
        assert(paramCol > 0 && parmaRow > 0);
        InitMatrix(parmaRow, paramCol);
    }

    XMatrix(const XMatrix<T> &paramMatrix) : m_Col(0), m_Row(0), m_Data(0) {
        InitMatrix(paramMatrix.m_Row, paramMatrix.m_Col);
        SetValue(paramMatrix.m_Data);
    }
    //
    ~XMatrix() { FreeMatrix(); }
    //重载=
    XMatrix &operator=(const XMatrix<T> &paramMatrix) {
        if (this != &paramMatrix) {
            InitMatrix(paramMatrix.m_Row, paramMatrix.m_Col);
            SetValue(paramMatrix.m_Data);
        }
        return *this;
    }
    //重载(),用于取矩阵的元素
    T &operator()(int paramRow, int paramCol) {
        return GetValue(paramRow, paramCol);
    }

    const T &operator()(int paramRow, int paramCol) const {
        return GetValue(paramRow, paramCol);
    }
    //
    void SetValue(const T *paramValueList) {
        assert(paramValueList != NULL);
        for (int i = 1; i <= m_Row; i++) {
            for (int j = 1; j <= m_Col; j++) {
                SetValue(i, j, *paramValueList);
                paramValueList++;
            }
        }
    }
    void SetValue(int paramRow, int paramCol, const T &paramValue) {
        GetValue(paramRow, paramCol) = paramValue;
    }
    //
    int GetRow() const { return m_Row; }

    int GetCol() const { return m_Col; }
    //
    XMatrix<T> operator*(const T &paramValue) const {
        XMatrix<T> r(*this);
        for (int i = 1; i <= r.GetRow(); i++) {
            for (int j = 1; j <= r.GetCol(); j++) {
                r(i, j) = r(i, j) * paramValue;
            }
        }
        return r;
    }

    XMatrix<T> operator+(const XMatrix<T> &paramMatrix) const {
        assert(m_Col == paramMatrix.m_Col && m_Row == paramMatrix.m_Row);
        XMatrix<T> r(*this);
        for (int i = 1; i <= r.GetRow(); i++) {
            for (int j = 1; j <= r.GetCol(); j++) {
                r(i, j) = r(i, j) + paramMatrix(i, j);
            }
        }
        return r;
    }
    XMatrix<T> operator-(const XMatrix<T> &paramMatrix) const {
        assert(m_Col == paramMatrix.m_Col && m_Row == paramMatrix.m_Row);
        XMatrix<T> r(*this);
        for (int i = 1; i <= r.GetRow(); i++) {
            for (int j = 1; j <= r.GetCol(); j++) {
                r(i, j) = r(i, j) - paramMatrix(i, j);
            }
        }
        return r;
    }
    XMatrix<T> operator*(const XMatrix<T> &paramMatrix) const {
        assert(m_Col == paramMatrix.m_Row);
        XMatrix<T> r(m_Row, paramMatrix.m_Col);
        r.Clear(0);
        int n = paramMatrix.m_Row;
        for (int i = 1; i <= r.GetRow(); i++) {
            for (int j = 1; j <= r.GetCol(); j++) {
                for (int k = 1; k <= n; k++) {
                    r(i, j) = r(i, j) + GetValue(i, k) * paramMatrix(k, j);
                }
            }
        }
        return r;
    }
    void Clear(const T &paramValue) {
        for (int i = 1; i <= GetRow(); i++) {
            for (int j = 1; j <= GetCol(); j++) { SetValue(i, j, paramValue); }
        }
    }


    const T &GetValue(int paramRow, int paramCol) const {
        assert(paramCol > 0 && paramRow > 0);
        assert(paramRow <= GetRow() && paramCol <= GetCol());
        return m_Data[(paramRow - 1) * m_Col + (paramCol - 1)];
    }

    T &GetValue(int paramRow, int paramCol) {
        assert(paramCol > 0 && paramRow > 0);
        assert(paramRow <= GetRow() && paramCol <= GetCol());
        return m_Data[(paramRow - 1) * m_Col + (paramCol - 1)];
    }

    bool operator==(const XMatrix<T> &paramMatrix) const {
        assert(m_Col == paramMatrix.m_Col && m_Row == paramMatrix.m_Row);
        for (int i = 1; i <= GetRow(); i++) {
            for (int j = 1; j <= GetCol(); j++) {
                if (GetValue(i, j) != paramMatrix(i, j)) { return false; }
            }
        }
        return true;
    }

    bool operator!=(const XMatrix<T> &paramMatrix) const {
        return !(*this == paramMatrix);
    }

    XMatrix<T> Transpose() const  //矩阵转置
    {
        XMatrix<T> r(GetCol(), GetRow());
        for (int i = 1; i <= GetRow(); i++) {
            for (int j = 1; j <= GetCol(); j++) { r(j, i) = GetValue(i, j); }
        }
        return r;
    }
    //
    void Reset(int parmaRow, int paramCol) {
        assert(paramCol > 0 && parmaRow > 0);
        InitMatrix(parmaRow, paramCol);
    }

   private:
    void InitMatrix(int parmaRow, int paramCol) {
        FreeMatrix();
        m_Col  = paramCol;
        m_Row  = parmaRow;
        m_Data = new T[parmaRow * paramCol];
        Zero();
    }

    void FreeMatrix() {
        if (m_Data != NULL) {
            delete[] m_Data;
            m_Data = NULL;
        }
        m_Col = 0;
        m_Row = 0;
    }

    void Zero() {
        unsigned char *pC     = (unsigned char *) m_Data;
        int            iBytes = GetRow() * GetCol() * sizeof(T);
        for (int i = 0; i < iBytes; i++, pC++) { *pC = 0; }
    }

   private:
    T * m_Data;
    int m_Col;
    int m_Row;
};


template <class T>
XMatrix<T> operator*(const T &paramValue, const XMatrix<T> &paramMatrix) {
    return paramMatrix * paramValue;
}

template <class T>
ostream &operator<<(ostream &o, const XMatrix<T> &paramMatrix) {
    for (int i = 1; i <= paramMatrix.GetRow(); i++) {
        for (int j = 1; j <= paramMatrix.GetCol(); j++) {
            o << paramMatrix(i, j);
            if (j < paramMatrix.GetCol()) cout << ",";
        }
        cout << endl;
    }
    return o;
}

typedef XMatrix<float>        FloatMatrix;
typedef XMatrix<limitedfloat> LFloatMatrix;

#endif
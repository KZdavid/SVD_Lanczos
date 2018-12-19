#include <math.h>
#include <iostream>
#include "ShowBinary.h"
#include "datatype.h"
using namespace std;

FloatMatrix *XMatrixIndentity(FloatMatrix *paramMatrixOut);
FloatMatrix *XMatrixScaling(FloatMatrix *paramMatrixOut, float paramX,
                            float paramY, float paramZ);
FloatMatrix *XMatrixTranslation(FloatMatrix *paramMatrixOut, float paramX,
                                float paramY, float paramZ);
FloatMatrix *XMatrixMultiply(FloatMatrix *paramMatrixOut, FloatMatrix *paramM1,
                             FloatMatrix *paramM2);
FloatMatrix *XMatrixRotationX(FloatMatrix *paramMatrixOut, float paramAngle);
FloatMatrix *XMatrixRotationY(FloatMatrix *paramMatrixOut, float paramAngle);
FloatMatrix *XMatrixRotationZ(FloatMatrix *paramMatrixOut, float paramAngle);
FloatMatrix *XMatrixOrthoOffCenterLH(FloatMatrix *paramMatrixOut,
                                     float paramLeft, float paramRight,
                                     float paramBottom, float paramTop,
                                     float paramZ_Near, float paramZ_Far);

FloatMatrix *XMatrixScaling(FloatMatrix *paramMatrixOut, float paramX,
                            float paramY, float paramZ) {
    assert(paramMatrixOut != NULL && paramMatrixOut->GetCol() == 4 &&
           paramMatrixOut->GetRow() == 4);
    XMatrixIndentity(paramMatrixOut);
    paramMatrixOut->SetValue(1, 1, paramX);
    paramMatrixOut->SetValue(2, 2, paramY);
    paramMatrixOut->SetValue(3, 3, paramZ);
    paramMatrixOut->SetValue(4, 4, 1);
    return paramMatrixOut;
}

FloatMatrix *XMatrixIndentity(FloatMatrix *paramMatrixOut) {
    assert(paramMatrixOut != NULL && paramMatrixOut->GetCol() == 4 &&
           paramMatrixOut->GetRow() == 4);
    paramMatrixOut->Clear(0.0f);
    paramMatrixOut->SetValue(1, 1, 1.0f);
    paramMatrixOut->SetValue(2, 2, 1.0f);
    paramMatrixOut->SetValue(3, 3, 1.0f);
    paramMatrixOut->SetValue(4, 4, 1.0f);
    return paramMatrixOut;
}

FloatMatrix *XMatrixTranslation(FloatMatrix *paramMatrixOut, float paramX,
                                float paramY, float paramZ) {
    assert(paramMatrixOut != NULL && paramMatrixOut->GetCol() == 4 &&
           paramMatrixOut->GetRow() == 4);
    XMatrixIndentity(paramMatrixOut);
    paramMatrixOut->SetValue(4, 1, paramX);
    paramMatrixOut->SetValue(4, 2, paramY);
    paramMatrixOut->SetValue(4, 3, paramZ);
    return paramMatrixOut;
}

FloatMatrix *XMatrixMultiply(FloatMatrix *paramMatrixOut, FloatMatrix *paramM1,
                             FloatMatrix *paramM2) {
    assert(paramMatrixOut != NULL && paramMatrixOut->GetCol() == 4 &&
           paramMatrixOut->GetRow() == 4);
    assert(paramM1 != NULL && paramM1->GetCol() == 4 && paramM1->GetRow() == 4);
    assert(paramM2 != NULL && paramM2->GetCol() == 4 && paramM2->GetRow() == 4);
    *paramMatrixOut = (*paramM1) * (*paramM2);
    return paramMatrixOut;
}

FloatMatrix *XMatrixRotationX(FloatMatrix *paramMatrixOut, float paramAngle) {
    assert(paramMatrixOut != NULL && paramMatrixOut->GetCol() == 4 &&
           paramMatrixOut->GetRow() == 4);
    XMatrixIndentity(paramMatrixOut);
    paramMatrixOut->GetValue(2, 2) = cosf(paramAngle);
    paramMatrixOut->GetValue(2, 3) = sinf(paramAngle);
    paramMatrixOut->GetValue(3, 2) = -sinf(paramAngle);
    paramMatrixOut->GetValue(3, 3) = cosf(paramAngle);
    return paramMatrixOut;
}

FloatMatrix *XMatrixRotationY(FloatMatrix *paramMatrixOut, float paramAngle) {
    assert(paramMatrixOut != NULL && paramMatrixOut->GetCol() == 4 &&
           paramMatrixOut->GetRow() == 4);
    XMatrixIndentity(paramMatrixOut);
    paramMatrixOut->GetValue(1, 1) = cosf(paramAngle);
    paramMatrixOut->GetValue(1, 3) = -sinf(paramAngle);
    paramMatrixOut->GetValue(3, 1) = sinf(paramAngle);
    paramMatrixOut->GetValue(3, 3) = cosf(paramAngle);
    return paramMatrixOut;
}


FloatMatrix *XMatrixRotationZ(FloatMatrix *paramMatrixOut, float paramAngle) {
    assert(paramMatrixOut != NULL && paramMatrixOut->GetCol() == 4 &&
           paramMatrixOut->GetRow() == 4);
    XMatrixIndentity(paramMatrixOut);
    paramMatrixOut->GetValue(1, 1) = cosf(paramAngle);
    paramMatrixOut->GetValue(1, 2) = sinf(paramAngle);
    paramMatrixOut->GetValue(2, 1) = -sinf(paramAngle);
    paramMatrixOut->GetValue(2, 2) = cosf(paramAngle);
    return paramMatrixOut;
}
// 2/(r-l)      0            0           0
// 0            2/(t-b)      0           0
// 0            0            1/(zf-zn)   0
// (l+r)/(l-r)  (t+b)/(b-t)  zn/(zn-zf)  1
FloatMatrix *XMatrixOrthoOffCenterLH(FloatMatrix *paramMatrixOut,
                                     float paramLeft, float paramRight,
                                     float paramBottom, float paramTop,
                                     float paramZ_Near, float paramZ_Far) {
    assert(paramMatrixOut != NULL && paramMatrixOut->GetCol() == 4 &&
           paramMatrixOut->GetRow() == 4);
    XMatrixIndentity(paramMatrixOut);
    paramMatrixOut->GetValue(1, 1) = 2.0f / (paramRight - paramLeft);
    paramMatrixOut->GetValue(2, 2) = 2.0f / (paramTop - paramBottom);
    paramMatrixOut->GetValue(3, 3) = 1.0f / (paramZ_Far - paramZ_Near);
    paramMatrixOut->GetValue(4, 1) =
        (paramLeft + paramRight) / (paramLeft - paramRight);
    paramMatrixOut->GetValue(4, 2) =
        (paramTop + paramBottom) / (paramBottom - paramTop);
    paramMatrixOut->GetValue(4, 3) = paramZ_Near / (paramZ_Near - paramZ_Far);
    return paramMatrixOut;
}


int main(int argc, char const *argv[]) {
    FloatMatrix A;

    return 0;
}
#include <stdafx.h>


////////////////   求一个整数的整数次方   ////////////////
bool bInvalidInput = false;
bool equal(double num1, double num2){
    if( (num1-num2 > -0.0000001) && (num1-num2) < 0.0000001 )
        return true;
    else
        return false;
}
double PowerWithUnsignedExponent(double base, unsigned int exponent){
    double result = 1.0;
    for(int i=1; i<=exponent; ++i){
        result *= base;
    }
    return result;
}
double Power(double base, int exponent){
    bInvalidInput = false;

    if( equal(base, 0.0) && exponent < 0 ){
        bInvalidInput = true;
        return 0.0;
    }

    unsigned int absExponent = (unsigned int)(exponent);
    if( exponent < 0 ){
        absExponent = (unsigned int)(-exponent);
    }

    double result = PowerWithUnsignedExponent(base, absExponent);
    if(exponent < 0){
        result = 1.0 / result;
    }
     return result;
}
////////////////   求一个整数的整数次方   ////////////////







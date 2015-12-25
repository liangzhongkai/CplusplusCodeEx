#include <stdio.h>


float InvSqrt(float x)
{
    float xhalf = 0.5f*x;
    int i = *(int*)&x; // get bits for floating VALUE
    i = 0x5f375a86- (i>>1); // gives initial guess y0
    x = *(float*)&i; // convert bits BACK to float
    x = x*(1.5f-xhalf*x*x); // Newton step, repeating increases accuracy
    return x;
} 


int main()
{
    float fvar = 9.01;
    printf("%.6lf\n", InvSqrt(fvar));
    float fvar1 = 16.01;
    printf("%.6lf\n", InvSqrt(fvar1));
    float fvar2 = 25.01;
    printf("%.6lf\n", InvSqrt(fvar2));
    float fvar3 = 36.01;
    printf("%.6lf\n", InvSqrt(fvar3));
    return 0;

}
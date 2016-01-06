#include <stdafx.h>

//1 static的对象是脱离对象的，寿命是从程序开始到程序结束
class A
{
public:
   static int aaaa;
};
A::aaaa = 0;

//2 local static & non-local static
//  供对外使用的对象最好使用local static
//  non-local static即全局static，初始化次序不能确定






#include <stdafx.h>

//1 operator=
//   返回一个reference to *this,  适用于所有带有=的运算符：+=|-=|*=等
class Widget{
public:
    Widget & operator=(const Widget& rhs){
        //。。。。
        return * this;
    }
};
//自我赋值
Widget list[10];
for(int i=0; i<10; ++i){
    for(int j=0; j<10; ++j){
        list[i] = list[j];        //潜在的自我赋值，i 可能等于 j
    }
}
//所以要兼备安全性
// <1>
//Widget & Widget::operator=(const Widget& rhs){
//    if( this != &rhs ){
//        Widget tmp(rhs);
//        swap(tmp);
//    }
//    return * this;
//}
// <2>
//Widget & Widget::operator=(Widget rhs){
//    if( this != &rhs ){
//        swap(rhs);
//    }
//    return * this;
//}


//2 operator[]
//   返回一个const reference 



#include <stdafx.h>

//1 operator=
//   ����һ��reference to *this,  ���������д���=���������+=|-=|*=��
class Widget{
public:
    Widget & operator=(const Widget& rhs){
        //��������
        return * this;
    }
};
//���Ҹ�ֵ
Widget list[10];
for(int i=0; i<10; ++i){
    for(int j=0; j<10; ++j){
        list[i] = list[j];        //Ǳ�ڵ����Ҹ�ֵ��i ���ܵ��� j
    }
}
//����Ҫ�汸��ȫ��
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
//   ����һ��const reference 



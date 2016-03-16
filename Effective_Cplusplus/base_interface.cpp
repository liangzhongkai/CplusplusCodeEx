﻿#include <stdafx.h>


//1 参数类型控制
struct Day{
    explicit Day(int d):val(d){};     //禁止隐式类型转换
    int val;
};
struct Month{
    explicit Month(int d):val(d){};     //禁止隐式类型转换
    int val;
};
struct Year{
    explicit Year(int d):val(d){};     //禁止隐式类型转换
    int val;
};
class Date{
public:
    Date(const Month& m, const Day& d, const Year& y);
};
Date d(Month(2), Day(30), Year(1999));
//Date d(2, 30, 1999);//报错


//2 返回值类型控制
class Item{
private:
    int a;
};
std::tr1::shared_ptr<Item> createItem(){    //强迫用户使用某种类型
    return std::tr1::shared_ptr<Item>(new Item);
}

//3 函数名字
//   统一以  "动词_名词"  这种形式


//4 参数的值、引用、地址？
//   小型type(例如内置类型)，都应该用pass-by-value
//   其他尽量用pass-by-reference-to-const


//5 返回值
//    有些返回值不能用引用的，例如：
//         const Rational operator* ( const Rational & lhs, const Rational & rhs );

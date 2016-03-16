#include <stdafx.h>

//1 内部分两大部分：
//   技术部分 =》例如将构造函数设为私有，实现单例，继承它的也必须是单例
//   逻辑部分 =》成员函数 和 成员变量<都设为private>

//2 外部用途：
//   垂直：是否用于多态性质, 还是单例
//   垂直：继承方式
//   水平：友元

//3 design class的考虑点
//   如何被创建 和 销毁
//   初始化 和 赋值 有什么不一样
//   这个class被passed by value
//   异常处理
//   是否有继承图系
//   新class的类型转换
//   哪些运算符是合理的
//   private，public，protected的划分
//   是否一般化==template
//   反思是否真的需要这个class

//4 用非成员函数代替成员函数，这样灵活性更高
class WebBrowser{
public:
    void clearA(){}
    void clearB(){}
    void clearAll(){                                     //成员函数，但clearBrowser比clearAll封装性、弹性都要好
        clearA();
        clearB();
    }
};
void clearBrowser( WebBrowser& wb ){   //非成员函数
    wb.clearA();
    wb.clearB();
}






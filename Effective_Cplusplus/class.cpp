#include <stdafx.h>

//1 内部分两大部分：
//   技术部分 =》对外/垂直/水平/内部
//   逻辑部分 =》如何映射到技术，这就产生了设计模式   ！！！

//2 主要技术：
//   对外：单例
//   垂直：继承方式
//   水平：友元、成员指针解除继承耦合
//   内部：成员的构建和销毁，接口的开放和设计，assert防止逻辑错误
//   共享：static，指针

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






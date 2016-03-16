#include <stdafx.h>

//1 类里的常量(define是全局的，跨作用域的)
class Player2{
private://内部使用
    enum{ NumTurns = 5 };
};
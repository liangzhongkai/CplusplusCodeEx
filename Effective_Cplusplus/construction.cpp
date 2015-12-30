#include <stdafx.h>

//1 内置类型     C++不保证他们的初始化
int x = 0;
double d = 0.0L;

//2 非内置类型 ，要靠构造函数进行初始化，而类成员变量应该在参数列表里赋值
class ABEntry{
private:
    string theName;
    string theAddress;
    string thePhone;
};
ABEntry::ABEntry(const string & name, const string & address, const string & phone)
    :theName(name),theAddress(address),thePhone(phone)  //成员初值列表，按照定义的顺序去赋值
{
    //现在，构造函数不需要任何操作
}





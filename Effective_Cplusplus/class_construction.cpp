#include <stdafx.h>

//1 内置类型     C++不保证他们的初始化
int x = 0;
double d = 0.0L;


//2 非内置类型 ，要靠构造函数进行初始化，而类成员变量应该在参数列表里初始化
class ABEntry{
public:
   ABEntry(const string & name, const string & address, const string & phone);
private:
   string theName;
   string theAddress;
   string thePhone;
};
ABEntry::ABEntry(const string & name, const string & address, const string & phone)
   :theName(name),theAddress(address),thePhone(phone)  //成员初值列表，按照定义的顺序去初始化
{
   //这里的操作都是赋值
}


//3 了解程序开始，到程序结束的各类成员的初始化次序
//  避免在某些对象在初始化时候使用了未初始化的对象
//  场合：提供对象给客户使用，就要确保自己的东西都准备好了
class FileSystem 
{
public:
   std::size_t numDisks();
};
FileSystem & tfs()
{
   static FileSystem fs;   //虽然在多线程环境有不确定性，但确保了使用fs对象之前已经初始化了
   return fs;
}
//客户使用
class Dir 
{
public:
   Dir();
};
Dir::Dir()
{
   std::size_t disks = tfs().numDisks();
}

//4 各种类型构造函数
FileSystem e1;        //default construction
//下面两种为传值
FileSystem e2(e1);  //copy construction
e2 = e1;                 //copy assignment construction   operator =
//如果想阻止这些行为, 实现每一个对象都独一无二, 但是有可以被继承
class HomeForSale{
public:
    int aaa();
protected:
    HomeForSale();                                      //禁止default construction
    ~HomeForSale();                                    //禁止default destruction
private:
    HomeForSale(const HomeForSale& );     //禁止copy construction
    HomeForSale& operator=(const HomeForSale&)const;  //禁止copy assignment construction
};


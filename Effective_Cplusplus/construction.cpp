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
//  场合：提供对象给客户使用
class FileSystem 
{
public:
   std::size_t numDisks();
};
FileSystem & tfs()
{
   static FileSystem fs;   //在多线程环境有不确定性
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





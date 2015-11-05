#ifndef SINGLETON_H_
#define SINGLETON_H_

/*
from:  http://www.cnblogs.com/ccdev/archive/2012/12/19/2825355.html
实现：1、变量和构造函数为私有
          2、线程安全在于  初始化变量的时候，避免多个线程去new这个变量
          3、获取变量的函数为：public, static, const
*/


/*
饿汉模式：即无论是否调用该类的实例，在程序开始时就会产生一个该类的实例，并在以后仅返回此实例。
由静态初始化实例保证其线程安全性，WHY？
因为静态实例初始化在程序开始时进入主函数之前就由主线程以单线程方式完成了初始化，不必担心多线程问题。
故在性能需求较高时，应使用这种模式，避免频繁的锁争夺
*/
class SingletonStatic
{
private:
    static const SingletonStatic* m_instance;
    SingletonStatic(){}
public:
    static const SingletonStatic* getInstance()
    {
        return m_instance;
    }
};

#endif
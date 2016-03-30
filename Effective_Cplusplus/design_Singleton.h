#ifndef SINGLETON_H_
#define SINGLETON_H_

/*
实现<涉及的技术>：
    1、变量和构造函数为私有
    2、线程安全在于  初始化变量的时候，避免多个线程去new这个变量
    3、获取变量的函数为：public, static, const
特点<应用逻辑场景和技术限制分析>：
    初始化次序不明确，即静态变量不能相互依赖
    They make it harder to reason about code   代码几百个地方使用到它，需要逐个排错
    They encourage coupling 例如物理引擎代码和音频代码不应该耦合在一起，但如果音频代码提供全局变量，那物理引擎就有机会引用到，这应该禁止
    They aren’t concurrency-friendly  如果用锁解决，粒度可能很大
    单例模式保障了单个实例，但更重要的是你如何使用，对这个系统的发展有没有限制
    单例模式如果被继承了，子类就不再是单例
    assert也可以实现单例
    常用于：logicserver全局变量，日志全局变量，各式各样的管理器mgr
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





class FileSystem
{
public:
    static FileSystem& instance();

    virtual ~FileSystem() {}
    virtual char* readFile(char* path) = 0;
    virtual void  writeFile(char* path, char* contents) = 0;

protected:
    FileSystem() {}
};

class PS3FileSystem : public FileSystem
{
public:
    virtual char* readFile(char* path)
    {
        // Use Sony file IO API...
    }

    virtual void writeFile(char* path, char* contents)
    {
        // Use sony file IO API...
    }
};

class WiiFileSystem : public FileSystem
{
public:
    virtual char* readFile(char* path)
    {
        // Use Nintendo file IO API...
    }

    virtual void writeFile(char* path, char* contents)
    {
        // Use Nintendo file IO API...
    }
};


FileSystem& FileSystem::instance()
{
#if PLATFORM == PLAYSTATION3
    static FileSystem *instance = new PS3FileSystem();
#elif PLATFORM == WII
    static FileSystem *instance = new WiiFileSystem();
#endif

    return *instance;
}




class FileSystem
{
public:
    FileSystem()
    {
        assert(!instantiated_);
        instantiated_ = true;
    }

    ~FileSystem() { instantiated_ = false; }

private:
    static bool instantiated_;
};

bool FileSystem::instantiated_ = false;


#endif


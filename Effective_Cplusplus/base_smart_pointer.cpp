#include <stdafx.h>

/////////////////////////////////////
//            用于资源管理
//   1 对于临时、零散的资源，可以立即使用智能指针
//   2 专门设计资源管理中心
/////////////////////////////////////


//1 std::auto_ptr
class Item{
private:
    int a;
};
Item* createItem(){
    return new Item();      //Resource Acquisition Is Initialization ; RAII    资源取得时机便是初始化时机
}
void f1(){
    std::auto_ptr<Item> pItem(createItem());    //获得资源的同时应立即放进管理对象中 【管理对象->资源】，管理对象对资源的生死负责
    //auto_ptr的析构函数会自动删除pItem
}
void f2(){
    //std::auto_ptr的唯一性
    std::auto_ptr<Item> pItem1(createItem());
    std::auto_ptr<Item> pItem2(pItem1);     //pItem2获取资源，pItem1设为NULL
    pItem1 = pItem2;                                   //pItem1获取资源，pItem2设为NULL
}

//2 std::shared_ptr
//   引用为0，就销毁
void f3(){
    //std::auto_ptr的唯一性
    std::tr1::shared_ptr<Item> pItem1(createItem());
    std::tr1::shared_ptr<Item> pItem2(pItem1);     //pItem2，pItem1共指向同一个对象，资源引用数加1
    pItem1 = pItem2;                                   //无任何改变
    // pItem2，pItem1销毁后，资源引用数为0，立即销毁
}
//   控制删除行为和时刻
template<class T>
inline void deleteItem(T * x){
    delete x;
}
std::tr1::shared_ptr<Item> pItem(static_cast<Item*>(0), deleteItem<Item>);


//3 智能指针销毁对象,  是delete,  而非delete[]
std::tr1::shared_ptr<Item> pItem1(new Item[4]);    //结果只会销毁[0]对应的元素
//boost::scoped_array    和   boost::shared_array   才是std::auto_ptr和std::tr1::shared_ptr的数组版本

//4 资源管理中心
//允许复制
class Mutex;
class Lock1{
public:
    explicit Lock1(Mutex* pm):mutexPtr(pm, unlock){
        lock(mutexPtr.get() );
    }
private:
    std::tr1::shared_ptr<Mutex> mutexPtr;     //Lock析构时，如果mutexPtr引用为0，会unlock销毁Mutex，无需特意定义析构函数
};
//uncopy
class Lock2{
private:     //copy construction define in private
    explicit Lock2(Mutex* pm):mutexPtr(pm, unlock){
        lock(mutexPtr.get() );
    }
private:
    std::tr1::shared_ptr<Mutex> mutexPtr;     //Lock析构时，如果mutexPtr引用为0，会unlock销毁Mutex，无需特意定义析构函数
};
//能动态感知调节内存等资源使用量

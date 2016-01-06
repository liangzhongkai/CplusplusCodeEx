#include <stdafx.h>

/////////////////////////////////////
//            ������Դ����
//   1 ������ʱ����ɢ����Դ����������ʹ������ָ��
//   2 ר�������Դ��������
/////////////////////////////////////


//1 std::auto_ptr
class Item{
private:
    int a;
};
Item* createItem(){
    return new Item();      //Resource Acquisition Is Initialization ; RAII    ��Դȡ��ʱ�����ǳ�ʼ��ʱ��
}
void f1(){
    std::auto_ptr<Item> pItem(createItem());    //�����Դ��ͬʱӦ�����Ž���������� ���������->��Դ��������������Դ����������
    //auto_ptr�������������Զ�ɾ��pItem
}
void f2(){
    //std::auto_ptr��Ψһ��
    std::auto_ptr<Item> pItem1(createItem());
    std::auto_ptr<Item> pItem2(pItem1);     //pItem2��ȡ��Դ��pItem1��ΪNULL
    pItem1 = pItem2;                                   //pItem1��ȡ��Դ��pItem2��ΪNULL
}

//2 std::shared_ptr
//   ����Ϊ0��������
void f3(){
    //std::auto_ptr��Ψһ��
    std::tr1::shared_ptr<Item> pItem1(createItem());
    std::tr1::shared_ptr<Item> pItem2(pItem1);     //pItem2��pItem1��ָ��ͬһ��������Դ��������1
    pItem1 = pItem2;                                   //���κθı�
    // pItem2��pItem1���ٺ���Դ������Ϊ0����������
}
//   ����ɾ����Ϊ��ʱ��
template<class T>
inline void deleteItem(T * x){
    delete x;
}
std::tr1::shared_ptr<Item> pItem(static_cast<Item*>(0), deleteItem<Item>);


//3 ����ָ�����ٶ���,  ��delete,  ����delete[]
std::tr1::shared_ptr<Item> pItem1(new Item[4]);    //���ֻ������[0]��Ӧ��Ԫ��
//boost::scoped_array    ��   boost::shared_array   ����std::auto_ptr��std::tr1::shared_ptr������汾

//4 ��Դ��������
//������
class Mutex;
class Lock1{
public:
    explicit Lock1(Mutex* pm):mutexPtr(pm, unlock){
        lock(mutexPtr.get() );
    }
private:
    std::tr1::shared_ptr<Mutex> mutexPtr;     //Lock����ʱ�����mutexPtr����Ϊ0����unlock����Mutex���������ⶨ����������
};
//uncopy
class Lock2{
private:     //copy construction define in private
    explicit Lock2(Mutex* pm):mutexPtr(pm, unlock){
        lock(mutexPtr.get() );
    }
private:
    std::tr1::shared_ptr<Mutex> mutexPtr;     //Lock����ʱ�����mutexPtr����Ϊ0����unlock����Mutex���������ⶨ����������
};
//�ܶ�̬��֪�����ڴ����Դʹ����

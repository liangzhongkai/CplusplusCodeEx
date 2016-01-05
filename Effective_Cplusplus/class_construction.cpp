#include <stdafx.h>

//1 ��������     C++����֤���ǵĳ�ʼ��
int x = 0;
double d = 0.0L;


//2 ���������� ��Ҫ�����캯�����г�ʼ���������Ա����Ӧ���ڲ����б����ʼ��
class ABEntry{
public:
   ABEntry(const string & name, const string & address, const string & phone);
private:
   string theName;
   string theAddress;
   string thePhone;
};
ABEntry::ABEntry(const string & name, const string & address, const string & phone)
   :theName(name),theAddress(address),thePhone(phone)  //��Ա��ֵ�б����ն����˳��ȥ��ʼ��
{
   //����Ĳ������Ǹ�ֵ
}


//3 �˽����ʼ������������ĸ����Ա�ĳ�ʼ������
//  ������ĳЩ�����ڳ�ʼ��ʱ��ʹ����δ��ʼ���Ķ���
//  ���ϣ��ṩ������ͻ�ʹ�ã���Ҫȷ���Լ��Ķ�����׼������
class FileSystem 
{
public:
   std::size_t numDisks();
};
FileSystem & tfs()
{
   static FileSystem fs;   //��Ȼ�ڶ��̻߳����в�ȷ���ԣ���ȷ����ʹ��fs����֮ǰ�Ѿ���ʼ����
   return fs;
}
//�ͻ�ʹ��
class Dir 
{
public:
   Dir();
};
Dir::Dir()
{
   std::size_t disks = tfs().numDisks();
}

//4 �������͹��캯��
FileSystem e1;        //default construction
//��������Ϊ��ֵ
FileSystem e2(e1);  //copy construction
e2 = e1;                 //copy assignment construction   operator =
//�������ֹ��Щ��Ϊ, ʵ��ÿһ�����󶼶�һ�޶�, �����п��Ա��̳�
class HomeForSale{
public:
    int aaa();
protected:
    HomeForSale();                                      //��ֹdefault construction
    ~HomeForSale();                                    //��ֹdefault destruction
private:
    HomeForSale(const HomeForSale& );     //��ֹcopy construction
    HomeForSale& operator=(const HomeForSale&)const;  //��ֹcopy assignment construction
};


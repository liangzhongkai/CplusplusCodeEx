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
//  ���ϣ��ṩ������ͻ�ʹ��
class FileSystem 
{
public:
   std::size_t numDisks();
};
FileSystem & tfs()
{
   static FileSystem fs;   //�ڶ��̻߳����в�ȷ����
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





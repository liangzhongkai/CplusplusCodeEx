#include <stdafx.h>

//1 ��������     C++����֤���ǵĳ�ʼ��
int x = 0;
double d = 0.0L;

//2 ���������� ��Ҫ�����캯�����г�ʼ���������Ա����Ӧ���ڲ����б��︳ֵ
class ABEntry{
private:
    string theName;
    string theAddress;
    string thePhone;
};
ABEntry::ABEntry(const string & name, const string & address, const string & phone)
    :theName(name),theAddress(address),thePhone(phone)  //��Ա��ֵ�б����ն����˳��ȥ��ֵ
{
    //���ڣ����캯������Ҫ�κβ���
}





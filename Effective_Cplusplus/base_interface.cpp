#include <stdafx.h>


//1 �������Ϳ���
struct Day{
    explicit Day(int d):val(d){};     //��ֹ��ʽ����ת��
    int val;
};
struct Month{
    explicit Month(int d):val(d){};     //��ֹ��ʽ����ת��
    int val;
};
struct Year{
    explicit Year(int d):val(d){};     //��ֹ��ʽ����ת��
    int val;
};
class Date{
public:
    Date(const Month& m, const Day& d, const Year& y);
};
Date d(Month(2), Day(30), Year(1999));
//Date d(2, 30, 1999);//����


//2 ����ֵ���Ϳ���
class Item{
private:
    int a;
};
std::tr1::shared_ptr<Item> createItem(){    //ǿ���û�ʹ��ĳ������
    return std::tr1::shared_ptr<Item>(new Item);
}

//3 ��������
//   ͳһ��  "����_����"  ������ʽ

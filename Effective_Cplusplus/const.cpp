#include <stdafx.h>


//1 ��ֵ����
const double AspectRatio = 1.653;    


//2 �ַ���
const char * const authorName = "kct";
//���õ�������const std::string authorName("kct");


//3 ����ĳ���(define��ȫ�ֵģ����������)
class Player1{
private://�ڲ�ʹ��
   static const int NumTurns = 5;
};


//4 
//4.1 ��ָͨ��
char str[] = "kct";
char * p1 = str;                  //����
const char * p2 = str;            //const ����
char * const p3 = str;            //const ָ��      �е�������
const char * const  p4 = str;     //const ָ��  ����
//4.2 STL��ָ�� -- ��ƽʱ�ĸպ��෴
vector<int> i1(10,1);
vector<int>::iterator iter1 = i1.begin();
const vector<int>::iterator iter2 = i1.begin();
vector<int>::const_iterator iter3 = i1.begin();
//iter1++;   //OK
//iter2++;   //ERROR
//iter3++;   //OK
//*iter3 = 10;  //ERROR


//5 ����
//���ñ������һ��char * const��ζ������constָ��


//6 ����������ֵ���������棩
class TextBlock1{
public:
   //��ȷ��ȷ���������õİ�ȫ����ȷ�������ڲ�non-static�İ�ȫ<��Ҫ����������������Ϊmutable>
   const char & operator[](std::size_t position) const{     
      return text[position];
   }
   //����const ���µ��õĵط������޸�ֵ
   //char & operator[](std::size_t position) const{           
   //    return text[position];
   //}
private:
   std::string text;
};


//7 ����ת��
class TextBlock2{
public:
   const char & operator[](std::size_t position) const{  
      //......
      return text[position];
   }
   char & operator[](std::size_t position) {
      return 
      const_cast<char&>(                                                   //�����޸����͵�const��volatile����
      static_cast<const TextBlock2&>(*this)[position]      //const TextBlock2&   �������const�����Ͳ��ܵ�������const�汾��operator[]
   );
}
private:
   std::string text;
};




int main()
{
   iter1++;      //OK
   //iter2++;    //ERROR
   iter3++;      //OK
   //*iter3 = 10;//ERROR
   printf("%d\n", *iter1);

   return 0;
}


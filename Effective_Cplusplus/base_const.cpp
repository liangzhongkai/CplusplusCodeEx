#include <stdafx.h>


//1 数值类型
const double AspectRatio = 1.653;    


//2 字符串
const char * const authorName = "kct";
//更好的做法：const std::string authorName("kct");


//3 类里的常量(define是全局的，跨作用域的)
class Player1{
private://内部使用
   static const int NumTurns = 5;
};


//4 
//4.1 普通指针
char str[] = "kct";
char * p1 = str;                  //随意
const char * p2 = str;            //const 数据
char * const p3 = str;            //const 指针      有点像引用
const char * const  p4 = str;     //const 指针  数据
//4.2 STL的指针 -- 跟平时的刚好相反
vector<int> i1(10,1);
vector<int>::iterator iter1 = i1.begin();
const vector<int>::iterator iter2 = i1.begin();
vector<int>::const_iterator iter3 = i1.begin();
//iter1++;   //OK
//iter2++;   //ERROR
//iter3++;   //OK
//*iter3 = 10;  //ERROR


//5 引用
//引用本身就有一种char * const的味道，即const指针


//6 函数（返回值、参数后面）
class TextBlock1{
public:
   //正确，确保返回引用的安全，还确保函数内部non-static的安全<若要消除，将变量设置为mutable>
   const char & operator[](std::size_t position) const{     
      return text[position];
   }
   //不用const 导致调用的地方可以修改值
   //char & operator[](std::size_t position) const{           
   //    return text[position];
   //}
private:
   std::string text;
};


//7 类型转换
class TextBlock2{
public:
   const char & operator[](std::size_t position) const{  
      //......
      return text[position];
   }
   char & operator[](std::size_t position) {
      return 
      const_cast<char&>(                                                   //用来修改类型的const或volatile属性
      static_cast<const TextBlock2&>(*this)[position]      //const TextBlock2&   这个加了const的类型才能调用上面const版本的operator[]
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


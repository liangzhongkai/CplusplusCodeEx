//*    288K	63MS	C++	1600B    并查集

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
 
struct product{
	long p,d; 
}pr[11000];     //商品数组
 
long f[11000]; //父节点数组
 
int cmp(product a, product b){
	return a.p>b.p; 
}
 
long findIn(long day){
         long tmpDay;
         tmpDay=day;

         while(f[tmpDay]!=tmpDay) tmpDay=f[tmpDay];    //找到day的根节点为tmpDay

         while(f[day]!=day){
                   day=f[day];
                   f[day]=tmpDay;                      //压缩路径，将路径中所有点的父节点赋值为其根节点
         }
         return tmpDay;                                //返回根节点
}
 
int main()
{
         long n,i,maxDay,ans,day;
         while(scanf("%ld",&n)!=EOF){
                   maxDay=0;
                   for(i=0;i<n;i++){
                            scanf("%ld%ld",&pr[i].p,&pr[i].d);
                            if(pr[i].d>maxDay) maxDay=pr[i].d;         //找到可以销售最晚的日期
                   }

                   for(i=0;i<=maxDay;i++)   f[i]=i;                    //初始化，每天的根节点为自己
                   sort(pr,pr+n,cmp);                                  //按照利润从大到小排序
                   
				   ans=0;
                   for(i=0;i<n;i++){
                            day=findIn(pr[i].d);      //找到该节点的根节点
                            if(day){                  //如果找到的不是0，说明此商品可以销售
									 f[day]=day-1;    //那么该天已经有商品销售，不能再销售新商品，父节点（不//一定是根节点，根节点有寻找和路径压缩的过程）成为前//一天。
                                     ans+=pr[i].p;    //加上该商品可以获得的利润
                            }
                   }
                   printf("%ld\n",ans);                   //输出最大能获得的利润
         }
         return 0;
}
//*/
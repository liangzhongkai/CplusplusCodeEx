//*    288K	63MS	C++	1600B    ���鼯

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
 
struct product{
	long p,d; 
}pr[11000];     //��Ʒ����
 
long f[11000]; //���ڵ�����
 
int cmp(product a, product b){
	return a.p>b.p; 
}
 
long findIn(long day){
         long tmpDay;
         tmpDay=day;

         while(f[tmpDay]!=tmpDay) tmpDay=f[tmpDay];    //�ҵ�day�ĸ��ڵ�ΪtmpDay

         while(f[day]!=day){
                   day=f[day];
                   f[day]=tmpDay;                      //ѹ��·������·�������е�ĸ��ڵ㸳ֵΪ����ڵ�
         }
         return tmpDay;                                //���ظ��ڵ�
}
 
int main()
{
         long n,i,maxDay,ans,day;
         while(scanf("%ld",&n)!=EOF){
                   maxDay=0;
                   for(i=0;i<n;i++){
                            scanf("%ld%ld",&pr[i].p,&pr[i].d);
                            if(pr[i].d>maxDay) maxDay=pr[i].d;         //�ҵ������������������
                   }

                   for(i=0;i<=maxDay;i++)   f[i]=i;                    //��ʼ����ÿ��ĸ��ڵ�Ϊ�Լ�
                   sort(pr,pr+n,cmp);                                  //��������Ӵ�С����
                   
				   ans=0;
                   for(i=0;i<n;i++){
                            day=findIn(pr[i].d);      //�ҵ��ýڵ�ĸ��ڵ�
                            if(day){                  //����ҵ��Ĳ���0��˵������Ʒ��������
									 f[day]=day-1;    //��ô�����Ѿ�����Ʒ���ۣ���������������Ʒ�����ڵ㣨��//һ���Ǹ��ڵ㣬���ڵ���Ѱ�Һ�·��ѹ���Ĺ��̣���Ϊǰ//һ�졣
                                     ans+=pr[i].p;    //���ϸ���Ʒ���Ի�õ�����
                            }
                   }
                   printf("%ld\n",ans);                   //�������ܻ�õ�����
         }
         return 0;
}
//*/
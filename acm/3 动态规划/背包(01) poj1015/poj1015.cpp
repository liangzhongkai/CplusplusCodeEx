/*    400K	16MS	C++	2371B
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int f[30][1000],path[30][1000] ;
int p[300],d[300],ans[30] ;


int main()
{
      int n,m;
	  int i, j, k;
      int tcase = 0 ;
      scanf("%d%d",&n,&m) ;
      while(n)
	  {
            tcase++ ;
            memset(f,-1,sizeof(f)) ;
            memset(path,0,sizeof(path)) ;
            int p_d = m*20 ;
            f[0][p_d] = 0 ;
            for (i=1 ; i<=n ; i++)
			{
                  scanf("%d%d",p+i,d+i) ;
            }
            for (j=0 ; j<m ; j++)
			{
                  for (k=0 ; k<=p_d*2 ; k++)
				  {
                        if (f[j][k]>=0)
						{
                              for (i=1 ; i<=n ; i++)
							  {
                                    if (f[j][k]+p[i]+d[i]>f[j+1][k+p[i]-d[i]])
									{
                                          int t1=j,t2=k ;
                                          while (t1>0 && path[t1][t2]!=i)
										  {
                                                t2 -= p[path[t1][t2]]-d[path[t1][t2]] ;
                                                t1-- ;
                                          }
                                          if (t1==0)
										  {
                                                f[j+1][k+p[i]-d[i]] = f[j][k]+p[i]+d[i] ;
                                                path[j+1][k+p[i]-d[i]] = i ;
                                          }
                                    }
                              }
                        }
                  }
            }

            i=p_d ;
            j=0, k=0 ;

            while (f[m][i+j]<0 && f[m][i-j]<0)
			{
                  j++ ;
            }
            if (f[m][i+j]>f[m][i-j])
			{
                  k=i+j ;
            }
            else
			{
                  k=i-j ;
            }

            printf("Jury #%d\n",tcase) ;
            printf("Best jury has value %d for prosecution and value %d for defence:\n",
                   (k-p_d+f[m][k])/2,(f[m][k]-k+p_d)/2) ;
            for (i=1 ; i<=m ; i++)
			{
                  ans[i] = path[m-i+1][k] ;
                  k -= p[ans[i]] - d[ans[i]] ;
            }

            sort (ans+1,ans+m+1) ;

            for (i=1 ; i<=m ; i++){
                  printf(" %d",ans[i]) ;
            }
            printf("\n\n") ;
            scanf("%d%d",&n,&m) ;
      }

    return 0;
}
//*/


/*    336K	110MS	C++	2672B

#include <cstdio>
 #include <cstring>
 #include <vector>
 #include <algorithm>
  using namespace std;
 
 #define maxn 220
 #define offset 25*20
 pair <int , int> cdd[maxn];
 int dp[22][400+offset];
 int par[22][400+offset];
 vector <int> order;
 
 int cmp(int a,int b){return a>b;}

 //candidate[a] exists in i men
 int notused(int a , int i, int p){
     while(par[i][p] != -1)
     {
         if( par[i][p] == a)return 0;
         p  = p - cdd[par[i][p]].first + cdd[par[i][p]].second;
         i--;
     }
     return 1;
 }
 
 int main(){
     int i, j , k , p ,n , m ,ncase=0;
     while( scanf("%d %d",&n,&m) != EOF && m)
     {
         memset(dp , -1 , sizeof(dp));
         memset(par , 0 , sizeof(par));
         dp[0][offset] = 0;
         par[0][offset] = -1;
         for(i=0 ; i<n ; i++)
             scanf("%d %d",&cdd[i].first,&cdd[i].second);
 
         //        dp[j][p] = max( dp[j-1][p+first[i]-second[i]] + first[i] + second[i])  
         for(i=1 ; i<=m ; i++)
         {    // 01 
             for(p=0 ; p<400+offset ; p++)
             {
                 if( dp[i-1][p] != -1)
                 {
                     for(j=0 ; j<n ; j++)
                     {
                         if(notused(j,i-1,p) && dp[i-1][p]+cdd[j].first+cdd[j].second > dp[i][p+cdd[j].first-cdd[j].second])
                         {
                             dp[i][ p+cdd[j].first-cdd[j].second ] = dp[i-1][p]+cdd[j].first+cdd[j].second;
                             par[i][ p + cdd[j].first - cdd[j].second ] = j;
                         }
                     }
                 }//if
             }
         }// for(i)
 
         for( k=0 ; k<=20*m ; k++)
         {
             if(dp[m][offset+k]!=-1 || dp[m][offset-k]!=-1 )
                 break;
         }
         if( dp[m][offset-k] > dp[m][offset+k]) k = -k;
 
         p = offset+k; i=m;
         order.clear();
         while(par[i][p] != -1)
         {
             order.push_back(par[i][p]);
             p = p -  cdd[par[i][p]].first + cdd[par[i][p]].second;
             i--;
         }
         pair <int,int> count=make_pair(0,0);
         for(i=0 ; i<order.size() ; i++)
         {
             count.first += cdd[order[i]].first;
             count.second += cdd[order[i]].second;
         }
         printf("Jury #%d\nBest jury has value %d for prosecution and value %d for defence:\n",++ncase , count.first,count.second);
         sort(order.begin(),order.end(),cmp);
         for(i=order.size()-1 ; i>=0 ; i--)printf(" %d",order[i]+1);
         printf("\n\n");
         
     }
     return 0;
 }
//*/




 /*                         492K	79MS	C++	1706B	
 #include <iostream>
using namespace std;
int main()
{
    long i,j,k,l,n,m,t1,maxf,count;
    long p[210],d[210],f[210],s[210];
    long can[30];
    long res[30][1000],from[30][1000];
    
    count=0;
    cin>>n>>m;
    while(n!=0 || m!=0)
    {
        count++;
        
        for(i=0;i<n;i++)
        {
            cin>>p[i]>>d[i];
            f[i]=p[i]-d[i];
            s[i]=p[i]+d[i];
        }
        maxf=20*m;
        
        for(i=0;i<=m;i++)
			for(j=0;j<=maxf*2;j++)
				res[i][j]=-1;

			res[0][maxf]=0;
			from[0][maxf]=-1;
			
			for(i=0;i<m;i++)
				for(j=0;j<=maxf*2;j++)
					if(res[i][j]!=-1)
					{
						for(k=0;k<n;k++)
						{
							t1=j;
							for(l=i;l>0;l--)
							{
								if(from[l][t1]==k) break;
								t1-=f[from[l][t1]];
							}
							if(l!=0) continue;
							
							t1=res[i][j]+s[k];
							if(res[i+1][j+f[k]]<t1)
							{
								res[i+1][j+f[k]]=t1;
								from[i+1][j+f[k]]=k;
							}
						}
					}
					
					for(i=0;i<=maxf;i++)
					{
						if(res[m][maxf+i]>res[m][maxf-i]) { t1=maxf+i; break;}
						if(res[m][maxf-i]!=-1) { t1=maxf-i; break;}
					}
					
					cout<<"Jury #"<<count<<endl;
					cout<<"Best jury has value "<<(res[m][t1]+t1-maxf)/2<<" for prosecution";
					cout<<" and value "<<(res[m][t1]-t1+maxf)/2<<" for defence:"<<endl;
					
					for(i=m;i>0;i--)
					{
						can[i]=from[i][t1];
						t1-=f[can[i]];
					}
					
					for(i=1;i<m;i++)
						for(j=i+1;j<=m;j++)
							if(can[i]>can[j]) swap(can[i],can[j]);
							
							for(i=1;i<=m;i++)
								cout<<" "<<can[i]+1;
							cout<<endl<<endl;
							
							cin>>n>>m;
    }
    return 0;
}

 //*/


 /*
 题意:现在法官要从公众中随机挑选n个人最为陪审团的候选人,然后再从这n个人中选m个人组成陪审团,选取m人的规则是:

      控方和辩方会根据自己对候选人的喜欢程度,给所有的候选人打分,分值从0……20.那么选出的m个人,必须满足辩方总分和控方总分的差的绝对值最小,

      如果有多种选择方案的辩方的总分和控方总分的差的绝对值相同,那么选取辩方总分和控方总分之和最大的方案即可.

      把所有候选人的辩方总分和控方总分之差称为"辩控差",总分之和称为"辩控和",第i个候选人的辩控差记为v[i],辩控和记为s[i].

	  用f[i][j]表示在取第i个候选人,使其辩控差为j的所有方案中,辩控和最大的那个方案,称为方案f(i,j)的辩控和,

	  如果没法选取第i个人,使其辩控差为j,那么f[i][j]的值就为-1,即方案f(i,j)不可行,
	  
	  该题要求选取m个人,那么,如果对所有的j的可能取值球出了所有的f[m][j] (-20*m<=j<=20*m),那么陪审团方案自然就容易找到了.

      方案f(i,j)是由某个可行方案f(i-1,x) (-20*m<=x<=20*m)递推而来的,而可行方案f(i-1,x)能推出方案f(i,j)的必要条件是:
	  
	  存在某个候选人k,满足k在方案f(i-1,x)中没有被选上,且x+v[k]=j.在所有满足该必要条件的f(i-1,x)中选出f(i-1,x)+s[k]的值最大的那个,
	  
	  那么方案f(i-1,x)再加上候选人k就推出了方案f(i,j),在这过程中,用数组path[i][j]来记录方案f(i,j)中最后选的那个候选人的编号,最后确定了解决方案之后,
	  
	  从f[m][j]出发,可以求出所有候选人的编号.

      初始时可以确定f[0][0]=0,由此出发,逐步递推,就能求出所有的可行方案f(m,j) (-20*m<=j<=20*m),
	  
	  根据题意辩控差可能为负数,因为f[m][j]中的j存放的是选取第m个候选人时的辩控差,而数组下标不能为负数,
	  
	  所以可以将辩控差的值都加上20*m来避免数组f[i][j]的下标出现负数,如题目实际的辩控差为0时,那么对应变换之后的辩控差为temp=20*m,
	  
	  很显然辩控差的取值范围是[0,2*temp].

      根据最后求解出来的方案f(m,j),f[m][j]中j为选取m个候选人的辩控差为j(注意这时的辩控差是变换之后的辩控差,实际的辩控差为:j-temp),
	 
	  f[m][j]存放的是辩控差为j的方案中最大的辩控和,那么有:

      V-S=j-temp;
      V+S=f[m][j]
    可以推出:V=(f[m][j]+j-temp)/2       V=(f[m][j]-j+temp)/2
    输出选取的陪审团人选时需要按升序顺序输出,那么就先进行升序排序后再进行输出.


	//    396K	16MS	C++	2836B
#include<iostream>
#include<string>
#include<cstdlib>
#include<algorithm>
using namespace std;

int f[25][1000];                                                      //f[i][j]表示取第i个候选人,使其辩控差为j的所有方案中辩控和最大的那个方案
int path[25][1000];                                                //path[i][j]表示方案f(i,j)中最后选取的那个候选人的编号
int result[25];                                                         //存放选取的陪审团成员
int p[205];
int d[205];

int cmp(const void * a,const void * b)
{
	return *(int *)a-*(int *)b;
}

int main()
{
	int i,j,x,y,k,m,n,temp,ncase=0;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		   if(n==0&&m==0)
				break;
		   for(i=1;i<=n;i++)
				scanf("%d%d",&p[i],&d[i]);

		   memset(f,-1,sizeof(f));
		   memset(path,0,sizeof(path));
		   temp=20*m;                                                         //即实际中辩控差为0时对应的变换后的辩控差(加上了20*m)
		   f[0][temp]=0;                                                      //初始时f[0][0]=0,相对应变换后f[0][temp]=0

		   for(i=0;i<m;i++)                                                   //每次循环选出第i个人,共要选出m人
			  for(j=0;j<=2*temp;j++)                                          //可能的辩控差范围时[0,2*temp](变换之后的)
				 if(f[i][j]>=0)                                               //方案f(i,j)可行
				 {
					for(k=1;k<=n;k++)                                         //在方案f(i,j)的基础上,选取下一个候选者
					   if(f[i][j]+p[k]+d[k]>f[i+1][j+p[k]-d[k]]) //该条件如果不成立,则说明了原来已经有了成立的方案f(i+1,j+p[k]-d[k]),后来的方案不优于这个方案
					   {
							x=i;
							y=j;
							while(x>0&&path[x][y]!=k)                         //判断第k个人是否已经在方案f(i,j)中被选中了
							{
								 y-=p[path[x][y]]-d[path[x][y]];
								 x--;
							}
							if(x==0)                                           //第k个人在方案f(i,j)中没有被选中
							{
								 f[i+1][j+p[k]-d[k]]=f[i][j]+p[k]+d[k];        //那么在方案f(i,j)的基础上,选取第k个人,形成方案f(i+1,j+p[k]-d[k])
								 path[i+1][j+p[k]-d[k]]=k;                     //记录新方案选取的成员
							}
					   }
				 }

		   i=temp;
		   k=0;
		   while(f[m][i+k]<0&&f[m][i-k]<0)                                      //找到可行的方案f(i,j)                                                    
				k++;
		   if(f[m][i+k]>f[m][i-k])                                              //最终方案中对应的辩控差为j
				j=i+k;
		   else
				j=i-k;

		   printf("Jury #%d\n",++ncase);
		   printf("Best jury has value %d for prosecution and value %d for defence:\n",(f[m][j]+j-temp)/2,(f[m][j]-j+temp)/2);

		   for(i=1;i<=m;i++)                                                
		   {
				result[i] = path[m-i+1][j];
				j -= p[result[i]]-d[result[i]];
		   }

		   qsort(result+1,m,sizeof(result[1]),cmp);

		   for(i=1;i<=m;i++)
				printf("%d ",result[i]);

		   printf("\n\n");
	}
	//system("pause");
	return 0;
}
 //*/
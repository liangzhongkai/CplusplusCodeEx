/*

735 3 4 125 6 5 3 350
633 4 500 30 6 100 1 5 0 1
735 0
0 3 10 100 10 50 10 10

735
630
0
0

//*/

/*
#include<iostream>

using namespace std;

int main()
{
	

	return 0;
}


//*/

















/*    Run Time: 0.01secs    Run Memory: 408KB                           搜索 所有合适的情况值

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <math.h>
#include<iostream>
#include<stdio.h>
#include<math.h>

using namespace std;

int a[11];
int num[11];
bool used[100010];
int maxn;

int main()
{
	 int i;
	 int cash;
	 while(scanf("%d",&cash)==1)
	 {
		   int n;
		   scanf("%d",&n);
		   for(i=1;i<=n;i++)
				scanf("%d%d",&num[i],&a[i]);

		   memset(used,0,sizeof(used));
		   int maxn=0;
		   used[0]=1;

		   for(i=1; i<=n&&maxn!=cash; i++)
		   {
			   for(int j=maxn; j>=0&&maxn!=cash; j--)
				   if( used[j] )
				   {
						for(int k=1;k<=num[i]&&maxn!=cash;k++)
						{
							 if(j+k*a[i]>cash)    //超出
								break;
							 if(used[j+k*a[i]])    //已经有过这种情况
								break;

							 used[j+k*a[i]]=1;     //标记这种情况

							 if(j+k*a[i]>maxn)
								maxn=j+k*a[i];      //求最大值
						}
				   }  
		   }
		   cout<<maxn<<endl;
	 }
	 return 0;
}
//*/





/*    Run Time: 0.1secs    Run Memory: 1092KB                                              D P

#include <iostream>
#include<cstring>
#include<cstdio>
using namespace std;

#define MAX 100002
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))

int bill[10][2]; // 面值 b[i,1] 有 b[i,0] 个
int b[110];
int m[2][MAX]; // 滚动数组；m[i,j]: 前i种面值组成的不超过j的最大总面值
int n, cash;
int nIndex;
int cnt;

void dp()
{
    int i, v;
    memset(m, 0, sizeof(m));

    for(v=b[0]; v<=cash; v++)
	{
        m[0][v] = b[0];
    }

    int vmax;
    int x, y;

    for(i=1; i<nIndex; i++)
	{
        x = i % 2;
        y = (i+1) % 2;
        vmax = min(b[i]-1, cash);

        for(v=0; v<=vmax; v++) 
		{
            m[x][v] = m[y][v];
            cnt = max(m[x][v], cnt);
        }
        for(v=b[i]; v<=cash; v++)
		{
            m[x][v] = max(m[y][v], m[y][v-b[i]] + b[i]);
            cnt = max(m[x][v], cnt);
        }
    }
}

int main()
{
    while( EOF != scanf("%d%d", &cash, &n) )
    {
        int i, j;
        for(i=0; i<n; i++)
            scanf("%d%d", &bill[i][0], &bill[i][1]);
        cnt = 0;
        nIndex = 0;
        for(i=0; i<n; i++) 
		{
            j = 1;
            while( 2*j <= bill[i][0] ) 
			{
                b[nIndex++] = j * bill[i][1];
                j<<=1;
            }
            if( bill[i][0]-j+1 > 0 )
                b[nIndex++] = (bill[i][0]-j+1) * bill[i][1];
        }
        dp();
        printf("%d\n", cnt);
    }
    return 0;
}

//*/











/*  	0.14s	704KB                          

#include <iostream>
#include <cstring>
using namespace std;

int n[11], d[11];
int cash, count;
int f[100001];
int result;

void multipack(int val, int amount)
{
        int k = 1, v;
        int cand;

        while (k < amount)
        {
                for (v = 100000; v >= k*val; v--)
                {
                        cand = f[v-k*val] + k*val;
						
                        if (cand <= cash && cand > f[v])
                                f[v] = cand;
                        if (f[v] > result)
								result = f[v];
                }
                amount -= k;
                k <<= 1;
        }

        for (v = 100000; v >= amount*val; v--)
        {
                cand = f[v-amount*val] + amount*val;

                if ( cand <= cash && cand > f[v] )
                        f[v] = cand;
                if ( f[v] > result ) 
						result = f[v];
        }

}

int main()
{
        int i, j, k;

        while (cin >> cash >> count)
        {
                memset(n, 0, sizeof(n));
                memset(d, 0, sizeof(d));
                memset(f, 0, sizeof(f));

                for (i = 0; i < count; i++)
                {
                        cin >> n[i+1] >> d[i+1];
                }
                for (i = count; i > 1; i--)                      //从大到小排序
                {
                        for (j = 1; j < i; j++)
                        {
                                if (d[j] < d[j+1])
                                {
                                        k = d[j]; d[j] = d[j+1]; d[j+1] = k;
                                        k = n[j]; n[j] = n[j+1]; n[j+1] = k;
                                }
                        }
                }

                result = 0;
                if (cash == 0 || count == 0 )
                {
                        cout << result << endl;
                }
                else
                {
                        for (i = 1; i <= count; i++)
                                multipack(d[i], n[i]);
                        cout << result << endl;
                }

        }
        return 0;
}

//*/


/*
	#include<cstdio>
　　
　　using namespace std;
　　
　　int N;
　　int c[12] , v[12];
　　int dp[100008];
　　int s[10008];
　　int f[11] = {1,2,4,8,16,32,64,128,256,512,1024};
　　
　　int main()
　　{
　　 int w;
　　 while(scanf("%d%d" , &N , &w) != EOF)
　　 {
　　 int i , j , k;
　　 for(i = 1 ; i <= w ; i ++)
　　 scanf("%d%d" , &c[i] , &v[i]);
　　
　　 k = 1;
　　 for(i = 0 ; i <= N ; i ++)
　　 dp[i] = 0;
　　 for(i = 1 ; i <= w ; i ++)
　　 {
　　 if(c[i] == 0) continue;
　　 s[k++] = v[i];
　　 j = 1;
　　 c[i] --;
　　 while(c[i] > f[j])
　　 {
　　 s[k++] = f[j] * v[i];
　　 c[i] -= f[j];
　　 j++;
　　 }
　　 if(c[i] > 0)
　　 s[k++] = c[i]*v[i];
　　 }
　　
　　 for(i = 1 ; i < k ; i ++)
　　 {
　　 for(j = N ; j >= s[i] ; j --)
　　 if(dp[j] < dp[j-s[i]] + s[i])
　　 dp[j] = dp[j-s[i]] + s[i];
　　 }
　　
　　 printf("%d\n" , dp[N]);
　　 }
　　 return 0;
　　}

//*/





/*     Run Time: 0.03secs    Run Memory: 696KB                                深刻理解：01背包、完全背包、多重背包

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_VOLUMN 100001
#define MAX_N 11
#define max(a,b) ((a)>(b) ? (a) : (b))
int vol, n;                                             // 背包容量 ;数量
int cv[MAX_N], num[MAX_N], f[MAX_VOLUMN];               
 

void ZeroOnePack(int cost, int value)                   //（01）体积、质量、费用；价值
{
     int v;
     for(v=vol; v>=cost; v--)
         f[v] = max(f[v], f[v-cost]+value);
}
 

void CompletePack(int cost, int value)                 //（无限）体积、质量、费用；价值
{
     int v;
     for(v=cost; v<=vol; v++)
         f[v] = max(f[v], f[v-cost]+value);
}
 
void  MultiplePack(int cost, int value, int amount)     //（多重）体积、质量、费用；价值；数量
{
     int k = 1;
     if(cost*amount >= vol)
         CompletePack(cost, value);
     else
     {
         while((amount-k) >= 0)
         { 
             ZeroOnePack(cost*k, value*k);
             amount -= k;
             k = k*2;
         }
         ZeroOnePack(cost*amount, value*amount);
     }
}
void dp()
{
     int i;
     for(i=1; i<=n; i++)
         MultiplePack(cv[i], cv[i], num[i]);
}
 
int  main(int argc, char **argv)
{
     int i;
     while(scanf("%d %d", &vol, &n)!=EOF)
     {   memset(f, 0, sizeof(f));
         for(i=1; i<=n; i++)
             scanf("%d %d", num+i, cv+i);
         dp();
         printf("%d\n", f[vol]);                       //最大数
     }
	 return 0;
}

 
//*/


/*                                                                           深刻理解：01背包、完全背包、多重背包
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
int f[100010],v;

int max(int a,int b) { return (a-b)>0?a:b; }
void zeroonepack(int cost)
{
    for (int i=v;i>=cost;i--) f[i]=max(f[i],f[i-cost]+cost);
}
void completepack(int cost)
{
    for (int i=cost;i<=v;i++) f[i]=max(f[i],f[i-cost]+cost);
}
void multiplepack(int cost,int amount)
{
    if (amount*cost>=v) { completepack(cost); return; }
    int k=1;
    while (k<amount)
    {
        zeroonepack(k*cost);
        amount-=k; k*=2;
    }
    zeroonepack(amount*cost);
}
int main(int argc, char** argv)
{
    int n,i,cost[12],amount[12];

    while (scanf("%d%d",&v,&n)!=EOF)
    {
        if (n==0) { printf("0\n"); continue; }
        for (i=1;i<=n;i++) scanf("%d%d",&amount[i],&cost[i]);
        if (v==0) { printf("0\n"); continue; }
        memset(f,0,sizeof(f));
        for (i=1;i<=n;i++) multiplepack(cost[i],amount[i]);
        printf("%d\n",f[v]);
    }

    return (EXIT_SUCCESS);
}
//*/











/*                                                                    深刻理解：01背包、完全背包、多重背包
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_VOLUMN 100001
#define MAX_N 11
#define max(a,b) ((a)>(b) ? (a) : (b))
int vol, n;
int cv[MAX_N], num[MAX_N], f[MAX_VOLUMN];

// f[i][v] = max(f[i-1][v], f[i-1][v-cost[i]]+value[i]) 
void ZeroOnePack(int cost, int value)
{
    int v;
     for(v=vol; v>=cost; v--)
         f[v] = max(f[v], f[v-cost]+value);
}
 
// f[i][v] = max(f[i-1][v], f[i][v-cost[i]]+value[i]) 
void CompletePack(int cost, int value)
{
    int v;
    for(v=cost; v<=vol; v++)
         f[v] = max(f[v], f[v-cost]+value);
}

void MultiplePack(int cost, int value, int amount)
{
    int k = 1;
    if(cost*amount >= vol)
         CompletePack(cost, value);
    else {
        while((amount-k) >= 0) {  
            ZeroOnePack(cost*k, value*k);
            amount -= k;
             k = k*2;
        }
         ZeroOnePack(cost*amount, value*amount);
     }
}

void dp()
{
    int i;
    for(i=1; i<=n; i++)
         MultiplePack(cv[i], cv[i], num[i]);
}
 
int main(int argc, char **argv)
{
    int i;
    while(scanf("%d %d", &vol, &n)!=EOF) {
        memset(f, 0, sizeof(f));
        for(i=1; i<=n; i++)
             scanf("%d %d", num+i, cv+i);
        dp();
         printf("%d\n", f[vol]);
    }
}
//*/
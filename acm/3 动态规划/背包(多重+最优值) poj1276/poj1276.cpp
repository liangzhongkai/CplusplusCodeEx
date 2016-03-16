/*   640K	47MS	C++	1191B
#include<iostream>
#include<algorithm>

using namespace std;

#define max(a,b) (a)>(b)?(a):(b)

int money[15];
int num[15];
int ans[100010];
int n, m;

void ZeroOnePack(int value)                   //（01）体积、质量、费用；价值
{
     int v;
     for(v=n; v>=value; v--)
         ans[v] = max(ans[v], ans[v-value]+value);
}
void CompletePack(int value)                 //（无限）体积、质量、费用；价值
{
     int v;
     for(v=value; v<=n; v++)
         ans[v] = max(ans[v], ans[v-value]+value);
}
void  MultiplePack(int value, int amount)     //（多重）体积、质量、费用；价值；数量
{
     int k = 1;
     if(value*amount >= n)
         CompletePack(value);
     else
     { 
         while((amount-k) >= 0)
         {
             ZeroOnePack(value*k);
             amount -= k;
             k = k<<1;
         }
         ZeroOnePack(value*amount);
     }
}
void dp()
{
     int i;
     for(i=0; i<m; i++)
         MultiplePack(money[i], num[i]);
}


int main()
{
	int i;
	while(cin >> n >> m )
	{
		for(i=0; i<m; i++)
			cin >> num[i] >> money[i];
			
		memset(ans, 0, sizeof(ans));      // 不要求装满!
		if(n==0 || m==0)
		{
			cout << 0 << endl;
		}
		else
		{
			dp();
			cout << ans[n] <<  endl;
		}

	}

	return 0;
}


/*      556K	47MS	C++	1425B
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
/*
    
样例输入

1000 5
800 2
400 5
300 5
400 3
200 2
1000 5
800 2
400 5
300 5
400 3
200 2

样例输出

3900
3900


*/

/*Run Time: 0.01secs    Run Memory: 3828KB
#include<iostream>
#include<cstring>

using namespace std;

int sum[30][30010];   //sum[n][m]自下而上   n个物品，m元情况下的最大求和值      
int price[30];
int weight[30];


int main()
{
    int n, m;
    int i, j;
    
    while( cin >> m >> n )   //个数n，钱数m 
    {
           for( i=1; i<=n; i++ )
                cin >> price[i] >> weight[i] ;
          
           //自下而上 
           for( i=n; i>=1; i-- )
                for( j=0; j<=m; j++ )
                {
                     sum[i][j] = ( i==n ? 0:sum[i+1][j] );    //初始化底层数据：最开始还有n个的时候的sum值为0
                     if( j>=price[i] )   //v[i] 为该物品价格 
                         sum[i][j] >?= sum[i+1][j-price[i]] + weight[i]*price[i];
                } 
           cout << sum[1][m] << endl; 
    }
    
    return 0;    
} 
//*/


//    Run Time: 0secs    Run Memory: 428KB

#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

#define MAX_VOLUMN 30001
#define MAX_N 26
#define max(a,b) ((a)>(b) ? (a) : (b))

int vol, n;                                             // 背包容量 ;数量
int cv[MAX_N], num[MAX_N], f[MAX_VOLUMN];           
 
void ZeroOnePack(int cost, int value)                   //（01）体积、质量、费用；价值
{
     int v;
     for(v=vol; v>=cost; v--)
         f[v] = max(f[v], f[v-cost]+value*cost);
}
 

void CompletePack(int cost, int value)                 //（无限）体积、质量、费用；价值
{
     int v;
     for(v=cost; v<=vol; v++)
         f[v] = max(f[v], f[v-cost]+value*cost);
}

void dp()
{
     int i;
     for(i=1; i<=n; i++)
         ZeroOnePack(num[i], cv[i]);
}
 
int  main()
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


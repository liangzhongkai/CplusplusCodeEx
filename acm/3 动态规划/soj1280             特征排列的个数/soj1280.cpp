/*
Sample Input

2 1 2
4 1 3 2 4
8 5 3 4 8 6 7 2 1
9 6 8 4 2 1 5 9 3 7
9 1 2 3 4 5 6 7 8 9
9 9 8 7 6 5 4 3 2 1
9 1 5 9 3 6 2 8 7 4
8 5 3 4 8 6 7 2 1
10 6 5 7 9 2 4 8 3 1 10
100 1 5 9 6 3 2 4 7 8 10 12 11 13 15 14 18 16 17 19 20 22 23 21 24 26 25 28 29 27 30 32 33 36 31 35 34 38 39 37 40 42 43 45 41 44 46 48 47 49 50 51 52 53 56 54 55 57 58 59 60 61 63 62 65 64 66 67 69 68 70 72 75 73 76 74 71 78 77 79 80 83 81 82 85 86 84 87 88 89 90 91 93 92 96 95 98 97 94 99 100
1 1
0 

Sample Output

1
5
531
1735
1
1
2590
15246
5156439960395796894
0
*/

//            Time Limit Exceeded     >1sec   312 KB
/*
#include<iostream>
#include<cstring>

using namespace std;

int ans;
int per[105];
bool vis[105];

void dp( int n, int p[], int ceng, int last )
{
    if( ceng==n )
    {
        ans++;
        return;
    }
        
    int i;
    if( p[ceng-1]==0 )
    {
        for( i=1; i<last; i++  )
        {
             if( vis[i]==false )
             {
                 vis[i] = true;
                 dp( n, p, ceng+1, i );
                 vis[i] = false;
             }
        }
    }
    if( p[ceng-1]==1 )
    {
        for( i=last+1; i<=n; i++ )
        {
             if( vis[i]==false )
             {
                 vis[i] = true;
                 dp( n, p, ceng+1, i );
                 vis[i] = false;
             }
        }
    }
}


int main()
{
    int n, i;
    while( cin>>n && n!=0 )
    {
           for( i=0; i<n; i++ )
           {
                cin >> per[i];
           }
           for( i=0; i<n-1; i++ )
           {
                if( per[i]<per[i+1] )
                    per[i] = 1;
                else
                    per[i] = 0;
           }
           
           memset( vis, false, sizeof(vis) );
           ans = 0;
           for( i=1; i<=n; i++ )
           {
               vis[i] = true;
               dp( n, per, 1, i );
               vis[i] = false;
           }
           
           cout << ans << endl;
    }
    
    return 0;
}
*/



//*                          Wrong Answer
#include<iostream>
#include<cstring>

using namespace std;

int per[101];
long long d[101][101];

int main()
{
    int n, i, j, k;
    while( cin>>n && n!=0 )
    {
           for( i=1; i<=n; i++ )
           {
                cin >> per[i];
           }
           for( i=1; i<n; i++ )
           {
                if( per[i]<per[i+1] )
                    per[i] = 1;
                else
                    per[i] = 0;
           }
           
           
           //初始化 
           memset( d, 0, sizeof(d) );
           if( per[1]==0 )
           {
               d[2][1] = 1;
               d[2][2] = 0;
           }
           else if( per[1]==1 )
           {
               d[2][1] = 0;
               d[2][2] = 1;
           }
           
           //DP过程     
           for( i=3; i<=n; i++ )
              for( j=1; j<=i; j++ )
              {
                 if( per[i-1]==0 )
                 {
                    for( k=j; k<=i-1; k++ )
                    {
                          d[i][j]  += d[i-1][k];
                    }
                 }
                 else 
                 {
                    for( k=1; k<j; k++ )   //这里k绝不能等于j， 想想是为什么？呵呵。。。
                    {
                          d[i][j]  += d[i-1][k];
                    }
                 }
              }
           
           long long ans = 0; 
               for( i=1; i<=n; i++ )
                    ans += d[n][i];
                
           cout << ans << endl;
    }
    
    return 0;
}
//*/




/*           Run Time: 0secs    Run Memory: 392KB                               分析出了比我的状态更好的状态，DP功力就在此处。 
 
#include<stdio.h>
#include<cstring>
//#include<ctime>
//#include<cmath>
//#include<algorithm>
#include<iostream>
//#include<vector>
//#include<queue>

using namespace std;

int a[101];
int v[101];
int f[101][101];
int n,m;

int main()
{
    int ca=0;
    while(scanf("%d",&n)==1&&n)
    {
        for(int i=1;i<=n;i++)
                scanf("%d",&a[i]);
                
        //初始化 
        for(int i=2;i<=n;i++)
        {
            if(a[i]<a[i-1])v[i]=0;
            else v[i]=1;   
        }
        memset(f,0,sizeof(f));
        f[1][0]=1;
        
        //DP
        for(int i=2;i<=n;i++)
            for(int j=0;j<=i-2;j++)
            {
                if(v[i])
                {
                    for(int k=j+1;k<=i-1;k++)
                            f[i][k]+=f[i-1][j];
                   
                }
                else
                {
                    for(int k=0;k<=j;k++)
                            f[i][k]+=f[i-1][j];
                }
              
            }  
            
        long long ans=0;
        for(int j=0;j<n;j++)
                ans+=f[n][j];
        cout<<ans<<endl;
    }
    return 0;
} 
//*/

 /*      0 sec     332 KB    
#include <cstdio>
#include <memory.h>
using namespace std;

const int N = 100;
long long cnt [N] [N];
int seq [N];
int n;

void f ()
{
    memset (cnt, 0, sizeof (cnt));
    cnt [0] [0] = 1;
    int i, j, k;
    
    for (i = 0; i < n; i ++)
        {
        scanf ("%d", &seq [i]);
        }
        
    for (i = n - 1; i; i --)
        {
        seq [i] = (seq [i] > seq [i - 1] ? 1 : 0);
        }
        
    for (i = 1; i < n; i ++)
        {
        for (j = 0; j <= i; j ++)
            {
            if (seq [i])
                {
                // 如果上升则 cnt [i - 1] [j] 对应的位置都能够产生 cnt [i] [j+1..i] 对应的某个位置
                for (k = j + 1; k <= i; k ++)
                    {
                    cnt [i] [k] += cnt [i - 1] [j];   //cnt [i - 1] [j]表示第i-1个点时有j个点比它矮 
                    }
                }
            else    
                {
                // 如果下降则 cnt [i - 1] [j] 对应的位置都能够产生 cnt [i] [0..j] 对应的某个位置
                for (k = 0; k <= j; k ++)
                    {
                    cnt [i] [k] += cnt [i - 1] [j];
                    }
                }
            }
        }
        
    long long sum = 0;
    for (i = 0;  i < n; i ++)
        {
        sum += cnt [n - 1] [i];
        }
    printf ("%lld ", sum);
}

int main ()
{
    while (scanf ("%d", &n), n)
        {
        f ();
        }
    return 0;
}
//*/



















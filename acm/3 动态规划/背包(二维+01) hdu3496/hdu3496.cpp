//  15MS	428K	874 B	C++
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int INF = 1<<30;

int n, m, l;
int dp[101][1005];

void zeroonepack(int c, int v){
	for(int i=m; i>0; i--){         // the number of movie
		for(int j=l; j>=c; j--){    // the time her father give
			if(dp[i][j]<dp[i-1][j-c]+v){
				dp[i][j] = dp[i-1][j-c]+v;
			}
		}
	}
}

int main()
{
	int tc;
	int i, j, a, b;

	scanf("%d", &tc);

	while(tc--){ 
		scanf("%d %d %d", &n, &m, &l);
		// such Initialization can promise the number of movie must be m !
		for(i=0; i<=l; i++){
			dp[0][i] = 0;
		}
		for(i=1; i<=m; i++){
			for(j=0; j<=l; j++){
				dp[i][j] = -INF;
			}
		}
		for(i=0; i<n; i++){
			scanf("%d %d", &a, &b);

			if(a<=l)
				zeroonepack(a, b);
		}
		/*
		if(dp[m][l]>0)                          // 因为它是01背包，所以不一定是最右边的那列是最大的
			printf("%d\n", dp[m][l]);
		else 
			printf("0\n");
		//*/
		int ans = 0;                            //  答案的提取
		for(i=1; i<=l; i++){
			if(ans<dp[m][i])
				ans = dp[m][i];
		}
		printf("%d\n", ans);
	}

	return 0;
}

/*
1
3 2 10
11 100
9 2
1 1

1
2 2 10
11 100
1 1
*/



/*    62MS	428K	951 B	
#include<stdio.h> 
#include<string.h> 

  const int inf=1<<30; 
  
	int dp[104][1010]; 
	int cost[110],val[110],n,vol,tle; 
	
	  int Max(int a,int b) 
	  { 
	  return a>b?a:b; 
	  } 
	  
		void work() 
		{ 
		int i,j,k; 
		
for(i=0;i<=vol;i++)
for(j=0;j<=tle;j++) 
dp[i][j]=-inf; 
dp[0][0]=0; 

for(k=1;k<=n;k++)//枚举物品 
for(i=vol;i>=1;i--)//容量 
for(j=tle;j>=cost[k];j--)//而外限制 
dp[i][j]=Max(dp[i][j],dp[i-1][j-cost[k]]+val[k]); 

int max=0; 
for(i=0;i<=tle;i++)  
if(max<dp[vol][i])  
max=dp[vol][i]; 
printf("%d\n",max); 
} 

int main() 
{ 
    int t; 
	
	freopen("d:\\1.txt","r",stdin); 
	scanf("%d",&t); 
    while(t--) 
	{ 
		scanf("%d%d%d",&n,&vol,&tle); 
        for(int i=1;i<=n;i++) 
			scanf("%d%d",&cost[i],&val[i]); 
		work(); 
	} 
    return 0; 
} 
//*/
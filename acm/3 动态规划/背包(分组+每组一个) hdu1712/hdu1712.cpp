//*    46MS	292K	663 B	C++

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <iostream>

using namespace std;

#define Max(a,b) a>b? a:b
#define NN 10010

int mat[105][105];
int dp[NN];
int n,m;

int main()
{
  int i,j,v;
  while(scanf("%d%d",&n,&m),n+m){
		for(i=1;i<=n;i++){
			for(j=1;j<=m;j++){
				scanf("%d",&mat[i][j]);
			}
		}
		for(i=1;i<=n;i++){			//分组
			for(v = m ;v >= 1;v--){	//背包容量
				for(j = 1 ;j<=m;j++){//不同时间的课程
					if(v>=j)
						dp[v] = Max(dp[v] ,dp[v-j]+mat[i][j]);
				}
			}
		}
		printf("%d\n",dp[m]);
		memset(dp,0,sizeof(dp));
	}
	return 0;
}

//*/














/*     62MS	292K	484 B	C++
#include<stdio.h>
int max(int a,int b)
{
	return a>b?a:b;
}
int f[102],a[102][102];
int main()
{
	int n,m,i,j,k;
	while(scanf("%d%d",&n,&m),n||m)
	{
		for(i=0;i<=m;i++)
			f[i]=0;
		for(i=0;i<n;i++)
			for(j=1;j<=m;j++)
				scanf("%d",&a[i][j]);
			for(i=0;i<=m;i++)
				f[i]=0;
			for(i=0;i<n;i++)
				for(k=m;k>=0;k--)
					for(j=1;j<=m;j++)
					{
						if(k<j)
							continue;
						f[k]=max(f[k],f[k-j]+a[i][j]);
					}
					printf("%d\n",f[m]);
	}
	return 0;
}
//*/
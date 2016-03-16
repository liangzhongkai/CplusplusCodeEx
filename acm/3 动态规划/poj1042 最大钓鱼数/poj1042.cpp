/*   288K	547MS	C++	1776B
#include<iostream>
#include<fstream>

using namespace std;

ifstream fin("data.txt");
#define  cin fin

const int N = 30;
const int M = 300;
int fish[N], des[N], time[N], dp[N][M], path[N][M], t[N];
int n, h;

int sum(int i, int tim){
	int ans = (fish[i]+fish[i] - des[i]*(tim-1))*tim >> 1;
	return ans;
}

void gettime(int p, int tim){
	if(p<=1) return ;
	t[p] = tim;
	h -= tim + time[p];
	gettime(p-1, path[p-1][h]);
}

int main()
{
	int i, j, k;
	int tmp, temp;
	int flag = 0;

	while(cin >> n && n!=0){
		cin >> h;
		h = h * 12;
		for(i=1; i<=n; i++){
			cin >> fish[i];
		}
		for(i=1; i<=n; i++){
			cin >> des[i];
		}
		for(i=2; i<=n; i++){
			cin >> time[i];
		}
		time[1] = 0;

		for(i=0; i<=n; i++){
			for(j=0; j<=h; j++){
				if(i)
					dp[i][j] = -1;
				else
					dp[i][j] = 0;
			}
		}

		memset(path, -1, sizeof(path));
		int max = -0x3fffffff, p;
		for(i=1; i<=n; i++){
			for(j=time[i]; j<=h; j++){
				for(k=0; k<=j-time[i]; k++){
					if(dp[i-1][k]>-1 && dp[i-1][k] + (tmp=sum(i, j-time[i]-k)) >= dp[i][j]){
						dp[i][j] = dp[i-1][k] + tmp;
						path[i][j] = j-time[i]-k;
					}
				}
				if(j>0 && dp[i][j-1]!=-1){ // 预防一行中第一个刚好去到这个岛，但没时间根本没时间钓鱼的。j>0 为必要条件
					temp = (fish[i] - path[i][j-1] * des[i]) < 0 ? 0 : (fish[i] - path[i][j-1] * des[i]);
					if(dp[i][j-1] + temp > dp[i][j]){
						dp[i][j] = dp[i][j-1] + temp;
						path[i][j] = path[i][j-1] + 1;
					}
				}
			}
			if(max<dp[i][h]){
				max = dp[i][h];  p = i;
			}
		}

		memset(t, 0, sizeof(t));
		gettime(p, path[p][h]);
		t[1] = h;                                                //  ?

		if(flag)
			cout << endl;
		for(i=1; i<n; i++){
			cout << t[i] * 5 << ", ";
		}
		cout << t[n] * 5 << endl;
		cout << "Number of fish expected: " << max << endl;
		flag = 1;
	}

	return 0;
}

//*/





//*         236K	532MS	C++	1766B
#include <stdio.h>
#include <string.h>

#define MAXN 30
#define MAXM 300
#define INF 0x3333333

int dp[MAXN][MAXM], path[MAXN][MAXM], f[MAXN], t[MAXN], d[MAXN], times[MAXN], m;

int sum(int i, int time){   // 钓time次鱼的总鱼数
	int ans  = (f[i] + f[i] - d[i] * (time - 1)) * time / 2;
	return ans;
}

void Gettimes(int p, int time){
	if(p <= 1) return;
	m -= (times[p] = time) + t[p];
	Gettimes(p - 1, path[p - 1][m]);
}

int main()
{
	int n, i, j, k, temp, CASE = 0;
	freopen("data.txt", "r", stdin);

	while(~scanf("%d", &n), n)
	{
		scanf("%d", &m);
		m = m * 12;

		for(i = 0; i <= n; i ++)
			for(j = 0; j <= m; j ++)
				if(!i)
					dp[i][j] = 0;
				else
					dp[i][j] = -1;

		memset(path, -1, sizeof(path));
		t[1] = 0;

		for(i = 1; i <= n; i ++) scanf("%d", &f[i]);  // 鱼数
		for(i = 1; i <= n; i ++) scanf("%d", &d[i]);  // 减数
		for(i = 2; i <= n; i ++) scanf("%d", &t[i]);  // 路程

		int max = - INF, p;
		for(i = 1; i <= n; i ++){
			for(j = t[i]; j <= m; j ++){              // 无需记录当总时间j<t[i]的

				for(k = 0; k <= j - t[i]; k ++)       // 当k=0,是表示在j时间内在第i个岛上钓到的最多鱼数  
					if(dp[i-1][k] != -1 && dp[i-1][k] + sum(i, j-k-t[i]) >= dp[i][j]){//利用数量关系排除了超越最大次数的钓到的鱼数 因为sum的值从小到大再到小
						dp[i][j] = dp[i-1][k] + sum(i, j-k-t[i]);
						path[i][j] = j-k-t[i];        // 表示在j时间内在第i个岛上钓到的最多鱼数
					}

				if(j > 0 && path[i][j-1] != -1){      // 处理尾数。能这样处理的原因是dp在同一行的值只会越来越大，那个边界次数的前一个必然小于边界次数的。
					temp = (f[i] - path[i][j-1] * d[i]) < 0 ? 0 : (f[i] - path[i][j-1] * d[i]);
					if(dp[i][j] < dp[i][j-1] + temp){ 
						dp[i][j] = dp[i][j-1] + temp;
						path[i][j] = path[i][j-1] + 1;
					}
				}

			}
			if(max < dp[i][m]){max = dp[i][m]; p = i;}// p代表第i个岛之后达到钓鱼的最大数，即后面的岛屿都不用去钓了。
		}

		memset(times, 0, sizeof(times));
		Gettimes(p, path[p][m]);

		times[1] = m;
		if(CASE) printf("\n");
		for(i = 1; i < n; i ++)
			printf("%d, ", times[i] * 5);
		printf("%d\n", times[n] * 5);
		printf("Number of fish expected: %d\n", max);
		CASE = 1;
	}
	return 0;
}
//*/



/*
#include<iostream>
#include<string>
#include<cstring>
#include <cmath>
#include<cstdio>
#include<algorithm>
#define Max(a,b) a>b?a:b
using namespace std;
int ti[30], fi[30][400], di[30], dp[30][400];
int h , n, i, j, k;

int main()
{
	freopen("data.txt", "r", stdin);
    while(~scanf("%d",&n)&&n)
    {
        memset(fi,0,sizeof(fi));
        scanf("%d",&h);
        h=h*12;             //共h个五分钟
        for(i=1;i<=n;i++)//i=1
			scanf("%d",&fi[i][1]);

        for(i=1;i<=n;i++)
			scanf("%d",&di[i]);

        for(i=2;i<=n;i++)//i=2
			scanf("%d",&ti[i]);
        ti[1]=0;

        for(i=1;i<=n;i++)
        {
           for(k=2;k<=h;k++)
           {
               if(fi[i][k-1]<=di[i])  break;
               fi[i][k]=fi[i][k-1]-di[i];
           }
        }

       memset(dp,-1,sizeof(dp));
       dp[0][0]=0;
       int sum,tt=0;
       for(i=0;i<n;i++)
       {
           for(j=0;j<=h;j++)
           {
		       sum=0;
               for(k=0; k<=h&&dp[i][j]!=-1; k++)//!!!**没想到这小细节还是关键来
               {
                  if(j+ti[i+1]+k>h)
					 break;

                  dp[i+1][j+ti[i+1]+k] = Max(dp[i][j]+sum, dp[i+1][j+ti[i+1]+k]);

                  if(fi[i+1][k+1]>0)
					 sum+=fi[i+1][k+1];
               }
           }
       }

        int mark=1,MAX=0;
        for(i=1;i<=n;i++)
        {
            if(MAX<dp[i][h])
            {
                MAX=dp[i][h];
                mark=i;
            }
        }

	   //cout<<"MAX="<<MAX<<endl;

       int MMAX=MAX;
        for(i=mark;i>=2;i--)
        {
           int sum=0;
           for(k=0;k<=h;k++)
           {
               if(MAX==sum+dp[i-1][h-k-ti[i]])
               {
                   fi[i][0]=k;
                   break;
               }
               sum=sum+fi[i][k+1];
           }
           h=h-ti[i]-k;
           MAX-=sum;//开端漏了
        }


        fi[1][0]=h;
        for(i=1;i<n;i++)
			printf("%d, ",fi[i][0]*5);
        printf("%d\n",fi[i][0]*5);
        printf("Number of fish expected: %d\n\n",MMAX);
    }
    return 0;
}


//*/

//*
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define max(a,b) a>b?a:b

int dp[1005];
int ans[1005];
int p;
int v[105], c[105];
int n, m, k;

void zeroonepack(int v, int c){
	int t, i;
	for(i=m; i>=c; i--){
		t = dp[i-c] + v;
		if(t>dp[i]){
			dp[i] = t;
		}
		ans[p++] = t;
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	int tc;
	int i;

	scanf("%d", &tc);
	while(tc--){
		scanf("%d %d %d", &n, &m, &k);
		for(i=0; i<n; i++){
			scanf("%d", v+i);
		}
		for(i=0; i<n; i++){
			scanf("%d", c+i);
		}

		memset(dp, 0, sizeof(dp));
		p = 0;
		for(i=0; i<n; i++){
			zeroonepack(v[i], c[i]);
		}

		sort(ans, ans+p);
		int tt = 1;
		for(i=1; i<p; i++){
			if(ans[i]!=ans[i-1])
				ans[tt++] = ans[i];
		}

		for(i=0; i<tt; i++){
			cout << ans[i] << " " ;
		}
		cout << endl;

		printf("%d\n", ans[tt-k]);
	}

	return 0;
}
//*/


/*     109MS	516K	1178 B	C++
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

int value[1005],volume[1005];
int f[1005][50],A[50],B[50];
int n,v,k;

void dp()
{
    int i,j,q,a,b,c;
    memset(f,0,sizeof(f));
    for(i=1;i<=n;i++)
        for(j=v;j>=volume[i];j--)
        {
           for(q=1;q<=k;q++)
           {
              A[q]=f[j-volume[i]][q]+value[i];  //选取新队列A
              B[q]=f[j][q];                             //选取新队列B
           }
           A[q]=-1;B[q]=-1;            //把A、B的第k+1个元素标记为-1
           a=b=c=1;
           while(c<=k&&(A[a]!=-1||B[b]!=-1))   //合并A、B两个有序队列，并赋给有序队列f[j][1...k]
           {
                  if(A[a]>B[b])
						f[j][c]=A[a],a++;
                  else
						f[j][c]=B[b],b++;
                  if(f[j][c]!=f[j][c-1])                 
						c++;
           }
        }
    cout<<f[v][k]<<endl;
}

int main()
{
    //freopen("in.txt","r",stdin);
    int t,i;
    cin>>t;
    while(t--)
    {
        cin>>n>>v>>k;
        for(i=1;i<=n;i++)
            cin>>value[i];
        for(i=1;i<=n;i++)
            cin>>volume[i];
        dp();
    }

    return 0;
}
//*/

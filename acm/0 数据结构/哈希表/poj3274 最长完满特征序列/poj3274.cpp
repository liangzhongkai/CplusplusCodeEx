/*
#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

const int N = 100010;
vector<int> hash[35];
int a[N];

int count(int a){
	int sum = 0;
	while(a>0){
		if(a&1) sum++;
		a = a>>1;
	}
	return sum;
}

void change(int a, int b){
	hash[a].push_back(b);
}

int main()
{
	int n, k;
	int i, j;

	scanf("%d%d", &n, &k);
	for(i=1; i<=n; i++){
		scanf("%d", a+i);
		//cout << count(a) << endl;
		change(count(a[i]), i);
	}

	for(i=1; i<=k; i++){
		for(j=0; j<hash[i].size(); j++)
			cout << hash[i][j] << " ";
		cout << endl;
	}
	return 0;
}
//*/



//*    26004K	313MS	C++	1555B
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

#define maxn 100005
#define maxk 32

int sum[maxn][maxk], c[maxn][maxk];
int head[maxn], next[maxn],ecount;
int n, p;

void addedge(int a)  // ecount 和 b 是一样的。
{
    next[ecount] = head[a];
    head[a] = ecount;
	ecount++;
}

int hash(int c[])
{
    int ret = 0;
    for (int i = 0; i < p; i++)
        ret = ((ret << 2) + (c[i] >> 4)) ^ (c[i] << 10);
    ret = (ret % maxn + maxn) % maxn;
    return ret;
}

void input()
{
	int i, j, k;
    memset(sum, 0, sizeof(sum));
    memset(c, 0, sizeof(c));
    memset(head, -1, sizeof(head));

    scanf("%d%d", &n, &p);

    ecount = 0;
    int ans = 0;
    addedge(hash(c[0]));

    for (i = 1; i <= n; i++)
    {
        int a;
        scanf("%d", &a);

		// 向每一位累积1
        for (j = 0; j < p; j++){
            sum[i][j] = sum[i - 1][j] + (1 & a);
            a >>= 1;
        }

        for (j = 0; j < p; j++)
            c[i][j] = sum[i][j] - sum[i][0];

        int h = hash(c[i]);
        for (j = head[h]; j != -1; j = next[j])
        {
            int ok = true;
            for (k = 0; k < p; k++)
                if (c[j][k] != c[i][k]){
                    ok = false;
                    break;
                }
            if (ok && ans < i - j)
                ans = i - j;
        }
        addedge(h);
    }
    printf("%d\n", ans);
}

int main()
{
    //freopen("t.txt", "r", stdin);
    input();
    return 0;
}
//*/




/*   26412K	344MS	C++	1598B
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

#define maxn 100005
#define maxk 32

int sum[maxn][maxk], c[maxn][maxk];
int head[maxn], next[maxn], v[maxn], ecount;
int n, p;

void addedge(int a, int b)  // ecount 和 b 是一样的。
{
    next[ecount] = head[a];
    head[a] = ecount;
    v[ecount] = b;      // 存储第ecount条边是b
	//cout << ecount << " " << b << " " << v[ecount]<< endl;
	ecount++;
}

int hash(int c[])
{
    int ret = 0;
    for (int i = 0; i < p; i++)
        ret = ((ret << 2) + (c[i] >> 4)) ^ (c[i] << 10);
    ret = (ret % maxn + maxn) % maxn;
    return ret;
}

void input()
{
	int i, j, k;
    memset(sum, 0, sizeof(sum));
    memset(c, 0, sizeof(c));
    memset(head, -1, sizeof(head));

    scanf("%d%d", &n, &p);

    ecount = 0;
    int ans = 0;
    addedge(hash(c[0]), 0);

    for (i = 1; i <= n; i++)
    {
        int a;
        scanf("%d", &a);

		// 向每一位累积1
        for (j = 0; j < p; j++){
            sum[i][j] = sum[i - 1][j] + (1 & a);
            a >>= 1;
        }
		// debug
		//for (j = 0; j < p; j++){
		//	cout << sum[i][j] << " ";
		//}
		//cout << endl;

        for (j = 0; j < p; j++)
            c[i][j] = sum[i][j] - sum[i][0];
        // debug
		//for (j = 0; j < p; j++)
		//	cout << c[i][j] << " ";
		//cout << endl;

        int h = hash(c[i]);
		//cout << h << endl;
        for (j = head[h]; j != -1; j = next[j])
        {
            int ok = true;
            for (k = 0; k < p; k++)
                if (c[v[j]][k] != c[i][k]){
                    ok = false;
                    break;
                }
            if (ok && ans < i - v[j])
                ans = i - v[j];
        }
        addedge(h, i);
    }
    printf("%d\n", ans);
}

int main()
{
    //freopen("t.txt", "r", stdin);
    input();
    return 0;
}
//*/



/*  40484K	329MS	C++	1539B

#include<iostream>

using namespace std;

#define maxn 100010
const int prime=99983;
int n,k;
int a[maxn][31],sum[maxn][31],C[maxn][31];
int hash[1000000];
int ans;

int hashcode(int *v,int k)   
{
       int i,p=0;
       for(i=0; i<k; i++)
              p=((p<<2)+(v[i]>>4))^(v[i]<<10);
       p = p%prime;
       if(p<0)   p=p+prime;
       return p;
}

int main()
{
       int i,j,x,p;
       scanf("%d%d",&n,&k);
       memset(sum,0,sizeof(sum));
       memset(hash,-1,sizeof(hash));
       memset(C,0,sizeof(C));
       hash[hashcode(C[0],k)]=0;
       ans=0;
       for(i=1;i<=n;i++)
       {
              scanf("%d",&x);
              for(j=0;j<k;j++){
                     a[i][j]=x%2;
                     x>>=1;
                     sum[i][j]=sum[i-1][j]+a[i][j];
                     C[i][j]=sum[i][j]-sum[i][0];
              }
              p=hashcode(C[i],k);
              while(hash[p]!=-1){
                     for(j=1;j<k;j++){
                            if(C[i][j]!=C[hash[p]][j])
                                   break;
                     }
                     if(j==k){
                            if(i-hash[p]>ans)
                                   ans=i-hash[p];
                            break;
                     }
                     p++;
              }
              if(hash[p]==-1)
                     hash[p]=i;
       }
       printf("%d\n",ans);
       return 0;
}
//*/
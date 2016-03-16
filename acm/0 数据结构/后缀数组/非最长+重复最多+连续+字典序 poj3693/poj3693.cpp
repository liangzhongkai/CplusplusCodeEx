//*     9580K	313MS   	C++	3075B
//      9580K	297MS	    C++	3195B     加 nn = n/2
//      9580K	329MS	    C++	3258B
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

#define min(a, b) a<b?a:b

const int N = 100005;
int sa[N], rank[N], height[N], cnt[N], wa[N], wb[N];
int r[N];   char ch[N]; 
int Log[N];   int best[20][N];  // 20层 可以 概括 2^20个数，绰绰有余。。。
int n;

int cmp(int *x, int a, int b, int l){
	return (x[a]==x[b]) && (x[a+l]==x[b+l]);
}

// 附加的0值在r[],rank[]的后面；但是在sa[],height[]的前面
void suffix(int *s){
	// sa数组
	int *x = wa, *y = wb, *t;
	int i, j, p, k;
	memset(rank, 0, sizeof(rank));
	memset(height, 0, sizeof(height));
	memset(sa, 0, sizeof(sa));

	int mm = 30;
	memset(cnt, 0, sizeof(cnt));
	for(i=0; i<n; i++)   cnt[x[i]=s[i]]++;
	for(i=1; i<mm; i++)   cnt[i] += cnt[i-1];
	for(i=n-1; i>=0; i--)  sa[--cnt[x[i]]] = i;

	for(j=1, p=1; p<n; mm=p, j*=2){
		for(p=0, i=n-j; i<n; i++)   y[p++] = i;
		for(i=0; i<n; i++)
			if(sa[i]>=j)   y[p++] = sa[i] - j;
		for(i=0; i<mm; i++)   cnt[i] = 0;
		for(i=0; i<n; i++)   cnt[x[y[i]]]++;
		for(i=1; i<mm; i++)   cnt[i] += cnt[i-1];
		for(i=n-1; i>=0; i--)   sa[--cnt[x[y[i]]]] = y[i];

		for(t=x, x=y, y=t, p=1, x[sa[0]]=0, i=1; i<n; i++)
			x[sa[i]] = cmp(y, sa[i], sa[i-1], j)?p-1:p++;
	}
	// rank数组
	for(i=0; i<n; i++){
		rank[sa[i]] = i;
	}
	
	// 另一种height数组
	for(k=0, i=0; i<n; height[rank[i++]]=k)
		for(k?k--:0, j=sa[rank[i]-1]; s[i+k]==s[j+k]; k++);
}

void rmq(){
	int i, j, t = Log[n];
	for(i=1; i<=n; i++)   best[0][i] = height[i];     // 抛弃了自己附加的r[0] = 0
	for(i=1; i<=t; i++){
		int limit = n - (1<<i) + 1;
		for(j=1; j<=limit; j++){
			best[i][j] = min(best[i-1][j] , best[i-1][j+(1<<i>>1)]);
		}
	}
}

// 注意后面还有一个自己附加的0值
int lcp(int a, int b){    
	a = rank[a],   b = rank[b];
	if(a==b)   return n - sa[a];
	if(a>b)   a = a^b,   b = a^b,   a = a^b;
	a++;
	int t = Log[b - a + 1];
	return min(best[t][a], best[t][b - (1<<t) + 1]);  // best[t][a]的范围可能只是[a, k1]的最长公共子串            所以，you see!
		                                             // best[t][b-(1<<t)+1]的范围是[k2, b]的最长公共子串
}


int main()
{
	freopen("in.txt", "r", stdin);
	int i, j;
	int cas = 0;

	// 统计出 1~N 的log值
	Log[0] = -1;
    for(i=1;i<=N;i++)
        Log[i]=(i&(i-1))?Log[i-1]:Log[i-1] + 1 ;

	while(scanf("%s", ch) && ch[0]!='#'){
		n = strlen(ch);
		for(i=0; i<n; i++){
			r[i] = ch[i] - 'a' + 1;
		}
		r[n++] = 0;
		suffix(r);
		rmq();                    // 默认 n
		
		int l, r, t, k, maxx=-1, nn = n/2, ans=0;  
		for(l=1; l<nn; l++){     // 枚举长度
			for(i=0; i+l<n; i+=l){
				k = lcp(i, i+l);
				r = k/l + 1;      // r为重复次数
				t = l - k%l;
				t = i - t;
				if (t>=0 && k%l!=0){  // 向后退了小于 l 位
					if(lcp(t, t+l)>=k)
						r++;
				}
				if(r>maxx){       // maxx最大重复次数
					maxx = r;
					ans= l;  
				}
			}  
		}  
		int start;  
		for(i=1; i<=n; i++){          // sa数组是保证字典序的神器啊 Orz 
			if( lcp(sa[i],sa[i]+ans)>=(maxx-1)*ans ){
				start = sa[i];
				l = ans * maxx;    // 总长度 = 单位长度 * 重复数
				break;
			}
		}  

		printf("Case %d: ", ++cas);
		for(int i=0; i<l; i++)
			printf("%c", ch[start+i]);
        printf("\n");  
	}

	return 0;
}
//*/




/*       10092K	407MS	C++	3147B

#include <iostream>
#include <cmath>
#include<cstring>
#include<cstdio>
using namespace std;

const int MAX_LEN = 100001;
const int MAX_DEP = 20;

int wa[MAX_LEN], wb[MAX_LEN], wv[MAX_LEN], wd[MAX_LEN], Height[MAX_LEN], sa[MAX_LEN], rank[MAX_LEN];
int s[MAX_DEP][MAX_LEN];
int n;
#define min(a,b) a>b?b:a

inline bool IsEqual(int *r, int a, int b, int l)
{
    return (r[a] == r[b] && r[a + l] == r[b + l]);
}

void da(int *r, int m = 27)
{
    int i, j, p, *x = wa, *y = wb, *t;
    memset(wd, 0, sizeof(wd));
    for (i = 0; i < n; i++) wd[x[i] = r[i]]++; x[n] = y[n] = 0;
    for (i = 1; i < m; i++) wd[i] += wd[i - 1];
    for (i = n - 1; i >= 0; i--) sa[--wd[x[i]]] = i;

    for (p = 1, j = 1; p <= n; m = p, j *= 2)
    {
        for(p = 0, i = n - j; i < n; i++) y[p++] = i;
        for(i = 0; i < n; i++)if(sa[i] >= j)y[p++] = sa[i] - j;
        for(i = 0; i < n; i++) wv[i] = x[y[i]];
        memset(wd, 0, sizeof(wd));
        for(i = 0; i < n; i++) wd[wv[i]]++;
        for(i = 1; i < m; i++) wd[i] += wd[i - 1];
        for(i = n - 1; i >= 0; i--) sa[--wd[wv[i]]] = y[i];
        for(t = x, x = y, y = t, i = 1, p = 2,x[sa[0]] = 1; i < n; i++)
            x[sa[i]] = IsEqual(y, sa[i-1], sa[i], j) ? p - 1 : p++;
    }
}

void CalHeight(int *r)
{
    int i, j, k;
    for (i = 0; i < n; i++)rank[sa[i]] = i;
    for (i = 0, Height[0] = k = 0; i < n; Height[rank[i++]] = k)
        for (k?k--:0, j=(rank[i]>0)?sa[rank[i]-1]:0; rank[i]>0&&r[i+k]==r[j+k]; k++);
}

void RMQInit()   // 目的是找出数组中最小的那个。
{
    int i, j, t, m;
    m = floor( log(double(n)) / log(2.0) );
    for(i = 0; i < n; i++) s[0][i] = Height[i];
    for (j = t = 1; j <= m; j++, t *= 2)
    {
        for(i = 0; i < n - t; i++) s[j][i] = min(s[j-1][i], s[j-1][i + t]);
        for(i = n - t; i < n; i++) s[j][i] = s[j-1][i];
    }
}

int RMQQuery(int i, int j)
{
    if(i == j) return n - sa[i];
    if (j < i) j += i, i = j - i, j -= i;
    int m = floor( log(double(j - i)) / log(2.0) );
    return min(s[m][i + 1], s[m][j - (1 << m) + 1]);
}

int main()
{
	freopen("in.txt", "r", stdin);
    char str[MAX_LEN];
    int r[MAX_LEN];
    int i, j, k, ss, maxn, len, l, sp, t, tsp, iter = 0;
    while(scanf("%s", str) && str[0] != '#')
    {
        n = strlen(str), maxn = 0, iter++;
        memset(r, 0, sizeof(r));
        for (i = 0; i < n; i++)  r[i] = str[i] - 'a' + 1;
        da(r);
        CalHeight(r);
        RMQInit();

		//for(i=0; i<5; i++){
		//	for(j=0; j<n; j++)
		//		printf("%d ", s[i][j]);
		//	printf("\n");
		//}

        for (i = 1; i <= n / 2; i++)
            for (j = i; j < n; j += i)
            {
                len = RMQQuery(rank[j - i], rank[j]);
				//cout << rank[j-i] << " " << rank[j] << " " << len << endl;
                tsp = (len || rank[j - i] < rank[j]) ? j - i : j;

                for (k = j - i - 1, ss = 0; k >= 0 && k > (j - 2 * i) && r[k] == r[k + i]; k--)
                    if(++ss == (i-(len%i)))tsp = k;
                    else if(rank[tsp] > rank[k])tsp = k;
                
				l = (ss + len)/i + 1;
                if(l > maxn) maxn = l, sp = tsp, t = i;
                else if(l == maxn && rank[sp] > rank[tsp])maxn = l, sp = tsp, t = i;
            }

        printf("Case %d: ", iter);
        for (i = 0; i < maxn * t; i++) 
			printf("%c", str[sp + i]);
        printf("\n");
    }
    return 0;
}
//*/




/*        13680K	282MS	C++	3699B

#include<iostream>  
#include<cstdio>  
#include<vector>  
#include<cstring>  
using namespace std;  
const int nMax =1000012;  
  
int  num[nMax];  
int sa[nMax], rank[nMax], height[nMax];  
int wa[nMax], wb[nMax], wv[nMax], wd[nMax];  
  
int cmp(int *r, int a, int b, int l){  
    return r[a] == r[b] && r[a+l] == r[b+l];  
}  
  
void da(int *r, int n, int m){          //  倍增算法 r为待匹配数组  n为总长度 m为字符范围  
    int i, j, p, *x = wa, *y = wb, *t;  
    for(i = 0; i < m; i ++) wd[i] = 0;  
    for(i = 0; i < n; i ++) wd[x[i]=r[i]] ++;  
    for(i = 1; i < m; i ++) wd[i] += wd[i-1];  
    for(i = n-1; i >= 0; i --) sa[-- wd[x[i]]] = i;  
    for(j = 1, p = 1; p < n; j *= 2, m = p){  
        for(p = 0, i = n-j; i < n; i ++) y[p ++] = i;  
        for(i = 0; i < n; i ++) if(sa[i] >= j) y[p ++] = sa[i] - j;  
        for(i = 0; i < n; i ++) wv[i] = x[y[i]];  
        for(i = 0; i < m; i ++) wd[i] = 0;  
        for(i = 0; i < n; i ++) wd[wv[i]] ++;  
        for(i = 1; i < m; i ++) wd[i] += wd[i-1];  
        for(i = n-1; i >= 0; i --) sa[-- wd[wv[i]]] = y[i];  
        for(t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i ++){  
            x[sa[i]] = cmp(y, sa[i-1], sa[i], j) ? p - 1: p ++;  
        }  
    }  
}  
  
void calHeight(int *r, int n){           //  求height数组。  
    int i, j, k = 0;  
    for(i = 1; i <= n; i ++) rank[sa[i]] = i;  
    for(i = 0; i < n; height[rank[i ++]] = k){  
        for(k ? k -- : 0, j = sa[rank[i]-1]; r[i+k] == r[j+k]; k ++);  
    }  
}  
  
int Log[nMax];  
int best[20][nMax];  
void initRMQ(int n) {//初始化RMQ  
    for(int i = 1; i <= n ; i ++) best[0][i] = height[i];  
    for(int i = 1; i <= Log[n] ; i ++) {  
        int limit = n - (1<<i) + 1;  
        for(int j = 1; j <= limit ; j ++) {  
            best[i][j] = min(best[i-1][j] , best[i-1][j+(1<<i>>1)]);  
        }  
    }  
}  
int lcp(int a,int b) {//询问a,b后缀的最长公共前缀  
    a = rank[a];    b = rank[b];  
    if(a > b) swap(a,b);  
    a ++;  
    int t = Log[b - a + 1];  
    return min(best[t][a] , best[t][b - (1<<t) + 1]);  
}  
  
char str[nMax];  
int ans[nMax];  
  
int main(){  
    int i,j,n,cas=0;  
    Log[0] = -1;  
    for(int i=1;i<=nMax;i++){  
        Log[i]=(i&(i-1))?Log[i-1]:Log[i-1] + 1 ;  
    }  
    while(scanf("%s",str)!=EOF&&str[0]!='#'){  
        n=strlen(str);  
        for(i=0;i<n;i++){  
            num[i]=str[i]-'a'+1;  
        }num[n]=0;  
        da(num, n + 1,30);  
        calHeight(num,n);  
        initRMQ(n);  
        int l,r,t,k,maxx=-1,a;  
        for(l=1;l<n;l++){     //枚举长度  
            for(i=0;i+l<n;i+=l){  
                k=lcp(i,i+l);  
                r=k/l+1;  
                t=l-k%l;  
                t=i-t;  
                if (t>=0&&k%l!=0){  
                    if(lcp(t,t+l)>=k) r++;  
                }  
                if(r>maxx){  
                    a=0;  
                    maxx=r;  
                    ans[a++]=l;  
                }  
                if(a==maxx){  
                    ans[a++]=l;  
                }  
            }  
        }  
        int start,b=0,c;  
        for(i=1;i<=n&&!b;i++){  //sa数组是保证字典序的神器啊 Orz  
            for(j=0;j<a;j++){  
                int tl=ans[j];  
                if(lcp(sa[i],sa[i]+tl)>=(maxx-1)*tl){  
                    start=sa[i];  
                    l=tl*maxx;  
                    b=1;  
                    break;  
                }  
            }  
        }  
        printf("Case %d: ",++cas);  
        for (int i=0;i<l;i++) printf("%c",str[start+ i]);  
        printf("\n");  
    }  
    return 0;  
}

//*/



/*        10632K	407MS	C++	4289B
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<map>
#include<vector>
#include<string>
#include<queue>
#include<stack>
using namespace std;
#define inf 0x7fffffff
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

using namespace std;


#define N 200001
struct suffixarr {
    int sa[N], rank[N], height[N];
    int wa[N], wb[N], wv[N], ws[N];
    int rmq[20][N];
    int n,m;
    int cmp(int *r, int a, int b, int l) {
        return r[a] == r[b] && r[a + l] == r[b + l];
    }
    void da(int *r) {
        int i, j, p, *x = wa, *y = wb, *t;
        for (i = 0; i < m; i++) ws[i] = 0;
        for (i = 0; i < n; i++) ws[x[i] = r[i]]++;
        for (i = 1; i < m; i++) ws[i] += ws[i - 1];
        for (i = n - 1; i >= 0; i--) sa[--ws[x[i]]] = i;
        for (j = 1, p = 1; p < n; j *= 2, m = p) {
            for (p = 0, i = n - j; i < n; i++) y[p++] = i;
            for (i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
            for (i = 0; i < n; i++) wv[i] = x[y[i]];
            for (i = 0; i < m; i++) ws[i] = 0;
            for (i = 0; i < n; i++) ws[wv[i]]++;
            for (i = 1; i < m; i++) ws[i] += ws[i - 1];
            for (i = n - 1; i >= 0; i--) sa[--ws[wv[i]]] = y[i];
            for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
                x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
        }
        return;
    }
    void calheight(int *r) {
        int i, j, k = 0;
        for (i = 0; i < n; i++)
            rank[sa[i]] = i;
        for (i = 0; i < n; i++)
            if (rank[i] == 0)
                height[rank[i]] = k = 0;
            else {
                for (k > 0 ? k-- : 0, j = sa[rank[i] - 1]; r[i + k] == r[j + k]; k++);
                height[rank[i]] = k;
            }
        return;
    }
    void rmq_init()
    {
        int i,j,t;
        for(i=0;i<n;i++)
            rmq[0][i]=height[i];
        for(t=i=1;t<n;i++,t<<=1)
        {
            for(j=0;j+t<n;j++)
                rmq[i][j]=min(rmq[i-1][j],rmq[i-1][j+t]);
            for(;j<n;j++)
                rmq[i][j]=rmq[i-1][j];
        }
        
    }
    int query(int i,int j)
    {
        if(i==j)
            return -1;
        if(i>j)
            swap(i,j);
        int m=(int)(log((double)j-i)/log(2.0));
        return min(rmq[m][i+1],rmq[m][j-(1<<m)+1]);
    }
} s;
char str[N];
int r[N];
int main() {
    int ti=0;
    while(cin>>str,strcmp(str,"#")!=0)
    {
        int len=strlen(str),i,j;
        for(i=0;i<len;i++)
            r[i]=str[i];
        r[i++]=0;
        s.n=i;s.m=130;
        s.da(r);
        s.calheight(r);
        s.rmq_init();
        int tst,st,l,maxl=0,t,k;
        for(i=1;i<=(s.n+1)/2;i++)
        {
            //cout<<i<<endl;
            for(j=i;j<s.n-1;j+=i)
            {
                len=s.query(s.rank[j-i],s.rank[j]);
                //cout<<j<<' '<<j-i<<' '<<len<<endl;
                if(len)
                {
                    tst=j-i;
                    
                    for(k=j-i-1;k>=0&&r[k]==r[k+i];k--)
                    {
                        len++;
                        if(len%i==0)
                            tst=k;
                        if(s.rank[tst]>s.rank[k])
                            tst=k;
                    }
                    l=len/i+1;
                    if(l>maxl||(l==maxl&&s.rank[st]>s.rank[tst]))
                    {
                        st=tst;
                        maxl=l;
                        t=i;
                    }
                }
                else
                {
                    if(maxl<1)
                    {
                        maxl=1;
                        st=s.rank[j-i]<s.rank[j]?j-i:j;
                        t=1;
                    }
                    else if(maxl==1)
                        if(min(s.rank[j-i],s.rank[j])<s.rank[st])
                            st=s.rank[j-i]<s.rank[j]?j-i:j;
                }
            }
        }
        printf("Case %d: ",++ti);
        for(i=0;i<maxl*t;i++)
            printf("%c",str[st+i]);
        printf("\n");
    }
    return 0;
}
//*/


/*         9984K	235MS	C++	4363B

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXD 100010
#define INF 0x3f3f3f3f
char b[MAXD];
int N, r[MAXD], sa[MAXD], rank[MAXD], height[MAXD], wa[MAXD], wb[MAXD], ws[MAXD], wv[MAXD];
int best[20][MAXD], mm[MAXD], len[MAXD], first[MAXD], P;
void init()
{
    int i;
    for(i = 0; b[i]; i ++)
        r[i] = b[i];
    r[N = i] = 0;
}
int cmp(int *p, int x, int y, int l)
{
    return p[x] == p[y] && p[x + l] == p[y + l];
}
int cmp1(const void *_p, const void *_q)
{
    int i, *p = (int *)_p, *q = (int *)_q;
    for(i = 0; i < len[*p] && i < len[*q]; i ++)
    {
        if(r[first[*p] + i] < r[first[*q] + i])
            return -1;
        else if(r[first[*p] + i] > r[first[*q] + i])
            return 1;
    }
    if(i == len[*p])
        return -1;
    return 1;
}
void da(int n, int m)
{
    int i, j, p, *x = wa, *y = wb, *t;
    memset(ws, 0, sizeof(ws[0]) * m);
    for(i = 0; i < n; i ++)
        ++ ws[x[i] = r[i]];
    for(i = 1; i < m; i ++)
        ws[i] += ws[i - 1];
    for(i = n - 1; i >= 0; i --)
        sa[-- ws[x[i]]] = i;
    for(j = p = 1; p < n; j *= 2, m = p)
    {
        for(p = 0, i = n - j; i < n; i ++)
            y[p ++] = i;
        for(i = 0; i < n; i ++)
            if(sa[i] >= j)
                y[p ++] = sa[i] - j;
        for(i = 0; i < n; i ++)
            wv[i] = x[y[i]];
        memset(ws, 0, sizeof(ws[0]) * m);
        for(i = 0; i < n; i ++)
            ++ ws[wv[i]];
        for(i = 1; i < m; i ++)
            ws[i] += ws[i - 1];
        for(i = n - 1; i >= 0; i --)
            sa[-- ws[wv[i]]] = y[i];
        for(t = x, x = y, y = t, x[sa[0]] = 0, i = p = 1; i < n; i ++)
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p ++;
    }
}
void calheight(int n)
{
    int i, j, k = 0;
    for(i = 1; i <= n; i ++)
        rank[sa[i]] = i;
    for(i = 0; i < n; height[rank[i ++]] = k)
        for(k ? -- k : 0, j = sa[rank[i] - 1]; r[i + k] == r[j + k]; k ++);
}
void initRMQ(int n)
{
    int i, j, x, y;
    for(mm[0] = -1, i = 1; i <= n; i ++)
        mm[i] = (i & (i - 1)) == 0 ? mm[i - 1] + 1 : mm[i - 1];
    for(i = 1; i <= n; i ++)
        best[0][i] = i;
    for(i = 1; i <= mm[n]; i ++)
        for(j = 1; j <= n - (1 << i) + 1; j ++)
        {
            x = best[i - 1][j];
            y = best[i - 1][j + (1 << (i - 1))];
            best[i][j] = height[x] < height[y] ? x : y;
        }
}
int askRMQ(int x, int y)
{
    int t = mm[y - x + 1];
    y = y - (1 << t) + 1;
    x = best[t][x];
    y = best[t][y];
    return height[x] < height[y] ? height[x] : height[y];
}
int calculate(int x, int y)
{
    int t;
    x = rank[x], y = rank[y];
    if(x > y)
        t = x, x = y, y = t;
    ++ x;
    return askRMQ(x, y);
}
void printresult(int max)
{
    int i, j, k;
    if(max == 1)
    {
        k = INF;
        for(i = 0; i < N; i ++)
            if(r[i] < k)
                k = r[i];
        printf("%c\n", k);
    }
    else
    {
        for(i = 0; i < P; i ++)
            ws[i] = i;
        qsort(ws, P, sizeof(ws[0]), cmp1);
        for(i = 0, k = ws[0]; i < len[k]; i ++)
            printf("%c", r[first[k] + i]);
        printf("\n");
    }
}
void solve()
{
    int i, j, k, p, max = 1, ans;
    da(N + 1, 128);
    calheight(N);
    initRMQ(N);
    for(i = 1; i < N; i ++)
        for(j = 0; j + i < N; j += i)
        {
            ans = calculate(j, j + i);
            k = j - (i - ans % i);
            ans = ans / i + 1;
            if(ans < max - 1 || (ans == max - 1 && calculate(k, k + i) < i))
                continue;
            for(k = ans == max - 1 ? k : j; j - k < i; k --)
            {
                ans = calculate(k, k + i);
                ans = ans / i + 1;
                if(ans < max)
                    break;
                if(ans > max)
                {
                    max = ans;
                    P = 0;
                }
                first[P] = k, len[P] = ans * i;
                ++ P;
            }
        }
    printresult(max);
}
int main()
{
    int t = 0;
    for(;;)
    {
        scanf("%s", b);
        if(b[0] == '#')
            break;
        printf("Case %d: ", ++ t);
        init();
        solve();
    }
    return 0;
}
//*/
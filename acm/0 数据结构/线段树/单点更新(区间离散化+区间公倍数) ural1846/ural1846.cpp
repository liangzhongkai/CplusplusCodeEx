/*
#include<iostream>

using namespace std;

#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1

const int N = 100005;
int gcd[N<<2];

int GCD(int a, int b){
	int c;
	if(a==0)   return b;
	while(b!=0){
		c = b; b = a % b; a = c;
	}
	return a;
}

void pushup(int rt){
	if(gcd[rt<<1] && gcd[rt<<1|1])
		gcd[rt] = GCD(gcd[rt<<1], gcd[rt<<1|1]);
	else if(gcd[rt<<1]==0 && gcd[rt<<1|1]){
		gcd[rt] = gcd[rt<<1|1];
	}
	else if(gcd[rt<<1|1]==0 && gcd[rt<<1]){
		gcd[rt] = gcd[rt<<1];
	}
}

void build(int l, int r, int rt){
	if(l==r){
		 gcd[rt] = 0;
	}
}


void update(int p, int a, int l, int r, int rt){
	if(l==r){
		gcd[rt] += a;
		return ;
	}
	int m = (l + r) >> 1;
	if(p<=m)
		update(p, a, lson);
	else
		update(p, a, rson);
	pushup(rt);
}

int query(int L, int R, int l, int r, int rt){
	if(l>=L && r<=R){
		
	}
}


int main()
{
	int n; 
	int cnt=1;

	scanf("%d", &n);
	while(n--){
		scanf("%c%d", &ch, &a);
		if(ch=='+'){
			update(cnt, a, 1, cnt, 1);
			printf("%d\n", gcd[1]);
		}
		else{
			
		}
	}

	return 0;
}

//*/



/*      0.171s	3 212 KB
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int N = 111111;
int tree[N<<2];
 
inline int gcd(int a,int b){
    if(!a || !b)    return a+b;
    for(int t;t=a%b;a=b,b=t);
    return b;
}
void update(int p,int v,int l,int r,int rt){
    if(l==r)
    {
        tree[rt]=v;
        return;
    }
    int m=(l+r)>>1;
    if(p<=m) update(p,v,lson);
    else    update(p,v,rson);
    tree[rt]=gcd(tree[rt<<1],tree[rt<<1|1]);
}

bool que[N];
int pos[N], vis[N];
vector<int> val;

int main(void)
{
    int n, i;
    while(scanf("%d",&n)==1)
    {
        val.clear();
        memset(tree,0,sizeof(tree));  // 初始化树状数组
        for(int i=0;i<n;i++)
        {
            char opt[9];
            int x;
            scanf("%s%d",opt,&x);
            que[i]=(opt[0]=='+');
            pos[i]=x;
            val.push_back(x);
        }
		// ******所有的操作离散化(sort+unique)******
        sort(val.begin(),val.end());
        val.erase(unique(val.begin(),val.end()),val.end()); 
		// *****************************************
		//for(i=0; i<val.size(); i++)
		//	printf("%d ", val[i]);
		//printf("\n");
        for(i=0;i<n;i++)
            pos[i]=lower_bound(val.begin(),val.end(),pos[i])-val.begin()+1;  // pos[]保存的是unique的val[]的下标
		//for(i=0; i<n; i++)
		///	printf("%d ", pos[i]);
		//printf("\n");
        memset(vis,0,sizeof(vis));
        int len=(int)val.size();
        int cnt=0;
        for(i=0;i<n;i++){
            if(que[i]){
                cnt++;
                vis[pos[i]]++;
                if(vis[pos[i]]==1)  update(pos[i],val[pos[i]-1],1,len,1);
            }
            else{
                cnt--;
                vis[pos[i]]--;
                if(vis[pos[i]]==0)  update(pos[i],0,1,len,1);
            }
            if(cnt)  printf("%d\n",tree[1]);
            else   puts("1");
        }
    }
    return 0;
}
//*/




//*   0.14	6 392 KB
#include<stdio.h>
#include<string.h>

#define HASH 1000003
#define MAXD 100010

int N, M, head[HASH], tree[4 * MAXD], next[MAXD], a[MAXD];
char op[5];

int hash(int x)   // 将0 ~ 10^9的整数
{
    return (((x << 1) ^ (x >> 1)) & 0x7fffffff) % HASH;
}

int gcd(int x, int y)
{
    return y == 0 ? x : gcd(y, x % y);
}

void init()
{
    memset(tree, 0, sizeof(tree));
    memset(head, -1, sizeof(head));
	// 为了让所有节点都存放到同一层里面的最小的2^n！
	// 而且同时也说明了前面“操作节点”的总数是比2^n小的！
	// 这种方式的线段树建造方法的好处就是你可以确切知道节点的位置。
    for(M = 1; M < N + 2; M <<= 1);
}
void update(int i)
{
    for(; i ^ 1; i >>= 1)
    {
        if(tree[i] < tree[i ^ 1])   // 等价于   判断i是左儿子还是右儿子   tree[奇/偶] < tree[偶/奇]
			tree[i >> 1] = gcd(tree[i ^ 1], tree[i]);
        else
			tree[i >> 1] = gcd(tree[i], tree[i ^ 1]);
    }
}
void in(int s)
{
    int h = hash(a[s]);
	// printf("%d\n", h);
    next[s] = head[h]; //  lastest下标的下一个下标
    head[h] = s;   //  是位置s的a[s]数对应的lastest下标
    tree[M + s] = a[s];
    update(M + s);
}
void out(int s)   
{
    int i, k, h = hash(a[s]);
    i = head[h];   // a[s]存放在最右边的位置下标
    if(a[i] == a[s])
    {
        head[h] = next[i];
        k = i;
    }
    else          // 处理冲突
    {
        for(; i != -1; i = next[i])
            if(a[next[i]] == a[s])  // 找到与a[s]相等的最右边的位置下标的前面一个
                break;
        k = next[i];
        next[i] = next[next[i]];    // 相当于链表里面的删除操作
    }
    tree[M + k] = 0;
    update(M + k);
}
void solve()
{
    int i, j;
    for(i = 0; i < N; i ++)
    {
        scanf("%s%d", op, &a[i]);
        if(op[0] == '+')
            in(i);
        else
            out(i);
        printf("***%d\n", tree[1] == 0 ? 1 : tree[1]);
    }
}
int main()
{
    while(scanf("%d", &N) == 1)
    {
        init();
        solve();
    }
    return 0;
}
//*/

/*
6
+ 8
+ 6
+ 8
+ 8
- 8
- 8
*/
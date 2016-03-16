//*         404K	344MS	C++	2615B
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<stack>

using namespace std;

const int N = 1010;
vector<int> adj[N], vec[N];
int  n,    
    belong[N], low[N], mark[N], cnt, num, instack[N],  // Tarjan所需
    in[N];

stack<int> st;
void Tarjan(int x)                         //  标记了双连通块，不单只是环
{
	int j;
	mark[x]=low[x]=++num;
	instack[x]=1;                          //  相当于mark[x]
	st.push(x);
	for(j=0; j<adj[x].size(); j++){  //  经过了这次循环，low[x]的值就已经确定了。
		int u=adj[x][j];
		if(mark[u]==-1){                    //  向前边，根据深度优先编号判断
			Tarjan(u);                     //  计算low[u]
			if(low[x]>low[u]) low[x]=low[u];
		}
		else if(instack[u] && low[x]>mark[u])    //  向后边
			low[x]=mark[u];
	}
	if(low[x]==mark[x]){   //  如果low[x]的值没有更改，证明儿子们都唔生性
		cnt++;
		do{
			j=st.top();
			st.pop();
			instack[j]=0;
			belong[j]=cnt;
		}while(j!=x);
	}
}

void dfs(int x){
	mark[x] = 1;
	int i, len = vec[x].size();
	for(i=0; i<len; i++){
		if(!mark[vec[x][i]]){
			 dfs(vec[x][i]);
			 break;
		}
	}
}

int main()
{
	//freopen("data.txt", "r", stdin);
	int i, j, len, a, b, nn,q;

	scanf("%d", &nn);
	while(nn--){
		for(i=1; i<=n; i++){
			adj[i].clear();
			vec[i].clear();
		}

		scanf("%d%d", &n, &q);
		for(i=1; i<=q; i++){
			scanf("%d%d", &a, &b);
			adj[a].push_back(b);
		}

		cnt = 0;
		num = 0;
		memset(instack, 0, sizeof(instack));
		memset(low, 0, sizeof(low));
		memset(mark, -1, sizeof(mark));
		for(i=1; i<=n; i++){
			if(mark[i]==-1){
				Tarjan(i);
			}
		}
		// debug
		//for(i=1; i<=n; i++){
		//	printf("%d ", belong[i]);
		//}
		//printf("\n");
		//if(cnt==1){
		//	printf("Yes\n");
		//	continue;
		//}
		memset(in, 0, sizeof(in));
		for(i=1; i<=n; i++){
			len = adj[i].size();
			for(j=0; j<len; j++){
				if(belong[i]!=belong[adj[i][j]]){
					vec[belong[i]].push_back(belong[adj[i][j]]);
					in[belong[adj[i][j]]]++;
				}
			}
		}
		// debug
		//for(i=1; i<=cnt; i++){
		//	for(j=0; j<vec[i].size(); j++)
		//		printf("%d %d\n", i, vec[i][j]);
		//}
		// debug
		//for(i=1; i<=cnt; i++){
		//	printf("%d ", in[i]);
		//}
		//printf("\n");
		int cur = 0;
		int count = 0;
		int key = 0;
		for(i=1; i<=cnt; i++){
			if(in[i]==0){
				cur = i;
				count++;
			}
		}
		if(count>1){
			printf("No\n");
			continue;
		}
		else{
			memset(mark, 0, sizeof(mark));
			dfs(cur);
			for(i=1; i<=cnt; i++){
				if(mark[i]!=1){
					printf("No\n");
					key = 1;
					break;
				}
			}
		}
		if(key==0)
			printf("Yes\n");
	}

	return 0;
}
//*/


//  364K	329MS	C++	1984B
// 分析：
// 首先环内的肯定是满足的，所以先缩点。
// 然后剩下一棵树。
//那么从根节点（即缩点后没有入度的点）出发，假设一路走下去是一条链的话（即树没有分叉），而且所有的点都能走到，那么就满足性质。

//证明：

//1、如果有分叉的话，分叉两边的点不能到达对方。
//2、入度为0的点不可能没有，因为已经缩点，不存在环了。
//3、入度为0的如果>1，那么两个入度为0的点不能到达对方。

// 所以，结论就是，只有所有收缩后的点成一长链，才能满足性质。
/*
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define N 5001
#define E 20001

struct gtp{
	int x,y,next;
}g[E];

int n,e,ls[N],f[N],dep[N],color[N],list[N];

void init(){
    scanf("%d%d",&n,&e);
    memset(ls,0,sizeof(ls));
    for (int i=1;i<=e;i++){
        scanf("%d%d",&g[i].x,&g[i].y);   // g[i]是第i条边
        g[i].next=ls[g[i].x];            // ls[i]是i点为起点与第一个儿子终点的边号
        ls[g[i].x]=i;
    }    
}    

int gf(int k){
    if (f[k]==k) return k;
    f[k]=gf(f[k]);
    return f[k];
}    
// 将所有环的f[]值指向最小深度。
void dfs(int k){   
    for (int t=ls[k];t!=0;t=g[t].next)    // 遍历所有儿子
		if (dep[g[t].y]==0){              // 向前边
			dep[g[t].y]=dep[k]+1;
			dfs(g[t].y);  
			if (dep[gf(g[t].y)]<dep[gf(k)]) f[k]=f[g[t].y];  // 
		}
		else if (color[gf(g[t].y)]==0 && dep[gf(g[t].y)]<dep[gf(k)])  
			f[k]=f[g[t].y];
   color[k]=1;   // 当所有儿子都为1时，它就为1，为1之后就是不会再修改它的f[]值，为剪枝用！
}
// 将各个双连通分量所点。
void tarjan(){
	int i;
    for (i=1;i<=n;i++) f[i]=i;   //  并查集
    memset(dep,0,sizeof(dep));
    memset(color,0,sizeof(color));
    for (i=1;i<=n;i++)
      if (dep[i]==0){
          dep[i]=1;
          dfs(i);
      }

    for (i=1;i<=n;i++) gf(i);
}    

void dfs2(int k){
	// list[i]表示深度为i的祖先结点号，只能表示一个。
	// 如果有两个相同深度的双连通块，那么肯定有一个块的没有映射到list[]里面
    list[dep[k]] = f[k];  
    for (int t=ls[k]; t!=0; t=g[t].next)
      if(dep[g[t].y]==0) {
          dep[g[t].y]=dep[k];
          if (f[g[t].y]!=f[k]) dep[g[t].y]++;
          dfs2(g[t].y);
      }    
}

bool flag(){
    int r[N];
	int i;
    memset(r,0,sizeof(r));
    for (i=1;i<=n;i++)
      for (int t=ls[i];t!=0;t=g[t].next)
        if (f[g[t].x]!=f[g[t].y]) r[f[g[t].y]]++;  // 计算度数

    memset(dep,0,sizeof(dep));
    memset(list,0,sizeof(list));
    for (i=1;i<=n;i++)
		if (f[i]==i && r[i]==0){  // 从入度为0的块的祖先入手
          dep[i]=1;
          dfs2(i);
          break;     // 为了检测有没有分叉！
		}

    for (i=1;i<=n;i++)    
		// 如果有独立块、或者相同深度的块，即不能构成  弱连通图
        if (dep[i]==0 || list[dep[i]]!=f[i]) return false;
    return true;
}

int main(){
    int TC;
    scanf("%d",&TC);
    for (int i=0;i<TC;i++){
        init();
        tarjan();
        if (flag()) printf("Yes\n");
               else printf("No\n");
    }    
	return 0;
}
//*/











//     （Tarjan算法）
/*     316K	329MS	C++	  1917B
//先用强连通缩点来化简图，然后在图上做拓扑排序，如果排序过程中，出现1个以上的点入度同时为0时，那么就不满足条件。
// 对比上面代码，它有全新的标记双连通块的方法，和
#include<cstdio>
#include<cstring>
#include<stack>
#include<iostream>

using namespace std;

const int N = 1001;

struct Edge
{
	int s,e,next;
}edge1[6*N], edge2[6*N];

int n,m,e_num1,e_num2,vis_num,cnt;
int head[N],instack[N],low[N],tim[N],belong[N],de[N];

void AddEdge(int a,int b,Edge edge[],int &e_num)
{
	edge[e_num].s=a;
	edge[e_num].e=b; 
	edge[e_num].next=head[a]; 
	head[a]=e_num++;
}

void getmap()
{
	int a,b;
	scanf("%d%d",&n,&m);
	e_num1=0;
	memset(head,-1,sizeof(head));
	while( m-- )
	{
		scanf("%d%d",&a,&b);
		AddEdge(a,b,edge1,e_num1);
	}
}

stack <int> st;
void tarjan(int x)                         //  标记了双连通块，不单只是环
{
	int j;
	tim[x]=low[x]=++vis_num;
	instack[x]=1;                          //  相当于mark[x]
	st.push(x);
	for(j=head[x];j!=-1;j=edge1[j].next){  //  经过了这次循环，low[x]的值就已经确定了。
		int u=edge1[j].e;
		if(tim[u]==-1){                    //  向前边，根据深度优先编号判断
			tarjan(u);                     //  计算low[u]
			if(low[x]>low[u]) low[x]=low[u];
		}
		else if(instack[u] && low[x]>tim[u])//  向后边
			low[x]=tim[u];
	}
	if(low[x]==tim[x]){                    //  如果low[x]的值没有更改，证明儿子们都唔生性
		cnt++;
		do{
			j=st.top();
			st.pop();
			instack[j]=0;
			belong[j]=cnt;
		}while(j!=x);
	}
}

int topo()
{
	int i,cur,u,count,num;
	count=0;
	for(i=1;i<=cnt;i++){   // cnt是双连通块个数
		if(de[i]==0){
			cur=i;count++;
		}
	}
	if(count>1)return 0;
	num=cnt;
	while(num--){
		count=0;
		for(i=head[cur];i!=-1;i=edge2[i].next){
			u=edge2[i].e;
			de[u]--;
			if(de[u]==0){
				count++;cur=u;   //  if count no less than 2, it prove to be that there is 分叉。
			}
		}
		if(count>1)return 0;
	}
	return 1;
}

void solve(){
	int i;
	cnt=vis_num=0;
	memset(instack,0,sizeof(instack));
	memset(low,0,sizeof(low));
	memset(tim,-1,sizeof(tim));

	for(i=1;i<=n;i++){
		if(tim[i]==-1)tarjan(i);
	}

	for(i=1;i<=n;i++){
		cout << belong[i] << " ";
	}
	cout << endl;
	
	e_num2=0;
	memset(head,-1,sizeof(head));
	memset(de,0,sizeof(de));
	for(i=0;i<e_num1;i++)
	{
		int j=edge1[i].s;
		int k=edge1[i].e;
		if(belong[j]!=belong[k])   //  不在同一个双连通块里面，
		{
			AddEdge(belong[j],belong[k],edge2,e_num2);   //  缩点，构造新图
			de[belong[k]]++;       //  计算入度
		}
	}
	topo()==1?puts("Yes"):puts("No");
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		getmap();
		solve();
	}
	return 0;
}

//*/






//        （Kosaraju算法）
/*         1276K	344MS	C++	1985B
#include<iostream>
using namespace std;

struct node{
    int v;
    node *next;
};

node pp[6005],qq[6005];
node *dd[1005],*rd[1005];
bool mark[1005];
bool map[1005][1005];
int cal[1005];
int ret[1005];
int n,m,ti;

void init()
{
    memset(mark,false,sizeof(mark));
    memset(cal,0,sizeof(cal));
    memset(dd,0,sizeof(dd));
    memset(rd,0,sizeof(rd));
    memset(ret,0,sizeof(ret));
    memset(map,false,sizeof(map));
}

void input()
{
    int u,v,i;
    scanf("%d%d",&n,&m);
    for(i=0;i<m;i++){
        scanf("%d%d",&u,&v);
        pp[i].v=v;
        pp[i].next=dd[u];
        dd[u]=&pp[i];
        
        qq[i].v=u;
        qq[i].next=rd[v];
        rd[v]=&qq[i];
    }
}        

void dfs(int k)
{
    mark[k]=true;
    node *p=dd[k];
    while(p){
        if(!mark[p->v])
            dfs(p->v);
        p=p->next;
    }
    cal[++ti]=k;
}

void rdfs(int k){
    ret[k]=ti;
    node *p=rd[k];
    while(p){
        if(!ret[p->v]) 
            rdfs(p->v);
        else if(ti!=ret[p->v]){
            map[ti][ret[p->v]]=true;
        }
        p=p->next;
    }
}

int dfsr(int k){
    int ans=0;
    for(int i=1;i<=ti;i++){
        if(map[k][i]){
            if(!cal[i])
                dfsr(i);
            ans=max(ans,cal[i]);
        }
    }
    cal[k]=ans+1;
    return cal[k];
}

int main()
{
    int t,i;
    scanf("%d",&t);
    while(t--){
        init();
        input();
        ti=0;
        for(i=1;i<=n;i++)
            if(!mark[i])
                dfs(i);
        for(ti=0,i=n;i>0;i--){
            if(!ret[cal[i]]){
                ti++;
                rdfs(cal[i]);
            }
        }
        int ans=0;
        memset(cal,0,sizeof(cal));
        for(i=1;i<=ti;i++){
            if(!cal[i])
                dfsr(i);
            ans=max(ans,cal[i]);
        }
        if(ans==ti) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}

//*/



// ( 5 )        352K	313MS	C++	 4053B
/*
// 判定是否是弱连通图.

// 先求强连通分量, 缩点, 缩点后如果满足要求则是竞赛图, 竞赛图有性质必定存在哈密尔顿路, 所以再树形dp, 求最长链, 状态转移:

// len[u]=max{1, len[v]+1}, u是v的父亲.

// 等于分量数即yes, 注意优化: 入度为0的只能有一个, 并且边数必须不小于分量数-1.

#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1001, M = 6000;

template<class T, int SIZE>
class Vec
{
public:
    Vec() : end(a) {}
    inline T * Beg() { return a; }
    inline T * End() { return end; }
    inline T & Push(const T &t) { *end = t; return *(end++); }
    inline T & Back() { return *(end - 1); }
    inline void Pop() { --end; }
    inline void Clr() { end = a; }
    inline bool Ept() { return a == end; }
private:
    T a[SIZE];
    T *end;
};

struct E
{
    int v;
    E *next;
    E(int vin = 0, E *nin = NULL) : v(vin), next(nin) {}
};

#define CLR(a) (memset(a, 0, sizeof(a)))

template<int VSIZE, int ESIZE>
class AList
{
public:
    inline void Clr() { CLR(e); buf.Clr(); }
    inline void Add(int u, int v) { e[u] = &buf.Push(E(v, e[u])); }
    // Add Unique
    inline bool AddUni(int u, int v) {
        for (E *p = e[u]; p; p = p->next)
            if (p->v == v) return true;
        Add(u, v);
        return false;
    }
    inline void Del(int u, int v) {
        if (!e[u]) return;
        if (e[u]->_v == v) {
            e[u] = e[u]->next;
            return;
        }
        for (E *q = e[u], *p = q->next; p; q = p, p = p->next)
            if (p->v == v)  q->next = p->next;
    }
    inline E * operator [] (int i) { return e[i]; }
private:
    Vec<E, ESIZE> buf;
    E* e[VSIZE];
};


const int VSIZE = N, ESIZE = M;
const int WHITE = -1, GRAY = -2, IDBEG = 0;

AList<VSIZE, ESIZE> _ol, _rl, *_now = NULL;

int _id[VSIZE] = {0}, _t[VSIZE] = {0}, _tend, _iend;

void scc_dfs(int i) {
    _id[i] = GRAY;
    for (E *p = (*_now)[i]; p; p = p->next) {
        if (WHITE == _id[p->v]) scc_dfs(p->v);
    }
    _id[i] = _iend;
    if (!(_tend < 0)) _t[_tend++] = i;
}

void scc_init() { fill_n(_id, VSIZE, WHITE); CLR(_t); }

void SCC(int n) {
    scc_init();
    int i;
    _tend = 0, _iend = IDBEG, _now = &_ol;
    for (i = 0; i < n; ++i) {
        if (WHITE == _id[i]) scc_dfs(i);
    }
    _now = &_rl;
    fill_n(_id, VSIZE, WHITE);
    for (i = _tend - 1, _tend = -1; i > -1; --i) {
        if (WHITE == _id[_t[i]]) {
            scc_dfs(_t[i]);
            ++_iend;
        }
    }
}

AList<N, M> _cl;
int _len[N], _in[N];

void Init() {
    _ol.Clr(), _rl.Clr(), _cl.Clr();
    CLR(_in);
}

void dfs_init() {
    CLR(_len);
}

int dfs_visit(int u) {
    if (_len[u]) return _len[u];
    int res = 1;
    for (E *p = _cl[u]; p; p=p->next) {
        // not "res = max(res, dfs_visit(p->v));"
        res = max(res, dfs_visit(p->v) + 1);
    }
    return _len[u] = res;
}

int DFS() {
    dfs_init();
    int i, res = 1;
    for (i = IDBEG; i < _iend; ++i) {
        res = max(res, dfs_visit(i));
    }
    return res;
}

int main() {
    int t, n, m, u, v, i;
    scanf("%d", &t);
    while (t--) {
        Init();
        scanf("%d%d", &n, &m);
        for (i = 0; i < m; ++i) {
            scanf("%d%d", &u, &v);
            --u, --v;
            _ol.Add(u, v);
            _rl.Add(v, u);
        }
        SCC(n);
        int cnt = 0, idn = _iend - IDBEG;
        for (u = 0; u < n; ++u) {
            for (E *p = _ol[u]; p; p = p->next) {
                v = p->v;
                if (_id[u] != _id[v]) {
                    if (!_cl.AddUni(_id[u], _id[v])) {
                        ++_in[_id[v]];
                        ++cnt;
                    }
                }
            }
        }
        if (!(cnt < idn - 1)
            && count(_in + IDBEG, _in + _iend, 0) < 2
            && DFS() == idn) {
            puts("Yes");
        }
        else {
            puts("No");
        }
    }
    return 0;
}


//*/
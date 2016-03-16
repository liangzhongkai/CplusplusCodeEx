//*      0MS	452K	1909 B	C++
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int INF = 99999999;
const int N = 210;
int n, m;
int dp[N][N];
char name[N][101];
int c[N];
bool vis[N];
int size;
int father[N];
int s[N];

struct node{
	int v;
	node *next;
}*head[N], coutry[N];
int p;

void init(){
	int i;
	size = 1;
	p = 0;
	memset(head, NULL, sizeof(head));
	memset(c, 0, sizeof(c));
	for(i=0; i<N; i++){
		father[i] = i;
		s[i] = 1;
	}
}

int find(char *ch){
	int i;
	for(i=1; i<size; i++){
		if(strcmp(name[i], ch)==0)
			return i;
	}
	if(i==size){
		strcpy(name[i], ch);
		size++;
	}
	return i;
}

void addedge(int u, int v){
	coutry[p].v = v;
	coutry[p].next = head[u];
	head[u] = &coutry[p++];
}

void dfs(int u){
	int i, j;
	node *p = head[u];
	
	for(i=1; i<=n; i++)
		dp[u][i] = INF;
	dp[u][0] = 0;
	dp[u][s[u]] = c[u];

	while(p!=NULL){
		int v = p->v;
		dfs(v);
		for(i=s[u]; i>0; i--){
			for(j=1; j<=s[v]; j++){
				if(dp[u][i]>dp[u][i-j]+dp[v][j])   // 本身就约束了 dp[u][i-j] != INF  和  dp[v][j] != INF
					dp[u][i] = dp[u][i-j] + dp[v][j];
			}
		}
		p = p->next;
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	char ch[101];
	char tmp;
	int i;
	int id1, id2;
	while(gets(ch)){
		if(ch[0]=='#')   break;
		sscanf(ch, "%d %d", &n, &m);
		init();
		for(i=0; i<n; i++){
			scanf("%s", ch);
			id1 = find(ch);
			scanf("%d", &c[id1]);
			tmp = getchar();
			while(tmp==' '){
				scanf("%s", ch);
				id2 = find(ch);
				addedge(id1, id2);

				father[id2] = id1;
				int t = id1;
				while(t!=father[t]){
					s[t] += s[id2];
					t = father[t];
				}
				s[t] += s[id2];

				tmp = getchar();
			}
		}
		for(i=1; i<=n; i++){
			if(father[i]==i)
				addedge(0, i);
		}
		c[0] = INF;
		s[0] = n + 1;

		dfs(0);
		int ans = INF;
		for(i=m; i<=n; i++){
             if(dp[0][i]<ans)
				  ans = dp[0][i];  
		}
		printf("%d\n", ans);
	}	

	return 0;
}
//*/



/*      62MS	584K	1841 B	C++

#include <iostream>
#include <sstream>
#include <map>
using namespace std;

const int maxn=310;
const int maxm=510;
const int maxl=21000;
const int maxx=1<<29;
int e[maxn],next[maxm],v[maxm];
int que[maxn],fa[maxn],id[maxn],d[maxn];
int f[maxn][maxn],g[maxn],ls[maxn];
map<string,int>list;
string sa,sb;
char s[maxl];
istringstream st;
int size,num;

int min(int a,int b){return a<b?a:b;}

void addedge(int a,int b){
	size++;
	next[size]=e[a];
	e[a]=size;
	v[size]=b;
}

int getnum(string s){
	if (list.find(s)==list.end()){
		num++;
		list[s]=num;
	}
	return list[s];
}

int main(){
	int n,m,l,r,i,j,k,a,b,ans;
	while(gets(s)){
		if (s[0]=='#') break;
		st.clear();
		st.str(s);
		st>>n>>m;
		size=num=0;
		list.clear();
		memset(e,-1,sizeof(e));
		memset(d,0,sizeof(d));
		memset(id,0,sizeof(id));
		for (i=1;i<=n;i++){
			gets(s);
			st.clear();
			st.str(s);
			st>>sa;
			a=getnum(sa);
			st>>g[a];
			while(st>>sb){
				d[a]++;
				b=getnum(sb);
				addedge(a,b);
				id[b]++;
			}
		}
		for (i=1;i<=n;i++)
			if (id[i]==0) {
				id[i]++;
				addedge(n+1,i);
				d[n+1]++;
			}
		n++;
		g[n]=maxx;
		memset(fa,-1,sizeof(fa));
		l=0; r=1; que[1]=n; fa[n]=0;
		while(l<r){
			i=que[++l];
			for (j=e[i];j>0;j=next[j])
				if (fa[v[j]]<0) {
					que[++r]=v[j];
					fa[v[j]]=i;
				}
		}
		memset(ls,0,sizeof(ls));
		for (i=1;i<=n;i++){
			f[i][0]=0;
			for (j=1;j<=n;j++)	f[i][j]=maxx;
		}
		for (i=n;i>=2;i--){
			b=que[i]; a=fa[b];
			ls[b]++;
			f[b][ls[b]]=min(f[b][ls[b]],g[b]);
			for (j=n;j>=0;j--)
				for (k=j-1;k>=0;k--)
					if (f[a][k]<maxx && f[b][j-k]<maxx)
						f[a][j]=min(f[a][j],f[a][k]+f[b][j-k]);
			ls[a]+=ls[b];
		}
		ans=f[n][m];
		for (i=m+1;i<n;i++)
			ans=min(ans,f[n][i]);
		cout<<ans<<endl;
	}
	return 0;
}

//*/




/*   0MS	456K	1885 B	C++
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <map>
using namespace std;

const int maxn=205,oo=99999999;
vector<int> g[maxn];
int dp[maxn][maxn],v[maxn],num[maxn];
bool fa[maxn];
int n,m,id;

int dfs(int x)
{
    num[x]=1;
    int i,j,k,y;
    for (k=0;k<g[x].size();k++)
    {
        y=g[x][k];
        num[x]+=dfs(y);
    }
	printf("%d\n", num[x]);
    for (k=0;k<=n;k++) 
		dp[x][k]=oo;
    dp[x][0]=0;
    dp[x][num[x]]=v[x];
    for (k=0; k<g[x].size(); k++)
    {
        y=g[x][k];
        for (i=num[x];i>=0;i--)
            for (j=0; j<=num[y]; j++)
                if (dp[x][i-j]+dp[y][j]<dp[x][i])
					dp[x][i] = dp[x][i-j]+dp[y][j];
    }
    return num[x];
}
int main()
{
    freopen("in.txt","r",stdin);
    char str[1000];
    int i,j,ans,now;
    while (gets(str))
    {
		if (str[0]=='#') break;
		sscanf(str,"%d%d",&n,&m);

		map<string,int> wmap;
		for (i=0;i<=n;i++)
			g[i].clear();
		memset(fa,0,sizeof(fa));
		id=0;

		for (i=1;i<=n;i++)
		{
			scanf("%s",str);
			if (wmap.find(str)==wmap.end()) 
				wmap[str]=++id;
			now=wmap[str];
			scanf("%d",&v[now]);
			while (getchar()!='\n')
			{
				scanf("%s",str);
				if (wmap.find(str)==wmap.end())
					wmap[str]=++id;
				g[now].push_back(wmap[str]);
				fa[wmap[str]]=true;
			}
		}
		v[0]=oo;
		for (i=1;i<=n;i++)
		{
			printf("%d\n", v[i]);
			if (fa[i]) continue;
			g[0].push_back(i);
		}
		dfs(0);
		ans=oo;
		for (i=m;i<=n;i++)
			if (dp[0][i]<ans) ans=dp[0][i];
		printf("%d\n",ans);
    }
    return 0;
}
//*/
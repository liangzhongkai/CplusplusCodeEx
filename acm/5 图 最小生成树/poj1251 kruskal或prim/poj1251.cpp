/*
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

ifstream  fin("data.txt");
#define  cin  fin 

int mp[30][30];

int main()
{
	int n, i, a, b;
	char ch;

	while(cin >> n && n!=0){
		memset(mp, 1<<6, sizeof(mp));

		cin >> ch >> a;
		for(i=1; i<=a; i++){
			cin >> ch >> b;
			mp[i][ch-64] = b;
			mp[ch-64][i] = b;
		}

		for(i=1; i<=n; i++){
			dist[i] = mp[1][i];
		}

		for(i=1; i<=n; i++){
			for()
		}
	}

	return 0;
}

//*/


/*    124K	0MS	C++	1498B  kruskal
#include<iostream>
#include<fstream>
#include<algorithm>
#include<string.h>
using namespace std;

int parent[26];
int n;//vertex num
int edge_num;
struct Edge
{
	int v1;
	int v2;
	int weight;
}edges[100];
int cmp(const void *edge1,const void *edge2)
{
	Edge *e1=(Edge *)edge1;
	Edge *e2=(Edge *)edge2;
	return e1->weight-e2->weight;
}
int find(int v)
{
	while(parent[v]>=0)
		v=parent[v];
	return v;
}
void Union(int r1,int r2)   
{
	if(parent[r1]<=parent[r2])
	{
		parent[r1]+=parent[r2];
		parent[r2]=r1;
	}
	else
	{
		parent[r2]+=parent[r1];
		parent[r1]=r2;
	}
}

int main()
{
	//freopen("input.txt","r",stdin);
	while(scanf("%d\n",&n)!=EOF&&n!=0)
	{
		edge_num=0;
		memset(parent,-1,sizeof(int)*n);
		char ch;
		int v1,v2;
		int k;
		for(int t=0;t<n-1;t++)
		{
			scanf("%c %d",&ch,&k);
			v1=ch-'A';
			for(int i=0;i<k;i++)
			{
				int w;
				scanf(" %c %d",&ch,&w);
				edges[edge_num].v1=v1;
				edges[edge_num].v2=ch-'A';
				edges[edge_num++].weight=w;
			}
			scanf("\n");
		}
		qsort(edges,edge_num,sizeof(Edge),cmp);
		int output=0;
		int count=0;
		for(int i=0;i<edge_num;i++)
		{
			if(count==n-1) //successed
				break;
			int r1=find(edges[i].v1);
			int r2=find(edges[i].v2);
			if(r1==r2)
				continue;
			Union(r1,r2);
			output+=edges[i].weight;
			count++;

		}
		//for(int i=0;i<edge_num;i++)
		//{
		//	cout<<edges[i].v1<<" "<<edges[i].v2<<" "<<edges[i].weight<<endl;
		//}
	        printf("%d\n",output);
	}
	return 0;
}
//*/


/*    164K	0MS	C++	1390B    kruskal
#include<stdio.h>
 #include<iostream>
 #include<algorithm>
  using namespace std;
 struct line
 {
     int begin;
     int end;
     int lenth;
 };
 line num[100];
 int amount,sumofline;
 int i,j;
 int father[100];
 int minlen;
 int find(int k)
 {
     return father[k]==k?k:father[k]=find(father[k]);
 }
 int cmp(line a,line b)
 {
     return a.lenth<b.lenth?1:0;
 }
 void ini()
 {
     sumofline=0;
     char start,tmpend;
     int tmpline,tmplen;
     int a,b;
     for(i=0;i<amount;i++) father[i]=i;
     for(i=0;i<amount-1;i++)
     {
         cin>>start;
         scanf("%d",&tmpline);
         a=start-'A';
         for(j=0;j<tmpline;j++)
         {
             cin>>tmpend;
             scanf("%d",&tmplen);
             b=tmpend-'A';
             num[sumofline].begin=a;
             num[sumofline].end=b;
             num[sumofline++].lenth=tmplen;
         }
     }
     sort(num,num+sumofline,cmp);
 }
 int kruskal()
 {
     minlen=0;
     int a,b;
     for(i=0;i<sumofline;i++)
     {
         a=find(num[i].begin),b=find(num[i].end);
         if(a!=b)
         {
             father[a]=b;
             minlen+=num[i].lenth;
         }
     }
     return minlen;
 }
 int main()
 {
     while(scanf("%d",&amount)==1&&amount)
     {
         ini();
         printf("%d\n",kruskal());
     }
     return 0;
 }
 //*/



/*   208K	0MS	C++	1434B    prim
#include <iostream>
#define MAX 27
#define MAXCOST 101
using namespace std;

int vertices[MAX],lowcost[MAX],minv,totalcost;
int edges[MAX][MAX];
bool visited[MAX];

int prim(int vertex_num,int v)
{
 int i,j;
    totalcost=0;
    visited[v]=true;
    for(i=0;i<vertex_num;i++)
        lowcost[i]=edges[v][i];
    for(i=1;i<vertex_num;i++)
    {
        minv=MAXCOST;

        for(j=0;j<vertex_num;j++)
            if(!visited[j]&&lowcost[j]<minv)//lowcost[j]是从顶点v到顶点j的权值
            {
                minv=lowcost[j];
                v=j;
            }
        visited[v]=true;
        totalcost+=minv;
        for(int j=0;j<vertex_num;j++)
            if(!visited[j]&&edges[v][j]<lowcost[j])
                lowcost[j]=edges[v][j];
    }
    return totalcost;
}

int main()
{
 int i;
    int num,degree,cost;
    char vertex;
    while(cin>>num && num)
    {
        for(i=0;i<num;i++) vertices[i]=i;
        for(int i=0;i<num;i++)
            for(int j=0;j<num;j++)
                edges[i][j]=MAXCOST;
        for(i=0;i<num;i++) visited[i]=false;

        for(i=0;i<num-1;i++)
        {
            cin>>vertex>>degree;
            for(int j=0;j<degree;j++)
            {
                cin>>vertex>>cost;
                edges[i][vertex-'A']=cost;
                edges[vertex-'A'][i]=cost;
            }
        }
        cout<<prim(num,0)<<endl;
    }
    return 0;
}
 //*/


/*   216K	0MS	C++	1305B   kruskal
#include<iostream>
#include<algorithm>
 
using namespace std;
 
#define MAX 26
 
// 定义边(x,y)，权为w 
typedef struct
{
	int x, y;
	int w;
}edge;
 
edge e[MAX * MAX];


// rank[x]表示x的秩 
int rank[MAX];
// father[x]表示x的父节点
int father[MAX];
int sum;
 
// 比较函数，按权值非降序排序
bool cmp(const edge a, const edge b)
{
     return a.w < b.w;
}
 
// 初始化集合
void Make_Set(int x)
{
	father[x] = x;
	rank[x] = 0;
}
// 查找x元素所在的集合,回溯时压缩路径 
int Find_Set(int x)
{
	if (x != father[x])
	{
		father[x] = Find_Set(father[x]);
	}
	return father[x];
}
// 合并x,y所在的集合
void Union(int x, int y, int w)
{
 
	if (x == y) return;
	if (rank[x] > rank[y])
	{
		father[y] = x;
	}
	else
	{
		if (rank[x] == rank[y])
		{
			rank[y]++;
		}
		father[x] = y;
	}
	sum += w;
}
 
int main()
{
	int i, j, k, m, n, t;
	char ch;
	while(cin >> m && m != 0)
	{
		k = 0;
		for (i = 0; i < m; i++) Make_Set(i);
		for (i = 0; i < m - 1; i++)
		{
			cin >> ch >> n;
			for (j = 0; j < n; j++)
			{
				cin >> ch >> e[k].w;
				e[k].x = i;
				e[k].y = ch - 'A';
				k++;
			}
		}
 
		sort(e, e + k, cmp);
 
		sum = 0;
 
		for (i = 0; i < k; i++)
		{
			Union(Find_Set(e[i].x), Find_Set(e[i].y), e[i].w);
		}
 
		cout << sum << endl;
	}
	return 0;
}
///*/



/*         208K	0MS	C++	1164B
#include <iostream>

#define MAXN 28
#define inf 10000
typedef int elem_t;

using namespace std;

elem_t prim(int n,elem_t mat[MAXN][MAXN],int* pre){
    elem_t min[MAXN],ret=0;

    int v[MAXN],i,j,k;
    for (i=0;i<n;i++)
        min[i]=inf,  v[i]=0,  pre[i]=-1;

    for (min[j=0]=0;j<n;j++){
        for (k=-1,i=0;i<n;i++)
            if (!v[i]&&(k==-1||min[i]<min[k]))
                k=i;
            for (v[k]=1,ret+=min[k],i=0;i<n;i++)
                if (!v[i]&&mat[k][i]<min[i])    // 如果是dijkstra，这里的更新要考虑  min[k]+mat[k][i] < min[i]
                    min[i]=mat[pre[i]=k][i];
    }
    return ret;
}

int main(){
    int n,m,i,j,result,q;
    int pre[MAXN];
    int distance[MAXN][MAXN];
    char s,e;
    while(cin>>n,n!=0){
        for (i = 0;i < n;i++)
            for (j = 0;j < n;j++)
                {
                    distance[i][j] = inf;
                }

        for(i = 0;i < n-1;i++){
            cin>>s>>m;
            for(j = 0;j < m;j++){
                cin>>e>>q;
                distance[s -'A'][e -'A'] = distance[e -'A'][s -'A'] = q;
            }
        }

        result  = prim(n,distance,pre);
        cout << result<<endl;
    }
    return 0;
}///*/
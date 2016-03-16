/*
#include <iostream>
using namespace std;

#define maxn 1002
bool s[maxn];
int n=1000;
struct edge{
int to;
int len;
edge* next;
};
int now;
int root;
edge * list[maxn];
bool visit[maxn];
int dpth;
int dfn[maxn];
int low[maxn];

void dfs(int i)
{
	// cout<<"come into "<<i<<endl;
	int sum=0;
	low[i]=dfn[i]=++dpth;
	for(edge *e=list[i];e;e=e->next){
    int j=e->to;
    ++sum;
    if(!dfn[j]){
      dfs(j);
      if(low[i]>low[j])low[i]=low[j];
      if((i==root&&sum>=2)||(i!=root&&dfn[i]<=low[j]))s[i]=1;
    }else {
      if(j!=i){
    if(dfn[j]<low[i])low[i]=dfn[j];
      }
    }   
}
}
void ff(int i){
for(edge * e = list[i];e;e=e->next){
    if(e->to!=now&&!visit[e->to]){
      /// cout<<e->to<<endl;
      visit[e->to]=1;
      ff(e->to);
    }
   
}
}



int main()
{
int bcnt=0;
while(1){
    ++bcnt;
dpth=0;
memset(list,NULL,sizeof(list));
memset(dfn,0,sizeof(dfn));
memset(low,0,sizeof(low));
int j,k;
scanf("%d",&j);
if(j==0)return 0;
scanf("%d",&k);
   edge * tem= new edge;
      tem->to = k;
      tem->next=list[j];   
      list[j]=tem;
      edge *temm= new edge;
      temm->to = j;
      temm->next=list[k];
      list[k]=temm;
memset(s,0,sizeof(s));
while(scanf("%d",&j)&&j){
    if(j==0)break;
  
      scanf("%d",&k);
      //    cout<<j<<' '<<k<<' '<<endl;
      edge * tem= new edge;
      tem->to = k;
      tem->next=list[j];   
      list[j]=tem;
      edge *temm= new edge;
      temm->to = j;
      temm->next=list[k];
      list[k]=temm;
}                  

root=k;
dfs(k);

cout<<"Network #"<<bcnt<<endl;
int cnt=0;
bool flag=true;
memset(visit,0,sizeof(visit));
for(int i =1;i<=1000;++i){
    if(s[i]){flag=false;
      now = i;
      for(edge* e=list[i];e;e=e->next){
    //    cout<<"wai"<<e->to<<endl;
    if(!visit[e->to]){
    ++cnt;
    ff(e->to);
    }
      }
     
      if(cnt)
    cout<<" SPF node "<<i<<" leaves "<<cnt<<" subnets"<<endl;
    
      memset(visit,0,sizeof(visit));
      cnt=0;
    }
}
if(flag) cout<<" No SPF nodes"<<endl;
cout<<endl;
}
}
//*/






//*     212K	0MS	    C++	1969B
//      212K	16MS	C++	2308B   ����Ҫmark[v]==1
//      220K	0MS	    C++	2394B   ����Ҫmark[u]=2
#include <iostream>
#include <vector>
using namespace std;

#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b

const int MAXN = 1010;
bool flag,cut[MAXN];
int mark[MAXN];  // ������ֵ��0,1,2������2����������
bool visit[MAXN];
int deep[MAXN],ancestor[MAXN];   // �������ǲ��ø��µġ�
vector< vector<int> > adj;

// Ч������������ȱ�š�������������ܴﵽ����С������ȱ��
// ���Ŵ�0��ʼ��
void dfs(int u,int father,int depth){  
    int i,v,son=0,len=adj[u].size();
    mark[u]=1,deep[u]=ancestor[u]=depth++;
    for(i=0;i<len;i++){
        v=adj[u][i];
		// ������v!=father֮���ߵ���ͷ�Ͳ�����
        if(v!=father && mark[v]==1)   // �����
            ancestor[u]=min(ancestor[u],deep[v]);
        if(mark[v]==0){               // ��ǰ��
            dfs(v,u,depth);
            son++;
            ancestor[u]=min(ancestor[u],ancestor[v]);
            if((father==-1 && son>1) || (father!=-1 && ancestor[v]>=deep[u]))
                cut[u]=true;
        }
    }
    //mark[u]=2;
}
void partition(int u){
    visit[u]=true;
    int i,len=adj[u].size();
    for(i=0;i<len;i++)
        if(!visit[adj[u][i]])
            partition(adj[u][i]);
}
int main()
{
    int i,j,x,y,n,cnt,ca=1;
    while(scanf("%d",&x),x){
        scanf("%d",&y);
        adj.assign(MAXN,vector<int>());  // ����MAXN��vector<int>���飬�൱�ڳ�ʼ����
        n=max(x,y);
        adj[x-1].push_back(y-1),  adj[y-1].push_back(x-1);

        while(scanf("%d",&x)){
            if(x==0) break;
            scanf("%d",&y);
            n=max(x,y);                  // �����ܽ����
            adj[x-1].push_back(y-1), adj[y-1].push_back(x-1);
        }

        memset(cut,false,sizeof(cut));
        memset(mark,0,sizeof(mark));

        //for(i=0;i<n;i++)
          //  if(mark[i]==0) 
                dfs(0,-1,0);

		//for(i=0; i<n; i++)
		//	if(cut[i])
		//	cout << i+1 << " ";
		//cout << endl;

        printf("Network #%d\n",ca++);
        for(flag=false,i=0; i<n; i++)
            if(cut[i]){                  // ����Ǹ�㡣
                flag=true;
                memset(visit,false,sizeof(visit));
                for(visit[i]=true,cnt=j=0;j<n;j++)
                    if(!visit[j])
                        partition(j),cnt++;  // dfs������ͨ��֧����
                printf("  SPF node %d leaves %d subnets\n",i+1,cnt);
            }
        if(!flag)
            printf("  No SPF nodes\n");
        printf("\n");
    }
    return 0;
}


//*/




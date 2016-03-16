/*    3261 C++ 280 27920 
#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

const int nMax=100005;
const int mMax=1000005;
int n,father[nMax],rank[nMax],m,sum;   //rank近似树的高度。

class edge{
public:
    int u,v,nex,flag;
};
edge e[mMax];
int k,head[nMax];

void addedge(int a,int b){//向图中加边的算法，注意加上的是有向边//b为a的后续节点既是a---->b
    e[k].u=a;
    e[k].v=b;
    e[k].nex=head[a];
    e[k].flag=1;
    head[a]=k;k++;
}

void del(int a,int b){
    for(int i=head[a];i;i=e[i].nex){
        if(e[i].v==b){
            e[i].flag=0;
        }
    }
}

int find(int x){ // 寻找父节点
    if(x!=father[x])
        return father[x]=find(father[x]);
    return x;
}

void unio(int a,int b){
    int x=find(a);
    int y=find(b);
    if(x==y)return;
	if(rank[x]==rank[y]){
		if (x<y)father[y]=x;
		else father[x]=y;
		return;
	}
	if(rank[x]>rank[y])father[y]=x;
	else father[x]=y;
}

void set(){    // 初始化
    int i;
    for(i=0; i<nMax-1; i++){
        father[i]=i;
    }
}

class cmd{
public:
    char ope[100];
    int a,b;
}list[nMax];
int ans[nMax];

int main()
{
    int i,a,b,q,f=0;
    while(scanf("%d",&n)!=EOF){
        if(f==1)    printf("\n");
        f=1;
        set();
        k=1;
        memset(head,0,sizeof(head));

        for(i=0;i<n;i++){
            scanf("%d",&rank[i]);
        }

        scanf("%d",&m);
        while(m--){
            scanf("%d%d",&a,&b);
            if(a>b)   swap(a,b);
            addedge(a,b);    // 边邻接表
        }

        scanf("%d",&q);
        for(i=0;i<q;i++){
            scanf("%s",list[i].ope);

            if(list[i].ope[0]=='d'){
                scanf("%d%d",&a,&b);
                if(a>b)   swap(a,b);
                list[i].a=a;
                list[i].b=b;
                del(a,b);     // 标记为0
            }
            else{
                scanf("%d",&list[i].a);
            }
        }

        for(i=1;i<k;i++){
            if(e[i].flag){
                unio(e[i].u,e[i].v);
            }
        }

        int N=0;
        for(i=q-1;i>=0;i--){   // 倒转来查
            if(list[i].ope[0]=='d'){
                unio(list[i].a,list[i].b);
            }
            else{
                b=find(list[i].a);
                a=rank[b];
                if(a<=rank[list[i].a]){
                    ans[N++]=-1;
                }
                else{
                    ans[N++]=b;
                }
            }
        }


        for(i=N-1;i>=0;i--){
            printf("%d\n",ans[i]);
        }
    }
    return 0;
}

//*/







//*      3261 C++ 280 1692 
#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

const int N = 10005;
const int M = 20005;
const int Q = 50005;

int rank[N];
char command[Q][10];
int cn[Q][2];
int father[N];
int ans[Q];

struct Edge{
	int u, v, next, flag;
};
Edge edge[M];
int head[N];   // 初始化-1
int cnt;       // 初始化0

void addEdge(int a, int b){
	if(a>b){
		a = a ^ b;
		b = a ^ b;
		a = a ^ b;
	}
	edge[cnt].u = a;
	edge[cnt].v = b;
	edge[cnt].next = head[a];
	edge[cnt].flag = 1;
	head[a] = cnt++;
}

void del(int a, int b){
	if(a>b){
		a = a ^ b;
		b = a ^ b;
		a = a ^ b;
	}
	for(int i=head[a]; i!=-1; i=edge[i].next){
		if(edge[i].v==b){
			edge[i].flag = 0;
			break;
		}
	}
}

int Find(int a){
	if(father[a]!=a)
		return father[a] = Find(father[a]);
	return a;
}

void Union(int a, int b){
	int A = Find(a);
	int B = Find(b);
	if(rank[A]>rank[B]){
		father[B] = A;
	}
	else if(rank[A]==rank[B]){
		if(A<B)
			father[B] = A;
		else
			father[A] = B;
	}
	else
		father[A] = B;
}

void init(){
	memset(head, -1, sizeof(head));
	for(int i=0; i<N; i++){
		father[i] = i;
	}
	cnt = 0;
}

int main()
{
	int n, m, q;
	int i;
	int a, b;
	int t = 0;

	while(scanf("%d", &n)!=EOF){
		if(t==1)   printf("\n");
		t = 1;
		init();

		for(i=0; i<n; i++)
			scanf("%d", rank+i);

		scanf("%d", &m);
		for(i=0; i<m; i++){
			scanf("%d%d", &a, &b);
			addEdge(a, b);
		}

		scanf("%d", &q);
		for(i=0; i<q; i++){
			scanf("%s", command+i);
			if(command[i][0]=='q'){
				scanf("%d", &cn[i][0]);
			}
			else{
				scanf("%d%d", &cn[i][0], &cn[i][1]);
				del(cn[i][0], cn[i][1]);
			}
		}

		for(i=0; i<m; i++){
			if(edge[i].flag==1){
				Union(edge[i].u, edge[i].v);
			}
		}

		cnt = 0;
		for(i=q-1; i>=0; i--){
			if(command[i][0]=='q'){
				b = Find(cn[i][0]);
				if(rank[cn[i][0]]<rank[b])
					ans[cnt++] = b;
				else
					ans[cnt++] = -1;
			}
			else{
				Union(cn[i][0], cn[i][1]);
			}
		}

		for(i=cnt-1; i>=0; i--){
			printf("%d\n", ans[i]);
		}
		printf("\n");
	}

	return 0;
}
//*/


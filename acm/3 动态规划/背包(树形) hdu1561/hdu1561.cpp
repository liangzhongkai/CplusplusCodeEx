//*       0MS	416K	1078 B	C++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define max(a, b) a>b?a:b

const int N = 205;
int dp[N][N];
int c[N];
int n, m;

struct node{
	int v;
	node *next;
}*head[N],good[N];
int p;

void init(){
	p = 1;
	memset(head, NULL, sizeof(head));
	memset(dp, 0, sizeof(dp));
}

void AddEdge(int a, int b){
	good[p].v = b;
	good[p].next = head[a];
	head[a] = &good[p++];
}

int dfs(int u){
	int i, j, t = 1, now;
	node *p = head[u];
	dp[u][1] = c[u];       // ��Ϊ��һ��t=1����һ����ɢȫ����dp[u][1]��ʼ���ڶ�����ɢ�ʹӣ�1�͵�һ�ε���ɢ�㣩��ʼ������ȫ                                              // ������dp[u][1]��ɫ�ʡ�

	//for(i=m; i>0; i--)     //  0MS	420K	1331 B	
	//	dp[u][i] = c[u];

	while(p!=NULL){
		int v = p->v;
		now = dfs(v);
		for(i=t; i>0; i--){
			for(j=1; j<=now; j++){           // ĳ�����Ľڵ����������Χ��
				if(dp[u][i+j]<dp[u][i]+dp[v][j])
					dp[u][i+j] = dp[u][i] + dp[v][j];
			}
		}
		t += now;
		
		p = p->next;
	}
	
	return t;
}
	
int main()
{
	freopen("in.txt", "r", stdin);
	  int i;
	  int a, b;
	  
	while(scanf("%d %d", &n, &m) && n+m){
		init();
		
		c[0] = 0;
		for (i = 1; i <= n; ++i) {	  
		  scanf("%d %d",&a, &b);
		  c[i] = b;
		  AddEdge(a, i);
		}
		  
		dfs(0);
		printf("%d\n", dp[0][m+1]);
	}
			
	return 0;
}
//*/

/*
3 2
0 1
0 2
0 3
7 4
2 2
0 1
0 4
2 9
7 1
7 6
2 2
0 0

5
18
*/




/*   0MS	428K	1155 B	    ���������㷨�Ƚ�ģ����

#include <stdio.h>
#include <string.h>

#define MAX 210
#define max(a,b) (a)>(b)?(a):(b)

  
struct node {
	  int v;
	  node *next;
}*head[MAX],tree[MAX];

int n,m,money[MAX];	//root��ʾ����ʱ�Ƿ��������
int ptr,dp[MAX][MAX];
	  
	
void Initial() {
	ptr = 1;
	memset(dp,0,sizeof(dp));
	memset(head,NULL,sizeof(head));
}

// �ڽӱ�
void AddEdge(int fa,int son) {
	tree[ptr].v = son;
	tree[ptr].next = head[fa];
	head[fa] = &tree[ptr++];
}

int Tree_DP(int v) {
	int i,j,tot = 1;
	node *p = head[v];

	while (p != NULL) {
		tot += Tree_DP(p->v);
		int tp = tot < m ? tot : m;                 //  �Ӹ���֦�������ĿǰΪֹ�ܵ����������
		for (j = tp; j >= 1; --j)                   //  ���鱳�����Ը���ֻѡһ����������ѭ��������ڱ���������Ʒ���ܹ���v�Ķ������ʶ���
			for (i = 1; i <= j; ++i)                //  ����Ʒ��dp[p->v][i] Ϊ����i�����ļ�ֵ
				if(dp[v][j]<dp[v][j-i]+dp[p->v][i])
					dp[v][j] = dp[v][j-i]+dp[p->v][i];
		p = p->next;
	}

	if (v != 0) {
		for (j = m; j >= 1; --j)    // ֪��Ϊʲôj=m��������j=tp+1�� ��Ϊ�ϲ�������϶������²㵥������������ڲ����֮�䴫��ʱ���²�ĵ�ǰ��Ϳ���û������
			dp[v][j] = dp[v][j-1] + money[v];	//��ѡ��ǰ�ڵ��Լ�����������
	}

	return tot;
}
							
							  
int main()
{
	freopen("in.txt", "r", stdin);
	int i,j,k,a,b;
	
	while (scanf("%d%d",&n,&m),n+m) {
		Initial();
		money[0] = 0;
		for (i = 1; i <= n; ++i) {	  
			scanf("%d%d",&a,&b);
			money[i] = b;
			AddEdge(a,i);
		}
										  
		Tree_DP(0);
		printf("%d\n",dp[0][m]);
	}
}
//*/











 

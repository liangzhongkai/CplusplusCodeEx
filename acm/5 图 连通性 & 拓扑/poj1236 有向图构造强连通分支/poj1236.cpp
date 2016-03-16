//  208K	0MS	  C++	2462B
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;

const int N = 105;
vector<int> adj[N];
int n,       belong[N], low[N], dep[N], cnt, num, instack[N],       in[N], out[N];

stack<int> st;
void Tarjan(int x)                         //  �����˫��ͨ�飬����ֻ�ǻ�
{
	int j;
	dep[x]=low[x]=++num;
	instack[x]=1;                          //  �൱��mark[x]
	st.push(x);
	for(j=0; j<adj[x].size(); j++){  //  ���������ѭ����low[x]��ֵ���Ѿ�ȷ���ˡ�
		int u=adj[x][j];
		if(dep[u]==-1){                    //  ��ǰ�ߣ�����������ȱ���ж�
			Tarjan(u);                     //  ����low[u]
			if(low[x]>low[u]) low[x]=low[u];
		}
		else if(instack[u] && low[x]>dep[u])//  ����
			low[x]=dep[u];
	}
	if(low[x]==dep[x]){   //  ���low[x]��ֵû�и��ģ�֤�������Ƕ�������
		cnt++;
		do{
			j=st.top();
			st.pop();
			instack[j]=0;
			belong[j]=cnt;
		}while(j!=x);
	}
}

int main()
{
	int i, j, len;
	int a;

	scanf("%d", &n);

	for(i=1; i<=n; i++){
		while(scanf("%d", &a) && a){
			adj[i].push_back(a);
		}
	}

	cnt = 0;
	num = 0;
	memset(instack, 0, sizeof(instack));
	memset(low, 0, sizeof(low));
	memset(dep, -1, sizeof(dep));
	for(i=1; i<=n; i++){
		if(dep[i]==-1){
			Tarjan(i);
		}
	}
	// debug
	//for(i=1; i<=n; i++){
	//	cout << belong[i] << " ";
	//}
	//cout << endl;
	if(cnt==1){
		printf("1\n0\n");
		return 0;
	}
	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));
	for(i=1; i<=n; i++){
		len = adj[i].size();
		for(j=0; j<len; j++){
			if(belong[i]!=belong[adj[i][j]]){
				out[belong[i]]++;       // ����
				in[belong[adj[i][j]]]++;// ���
			}
		}
	}
	// debug
	//for(i=1; i<=cnt; i++){
	//	cout << in[i] << " " << out[i] << endl;
	//}
	int ans1 = 0, ans2 = 0;
	for(i=1; i<=cnt; i++){
		if(out[i]==0)   ans2++;
		if(in[i]==0)   ans1++;
	}
	printf("%d\n%d\n", ans1, ans2>ans1?ans2:ans1);

	return 0;
}


/*
5
2 4 3 0
4 5 0
4 0
2 0
1 0

5
2 4 3 0
4 5 0
0
0
1 0

*/
//        20208K  3782MS	C++	3047B
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

#define INT_MAX  10000000
#define NMAX  20010
#define MMAX  1000000

struct EDGE{
	int u, v, cap, flow;
	int next;
	EDGE(int a=0, int b=0, int c=0, int d=0):u(a),v(b),cap(c),flow(d){}
};

struct EDGELIST{      // ���ն���ͨ�����������ȥѡ���
	int start[NMAX];  // ��¼����ĵ�һ���ߺ�
	int last[NMAX];   // ��¼��������һ���ߺ�
	int t;            // tΪ�ߺ�
	EDGE arc[MMAX];   // ����ߺ��룬����¼�ڽӱߵĹ�ϵ
	void clear(){
		t = 0;
		memset(last, -1, sizeof(last));
	}
	void push_back(EDGE edge){
		edge.next = -1;   arc[t] = edge;
		if(last[edge.u]!=-1)   arc[last[edge.u]].next = t;
		else   start[edge.u] = t;
		last[edge.u] = t;   t++;
	}
	void add_arc(EDGE edge){
		push_back(edge);   
		push_back(EDGE(edge.v, edge.u, edge.cap));
	}
}net;

int q[2][NMAX]; // ��������
int q1[2];      // �������еĶ�ͷ�±�
int q2[2];      // �������еĶ�β�±�
int qnow;       // �����±�

// ���²���������һ�����У�ȥ��������һ����Q��
// �����ͱ�����һ�����н���bfsʱʹ�ÿռ�̫�ࡣ��Ҳֻ�ǽ���������á�
void push_queue(int a){
	q[qnow][q2[qnow]++] = a;
}
int pop_queue(){
	return q[qnow^1][q1[qnow^1]++];
}
void switch_queue(){
	qnow ^= 1;
	q1[qnow] = 0,   q2[qnow] = 0;
}
bool empty_queue(){
	return q1[qnow^1] >= q2[qnow^1];
}
int size_queue(){
	return q2[qnow^1] - q1[qnow^1];
}

int n, m;
int dis[NMAX];              // BFS()��
int path[NMAX], deep;       // dinic
int cur[NMAX];              // dinic

// BFS���ֲ��Ѱ������·�Ĳ���ͬʱ�����ˡ�
// �ֲ㣺bfs��������Ѿ��������ĵ�
// ����·����Ѱ�ҵ����ʱ��������������
bool BFS(){
	int i, l, u, v;
	memset(dis, -1, sizeof(dis));
	dis[0] = 0;   qnow = 0;
	switch_queue();
	push_queue(0);
	switch_queue();

	while(!empty_queue()){
		l = size_queue();
		while(l--){                                                // �൱��������for(i=0; i<l; i++)�����ڽӱ�
			u = pop_queue();
			for(i=net.start[u]; i!=-1; i=net.arc[i].next){         // i�Ǳߺ�
				 v = net.arc[i].v;
				 if(dis[v]==-1 && net.arc[i].cap>net.arc[i].flow){
					push_queue(v);
					dis[v] = dis[u] + 1;
					if(v==n)   return true;
				 }
			}
		}
		switch_queue();   // �����д洢����ͬʱ������¶����ÿգ�0��
	}
	return false;
}

// ����Ŀ�Ķ���Ϊ�˲���dis[]���� + ��������ڽӱ�
int Dinic(){
	int i, u, neck, pos, res;
	int maxflow = 0;
	while(BFS()){
		memcpy(cur, net.start, sizeof(cur));
		deep = 0;                           // dfsջ�ĸ߶�
		u = 0;
		// ֻ֪�����ڽӱ��DFS��ʽ
		while(true){
			// �൱��dfs����ֹ������Ȼ�������Ǹ��������������е���
			if(u==n){
				neck = INT_MAX;             // ��������
				for(i=0; i<deep; i++){      // �������ô��
					res = net.arc[path[i]].cap - net.arc[path[i]].flow;
					if(res<neck){
						neck = res;
						pos = i;            // ����Լ��������ıߺ�
					}
				}
				maxflow += neck;
				for(i=0; i<deep; i++){
					net.arc[path[i]].flow += neck;
					net.arc[path[i]^1].flow -= neck;  // ����ߣ�ʵ�ʵĲ�����+/-1���ó����ڱߺ�   ǿ��
				}
				deep = pos;
				u = net.arc[path[deep]].u;  // ���Ǹ������ıߵ���㿪ʼ������dfs��
			}

			// ���� u �������ڽӱߣ��������-1����ʾ�ڷֲ�������u������û�нڵ�ģ�����֮��
			for(i=cur[u]; i!=-1; i=net.arc[i].next){
				if(net.arc[i].cap>net.arc[i].flow &&  // �ֲ������б�(u, net.arc[i].v)
					dis[u]+1==dis[net.arc[i].v])      // �ֲ�����
					break;
			}

			cur[u] = i;     // iΪ�ߺ�
			if(i!=-1){
				path[deep++] = i;
				u = net.arc[i].v;
			}
			else{
				if(deep==0)   break;
				dis[u] = -1;                // ��ʾĳ�ߵ�������û��·�������ˡ�
				u = net.arc[path[--deep]].u;
			}
		}
	}
	return maxflow;
}

int main()
{
	int i, a, b, w;
	scanf("%d %d", &n, &m);
	
	net.clear();

	for(i=1; i<=n; i++){
		scanf("%d %d", &a, &b);
		net.add_arc(EDGE(0,i,a));
		net.add_arc(EDGE(i, n+1, b));
	}
	for(i=0; i<m; i++){
		scanf("%d %d %d", &a, &b, &w);
		net.add_arc(EDGE(a, b, w));
	}

	n++;
	printf("%d\n", Dinic());
		 
	return 0;
}
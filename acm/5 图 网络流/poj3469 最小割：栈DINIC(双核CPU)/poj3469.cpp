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

struct EDGELIST{      // 最终都是通过操作顶点号去选择边
	int start[NMAX];  // 记录顶点的第一条边号
	int last[NMAX];   // 记录顶点的最后一条边号
	int t;            // t为边号
	EDGE arc[MMAX];   // 赋予边号码，及记录邻接边的关系
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

int q[2][NMAX]; // 两个队列
int q1[2];      // 两个队列的队头下标
int q2[2];      // 两个队列的队尾下标
int qnow;       // 队列下标

// 以下操作都是在一个队列，去控制另外一个，Q？
// 这样就避免了一个队列进行bfs时使用空间太多。它也只是仅有这个作用。
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
int dis[NMAX];              // BFS()用
int path[NMAX], deep;       // dinic
int cur[NMAX];              // dinic

// BFS将分层和寻找增广路的操作同时进行了。
// 分层：bfs不会遍历已经遍历过的点
// 增广路：当寻找到汇点时，就立即结束。
bool BFS(){
	int i, l, u, v;
	memset(dis, -1, sizeof(dis));
	dis[0] = 0;   qnow = 0;
	switch_queue();
	push_queue(0);
	switch_queue();

	while(!empty_queue()){
		l = size_queue();
		while(l--){                                                // 相当于以往的for(i=0; i<l; i++)遍历邻接边
			u = pop_queue();
			for(i=net.start[u]; i!=-1; i=net.arc[i].next){         // i是边号
				 v = net.arc[i].v;
				 if(dis[v]==-1 && net.arc[i].cap>net.arc[i].flow){
					push_queue(v);
					dis[v] = dis[u] + 1;
					if(v==n)   return true;
				 }
			}
		}
		switch_queue();   // 换队列存储，并同时将这个新队列置空（0）
	}
	return false;
}

// 以上目的都是为了产生dis[]数组 + 利用埋边邻接表
int Dinic(){
	int i, u, neck, pos, res;
	int maxflow = 0;
	while(BFS()){
		memcpy(cur, net.start, sizeof(cur));
		deep = 0;                           // dfs栈的高度
		u = 0;
		// 只知道边邻接表的DFS方式
		while(true){
			// 相当于dfs的终止条件，然后计算出那个调整流量，进行调整
			if(u==n){
				neck = INT_MAX;             // 调整流量
				for(i=0; i<deep; i++){      // 反向的肿么办
					res = net.arc[path[i]].cap - net.arc[path[i]].flow;
					if(res<neck){
						neck = res;
						pos = i;            // 相对自己最大调整的边号
					}
				}
				maxflow += neck;
				for(i=0; i<deep; i++){
					net.arc[path[i]].flow += neck;
					net.arc[path[i]^1].flow -= neck;  // 反向边：实际的操作是+/-1，得出相邻边号   强大！
				}
				deep = pos;
				u = net.arc[path[deep]].u;  // 从那个调满的边的起点开始，继续dfs。
			}

			// 遍历 u 的所有邻接边，如果等于-1，表示在分层网络里u后面是没有节点的，否则反之。
			for(i=cur[u]; i!=-1; i=net.arc[i].next){
				if(net.arc[i].cap>net.arc[i].flow &&  // 分层网络有边(u, net.arc[i].v)
					dis[u]+1==dis[net.arc[i].v])      // 分层网络
					break;
			}

			cur[u] = i;     // i为边号
			if(i!=-1){
				path[deep++] = i;
				u = net.arc[i].v;
			}
			else{
				if(deep==0)   break;
				dis[u] = -1;                // 表示某边的起点后面没有路可以走了。
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
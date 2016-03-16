//   416K	204MS	C++	2031B
#include<iostream>
#include<cstdio>
#include<deque>
#include<cstring>

using namespace std;

const int N = 105;
const int F = 0x7fffffff;
int n, np, nc, m;
int resi[N][N]; // 残余网络
deque<int> act; // 活跃顶点队列
int h[N];       // 高度 
int ef[N];      // 盈余 
int s, t;       // 源与汇
int V;          // 顶点数量

void push_ralabel(){
	int i;
	int sum = 0;
	int u, v, p;

	for(i=1; i<=V; i++){
		h[i] = 0;
	}
	h[s] = V;
	memset(ef, 0, sizeof(ef));
	ef[s] = F;   ef[t] = -F;
	act.push_front(s);
	printf("%d %d\n", s, t);
	
	while(!act.empty()){
		u = act.back();
		act.pop_back();
		for(i=1; i<=V; i++){
			v = i;
			if(resi[u][v]<ef[u]){  // 与多个后接节点比较，ef[u]越来越小 
				p = resi[u][v];
				/*
				if(u==s || h[u]==h[v]+1){
					printf("%d\n", p);
				}
				*/
			}
			else{
				p = ef[u];
				/*
				if(u==s || h[u]==h[v]+1){
					printf("%d\n", p);
				}
				*/
			}
			if(p>0 && (u==s || h[u]==h[v]+1)){
				resi[u][v] -= p;   resi[v][u] += p;
				if(v==t)   sum += p;
				ef[u] -= p;   ef[v] += p;
				if(v!=s && v!=t){
					act.push_front(v);    // 在链表前头插入
				}
				/*
				printf("***%d    %d\n", h[u], h[v]);
				for(i=1; i<=V; i++){
					printf("%d  ", ef[i]);   
				}
				printf("\n");
				*/
			}
		}
		if(u!=s && u!=t && ef[u]>0){
			h[u]++;
			act.push_front(u);
		}
	}

	//                       << 精华 >>
	//                         <<一>>
	// 设置高度的目的：因为对于某边<u,v>的一次推进已经将u所能推进
	// 的量都推进了，因为后接的节点高度都要低，所以流量会一直流向
	// 最低且最后的t点，那些流不进t点的会返回流入s点。
	//                         <<二>>
	// 最后所有的推进量都流入s，t两点，不用担心最后流入s,t两点时，
	// 边会溢满，因为最初所有流量的流出都是经过与s连接的边所限制，
	// 所以一定可以流回s点，所有的流量都流入s后，就代表没有活跃顶
	// 点，就退出循环。
/*
	for(i=1; i<=V; i++){
		printf("%d  ", ef[i]);   // 除两个外，全部都等于0
	}
	printf("\n");
*/
	printf("%d\n", sum);
}

int main()
{
	int i;
	int u, v, val;
	// 构图
	while(scanf("%d %d %d %d", &n, &np, &nc, &m)!=EOF){
		s = n + 1;   t = n + 2;   V = n + 2;
		memset(resi, 0, sizeof(resi));

		// 中间节点的边
		for(i=0; i<m; i++){
			while(getchar()!='(')   ;
			scanf("%d,%d)%d", &u, &v, &val);
			resi[u+1][v+1] = val;
		}

		// 源点与节点的边
		for(i=0; i<np; i++){
			while(getchar()!='(')   ;
			scanf("%d)%d", &u, &val);
			resi[s][u+1] = val;
		}

		// 节点与汇点的边
		for(i=0; i<nc; i++){
			while(getchar()!='(')   ;
			scanf("%d)%d", &u, &val);
			resi[u+1][t] = val;
		}

		// 预流推进算法
		push_ralabel();
	}

	return 0;
}

/*
2 1 1 2 (0,1)20 (1,0)10 (0)15 (1)20
7 2 3 13 (0,0)1 (0,1)2 (0,2)5 (1,0)1 (1,2)8 (2,3)1 (2,4)7
         (3,5)2 (3,6)5 (4,2)7 (4,3)5 (4,5)1 (6,0)5
         (0)5 (1)2 (3)2 (4)1 (5)4
2 1 1 2 (0,1)20 (1,0)10 (0)15 (1)10
7 2 3 13 (0,0)1 (0,1)2 (0,2)5 (1,0)1 (1,2)8 (2,3)1 (2,4)7
         (3,5)2 (3,6)5 (4,2)7 (4,3)5 (4,5)1 (6,0)5
         (0)5 (1)2 (3)2 (4)1 (5)4
*/
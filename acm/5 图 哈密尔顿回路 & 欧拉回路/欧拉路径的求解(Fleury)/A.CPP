#include<iostream>

using namespace std;

#define MAXN 200
struct stack{
	int top, node[MAXN];
}s;
int Edge[MAXN][MAXN];
int n;

void dfs(int x){
	int i;
	s.top++;
	s.node[s.top] = x;

	for(i=0; i<n; i++){
		if(Edge[i][x]>0){
			Edge[i][x] = 0;   Edge[x][i] = 0;
			dfs(i);
			break;
		}
	}
}

void Fleury(int x){   // x为2个奇数顶点的一个或者任意一个
	int i, b;
	s.top = 0; s.node[s.top] = x;
	
	while(s.top>=0){
		b = 0;
		for(i=0; i<n; i++){
			if(Edge[s.node[s.top]][i]>0){
				//cout << "*"<<s.node[s.top]<<"*"<<i<< "  "; 
				//for(int j=0; j<n; j++){
				//	for(i=0; i<n; i++){
				//		cout << Edge[j][i] << " " ;
				//	}
				//	cout << endl;
				//}
				b = 1; break;
			}
		}
		if(b==0){
			printf("%d ", s.node[s.top]+1);
			s.top--;
		}
		else{
			s.top--;
			dfs(s.node[s.top+1]);
			cout << "*" <<s.node[s.top] << "   ";
		}
	}
	printf("\n");
}

int main()
{
	int i, j;
	int m, s, t;
	int degree, num, start;
	scanf("%d%d", &n, &m);
	memset(Edge, 0, sizeof(Edge));

	for(i=0; i<m; i++){
		scanf("%d%d", &s, &t);
		Edge[s-1][t-1] = 1;   Edge[t-1][s-1] = 1;
	}

	num = 0;   start = 0;
	for(i=0; i<n; i++){
		degree = 0;
		for(j=0; j<n; j++){
			degree += Edge[i][j];
		}
		if(degree&1){
			start = i;   num++;
		}
	}

	if(num==0 || num==2)   Fleury(start);
	else   printf("No, Euler path\n");


	return 0;
}

/*
9 14
1 2
1 8
2 3
2 8
2 9
3 4
4 5
4 6
4 9
5 6
6 7
6 9
7 8
8 9

*/
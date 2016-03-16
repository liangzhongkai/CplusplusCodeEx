//  1512K	125MS	C++	1602B
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

#define N 60

struct node
{
	int a,b,c;
	int time;
}cur,next;
int mark[N][N][N],n;//mark[][][]保存当前时刻3个盘子所在位置
char map[N][N];

int bfs()
{
	int i;
	queue<node> q;
	memset(mark,0,sizeof(mark));
	cur.time=0;
	mark[cur.a][cur.b][cur.c]=1;
	if(cur.a==cur.b && cur.b==cur.c)return 0;
	q.push(cur);

	while(!q.empty())
	{
		cur=q.front();
		q.pop();
		
		for(i=1;i<=n;i++)
		{
			if(map[cur.a][i]==map[cur.b][cur.c] && !mark[i][cur.b][cur.c])
			{//对图中每个点遍历，满足条件的就入队，并将这种状态标记，避免重复操作
				mark[i][cur.b][cur.c]=1;
				next.time=cur.time+1;
				next.a=i, next.b=cur.b, next.c=cur.c;
				if(next.a==next.b && next.b==next.c) return next.time;
				q.push(next);
			}
			if(map[cur.b][i]==map[cur.a][cur.c] && !mark[cur.a][i][cur.c])
			{
				mark[cur.a][i][cur.c]=1;
				next.time=cur.time+1;
				next.a=cur.a, next.b=i, next.c=cur.c;
				if(next.a==next.b && next.b==next.c) return next.time;
				q.push(next);
			}
			if(map[cur.c][i]==map[cur.b][cur.a] && !mark[cur.a][cur.b][i])
			{
				mark[cur.a][cur.b][i]=1;
				next.time=cur.time+1;
				next.a=cur.a, next.b=cur.b, next.c=i;
				if(next.a==next.b && next.b==next.c) return next.time;
				q.push(next);
			}
		}
	}
	return -1;
}
int main()
{
	int i,j;
	while(scanf("%d",&n),n)
	{
		scanf("%d%d%d%c",&cur.a,&cur.b,&cur.c);
		
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=n;j++)
			{
				cin>>map[i][j];//cin的确很好用的说……
			}
		}
		int x=bfs();
		if(x!=-1) printf("%d\n",x);
		else printf("impossible\n");
	}
	return 0;
}




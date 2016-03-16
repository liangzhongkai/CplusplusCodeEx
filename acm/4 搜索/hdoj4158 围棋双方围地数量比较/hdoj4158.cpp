//  15MS	284K	2164 B	C++
#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

typedef pair<int, int> pii;

int mp[21][21];
bool vis[21][21];
int bsum, wsum;
int n;

void bfs(int x, int y)
{
	int a, b;
	int key = 0, temp=0;
	int sum = 1;

	queue<pii> q;
	q.push(make_pair(x, y));
	vis[x][y] = true;
	
	while(!q.empty())
	{
		pii tmp = q.front();
		a = tmp.first;
		b = tmp.second;
		q.pop();

		if(b+1<=n && !vis[a][b+1])
		{
			if(mp[a][b+1]==0)
			{
				vis[a][b+1] = true;
				sum++;
				q.push(make_pair(a, b+1));
			}
			else if(temp!=0 && temp!=mp[a][b+1])
				key = 1;
			else if(temp==0)
				temp = mp[a][b+1];
		}
		if(a+1<=n && !vis[a+1][b] )
		{
			if(mp[a+1][b]==0)
			{
				vis[a+1][b] = true;
				sum++;
				q.push(make_pair(a+1,b));
			}
			else if(temp!=0 && temp!=mp[a+1][b])
				key = 1;
			else if(temp==0) 
				temp = mp[a+1][b];
		}
		if(b-1>=1 && !vis[a][b-1] )
		{
			if(mp[a][b-1]==0)
			{
				vis[a][b-1] = true;
				sum++;
				q.push(make_pair(a,b-1));
			}
			else if(temp!=0 && temp!=mp[a][b-1])
				key = 1;
			else if(temp==0) 
				temp = mp[a][b-1];
		}
		if(a-1>=1 && !vis[a-1][b])
		{
			if(mp[a-1][b]==0)
			{
				vis[a-1][b] = true;
				sum++;
				q.push(make_pair(a-1,b));
			}
			else if(temp!=0 && temp!=mp[a-1][b])
				key = 1;
			else if(temp==0) 
				temp = mp[a-1][b];
		}
	}

	if(key==1)
		return ;
	else
	{
		if(temp==1)
			bsum += sum;
		else
			wsum += sum;
	}
}

int main()
{	
	int a, b;
	int i, j;
	int x, y;

	while(cin >> n && n!=0 && cin >> a >> b)
	{
		memset(mp, 0, sizeof(mp));
		memset(vis, false, sizeof(vis));

		for(i=0; i<a; i++)
		{
			cin >> x >> y;
			mp[x][y] = 1;
		}

		for(i=0; i<b; i++)
		{
			cin >> x >> y;
			mp[x][y] = 2;
		}

		bsum = 0; wsum = 0;
		for(i=1; i<=n; i++)
		{
			for(j=1; j<=n; j++)
			{
				if(mp[i][j]==0 && !vis[i][j]) 
				{
					bfs(i, j);
				}
			}
			cout << bsum << " " << wsum << endl;
		}

		if(bsum==wsum)
			cout << "Draw" << endl;
		if(bsum>wsum)
			cout << "Black wins by " << bsum-wsum << endl;
		if(bsum<wsum)
			cout << "White wins by " << wsum-bsum << endl;
	}

	return 0 ;
}
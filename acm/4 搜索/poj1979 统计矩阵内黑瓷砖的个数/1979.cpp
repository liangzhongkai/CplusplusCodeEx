#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

typedef pair<int, int> pi;

char map[21][21];
bool flag[21][21];

int x[4]={1,-1,0,0};
int y[4]={0,0,1,-1};

int main()
{
	int w, h;
	int i, j;
	int a, b;
	int xx, yy;
	int ans;

	while( cin >> w >> h && w!=0 && h!=0 )
	{
		for( i=1; i<=h; i++ )
			for( j=1; j<=w; j++ )
			{
				cin >> map[i][j];
				if( map[i][j]=='@' )
				{
					a = i; 
					b = j;
				}
			}

		ans = 1;
		memset(flag, false, sizeof(flag));
		flag[a][b] = true;
		queue<pi> q;
		q.push(make_pair(a,b));

		while(!q.empty())
		{
			pi temp;
			temp = q.front();
			q.pop();
			for(i=0; i<4; i++ )
			{
				xx = temp.first + x[i];
				yy = temp.second + y[i];
				if( xx>0 && xx<=h && yy>0 && yy<=w && !flag[xx][yy] && map[xx][yy]=='.' )
				{
					ans++;
					flag[xx][yy] = true;
					q.push(make_pair(xx, yy));
				}
			}
		}

		cout << ans << endl;

	}

	return 0;
}
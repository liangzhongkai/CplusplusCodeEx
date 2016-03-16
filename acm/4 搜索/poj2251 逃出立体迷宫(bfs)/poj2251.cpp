//*     464K	16MS	C++	2187B

#include<iostream>
#include<queue>

using namespace std;

struct point
{
	int l, x, y;
};

int l, r, c;

int ll[6] = {0,0,0,0,1,-1};
int xx[6] = {1,0,-1,0,0,0};
int yy[6] = {0,1,0,-1,0,0};

bool is_inside(int a, int b, int d)
{
	if( a>=0 && a<l && b>=0 && b<c && d>=0 && d<r )
		return true;
	return false;
}

int main()
{
	 int i, j, k;
	 int sl, sx, sy;
	 int el, ex, ey;

	 while( cin >> l >> r >> c && l!=0 && r!=0 && c!=0 )
	 {
		  char map[31][31][31];
		  bool vis[31][31][31];
		  int  ans[31][31][31];

		  for(i=0; i<31; i++)
			  for(j=0; j<31; j++)
				  for(k=0; k<31; k++)
				  {
					  ans[i][j][k] = 0;
					  vis[i][j][k] = false;
				  }
		  char tmp;
		  tmp = cin.get();

		  for(i=0; i<l; i++)
		  {
			  for(j=0; j<=r; j++)
			  {
				  gets(map[i][j]);
				  if(map[i][j][0]==10) break;
				  for(k=0; k<c; k++)
				  {
					  if(map[i][j][k]=='S')
					  {
						  sl = i;  sx = k; sy = j;
					  }
					  else if(map[i][j][k]=='E')
					  {
						  el = i;  ex = k; ey = j;
					  }
				  }
			  }
		  }

		  //cout << sl << sy << sx << endl;
		  //cout << el << ey << ex << endl;

		  queue<point> q;
		  point temp;
		  temp.l = sl;  temp.x = sx;  temp.y = sy;
		  q.push(temp);
		  vis[sl][sy][sx] = true;
		  ans[sl][sy][sx] = 0;
		  int key = 0;
		  while(!q.empty())
		  {
			  temp = q.front();
			  q.pop();

			  for(i=0; i<6; i++)
			  {
				  point tp;
				  tp.l = temp.l + ll[i];
				  tp.x = temp.x + xx[i];
				  tp.y = temp.y + yy[i];

				  if(tp.l==el && tp.x==ex && tp.y==ey)
				  {
					  ans[tp.l][tp.y][tp.x] = ans[temp.l][temp.y][temp.x] + 1;
					  key = 1;
					  break;
				  }

				  if(is_inside(tp.l, tp.x, tp.y) && !vis[tp.l][tp.y][tp.x] && map[tp.l][tp.y][tp.x]=='.')
				  {
						vis[tp.l][tp.y][tp.x] = true;
						ans[tp.l][tp.y][tp.x] = ans[temp.l][temp.y][temp.x] + 1;
						
						q.push(tp);
				  }
				 
			  }

			  if(key==1)
				  break;
		  }

		  if(ans[el][ey][ex]!=0)
			cout << "Escaped in " << ans[el][ey][ex] << " minute(s)." << endl;
		  else
			  cout << "Trapped!" << endl;
	 }

	return 0;
}

//*/
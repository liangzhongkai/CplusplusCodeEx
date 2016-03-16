//*    错在 不是按字典序 去排列顺序
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct point
{
	int x, y;
	int num;
}ans[70];

int p, q;
bool vis[27][27];
int xx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
int yy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

bool is_inmap(int x, int y)
{
	if(x>0 && x<=p && y>0 && y<=q)
		return true; 
	else
		return false;
}

int count(point a)
{
	int sum = 0;
	for(int i=0; i<8; i++)
	{
		int x = a.x + xx[i];
		int y = a.y + yy[i];
		if(!vis[x][y] && is_inmap(x, y))
			sum++;
	}
	return sum;
}

bool cmp(const point &a, const point &b)
{
	return a.num<b.num;
}

bool dfs(int x, int y, int ceng)
{
	int i;
	if(ceng>=p*q)
		return true;
	else
	{
		vector<point> vec1;
		point t;

		for(i=0; i<8; i++)
		{
			t.x = x + xx[i];
			t.y = y + yy[i];
			if(!vis[t.x][t.y] && is_inmap(t.x, t.y))
			{
				vec1.push_back(t);
			}
		}

		for(i=0; i<vec1.size(); i++)
		{
			vec1[i].num = count(vec1[i]);
		}

		sort(vec1.begin(), vec1.end(), cmp);

		for(i=0; i<vec1.size(); i++)
		{
			ans[ceng+1].x = vec1[i].x;
			ans[ceng+1].y = vec1[i].y;
			vis[vec1[i].x][vec1[i].y] = true;

			if(dfs(vec1[i].x, vec1[i].y, ceng+1))
				return true;

			vis[vec1[i].x][vec1[i].y] = false;
		}
	}
	return false;
}

int main()
{
	 int tc;
	 int i, cnt =1;
	 cin >> tc;
	 while(tc--)
	 {
		 cin >> p >> q;
		 if(p*q>26)
		 {
			 cout << "Scenario #" << cnt << ":" << endl << "impossible" << endl << endl;
			 continue;
		 }
		 memset(vis, false, sizeof(vis));
		 vis[1][1] = true;
		 point tp;
		 tp.x = 1; tp.y = 1;
		 ans[1] = tp;

		 if(dfs(1, 1, 1))
		 {
			 cout << "Scenario #" << cnt << ":" << endl;
			 for(i=1; i<=p*q; i++)
			 {
				 cout << char(ans[i].y+64) << ans[i].x;
			 }
			 cout << endl;
		 }
		 else
			 cout << "Scenario #" << cnt << ":" << endl << "impossible" << endl;
		 cout << endl;

		cnt++;
	 }
		
	return 0;
}
//*/

/*
#include <iostream>
using namespace std;

int main()
{
	//freopen("in.txt","r",stdin);
	int i,n,p,q;
	cin >> n;
	for(i=1;i<=n;i++)
	{
		cin>>p>>q;
		cout<<"Scenario #"<<i<<":"<<endl;
		if(p==1 &&q ==1)
			cout<<"A1"<<endl;
		else if(p==3 && q==4)
			cout<<"A1C2A3B1D2B3C1A2C3D1B2D3"<<endl;
		else if(p==3 && q==7)
			cout<<"A1B3D2F1G3E2G1F3E1G2E3C2A3B1C3A2C1D3B2D1F2"<<endl;
		else if(p==3 && q==8)
			cout<<"A1B3C1A2C3D1B2D3E1G2E3C2A3B1D2F1H2F3G1E2G3H1F2H3"<<endl;
		else if(p==4 && q==3)
			cout<<"A1B3C1A2B4C2A3B1C3A4B2C4"<<endl;
		else if(p==4 && q==5)
			cout<<"A1B3C1A2B4D3E1C2D4E2C3A4B2D1E3C4A3B1D2E4"<<endl;
		else if(p==4 && q==6)
			cout<<"A1B3C1A2B4C2D4E2F4D3E1F3D2B1A3C4B2A4C3E4F2D1E3F1"<<endl;
		else if(p==5 && q==4)
			cout<<"A1B3A5C4D2B1A3B5D4C2B4A2C1D3C5A4B2D1C3D5"<<endl;
		else if(p==5 && q==5)
			cout<<"A1B3A5C4A3B1D2E4C5A4B2D1C3B5D4E2C1A2B4D5E3C2E1D3E5"<<endl;
		else if(p==6 && q==4)
			cout<<"A1B3A5C6D4B5D6C4D2B1A3C2B4A2C1D3B2D1C3D5B6A4C5A6"<<endl;
		else if(p==7 && q==3)
			cout<<"A1B3C1A2C3B1A3C2B4A6C7B5A7C6A5B7C5A4B2C4B6"<<endl;
		else if(p==7 && q==4)
			cout<<"A1B3A5B7D6B5A7C6D4C2A3B1D2C4B2A4B6D7C5A6C7D5B4D3C1A2C3D1"<<endl;
		else if(p==8 && q==3)
			cout<<"A1B3C1A2B4C2A3B1C3A4B2C4A5B7C5A6B8C6A7B5C7A8B6C8"<<endl;
		else
			cout<<"impossible"<<endl;
		cout<<endl;
	}
	return 0;

}


//*/






/*    172K	16MS	C	1037B
#include <stdio.h>
#include <memory.h>

int visit[26][26],locatex[626],step[8][2]={-1,-2,1,-2,-2,-1,2,-1,-2,1,2,1,-1,2,1,2};
char locatey[626];
int p,q,cas;

void put()
{
	int i,j;
	for(i=0;i<p*q;i++)
		printf("%c%d",locatey[i],locatex[i]+1);
	printf("\n");
}

int search(int deep,int r,int x)
{
	int i,sx,sy;
	if(deep==p*q-1) {locatex[deep]=r;locatey[deep]=x+'A';return 1;}
	for(i=0;i<8;i++)
	{
		sx=r+step[i][0];sy=x+step[i][1];
		if(sx>=0&&sx<p&&sy>=0&&sy<q&&visit[sx][sy])
		{
			visit[sx][sy]=0;
			locatex[deep]=r;
			locatey[deep]=x+'A';

			if(search(deep+1,sx,sy))
				return 1;

			visit[sx][sy]=1;
			locatex[deep]=-1;
			locatey[deep]='0';
		}
	}
	return 0;
}

int main()
{
	int i;
	scanf("%d",&cas);
	for(i=1;i<=cas;i++)
	{
		scanf("%d %d",&p,&q);
		memset(visit,1,sizeof(visit));
		visit[0][0]=0;
		printf("Scenario #%d:\n",i);
		if(search(0,0,0)) put();
		else if(p==1 && q==1) printf("A1\n");
		else printf("impossible\n");
		if(i!=cas) printf("\n");
	}
	return 0;
}
//*/
//      476K	47MS	C++	1824B
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>

using namespace std;

//ifstream  fin("data.txt");
//#define  cin  fin 

struct point
{
	int price, level, expend;
}mp[105];

vector<int> vec1[105], vec2[105];   // 物品id, 边权值
//bool vis[105];

struct node
{
	int id, ml, mr, sum;
	bool operator<(const node &a)const
	{
		return a.sum<sum;
	}
};

int main()
{
	int m, n;
	int a, b;
	int i, j;
	int Ml, Mr;

	cin >> m >> n;
	for(i=1; i<=n; i++)
	{
		cin >> mp[i].price >> mp[i].level >> mp[i].expend;
		if(i==1)
			Ml = Mr = mp[i].level;
		for(j=0; j<mp[i].expend; j++)
		{
			cin >> a >> b;
			vec1[i].push_back(a);
			vec2[i].push_back(b);
		}
	}

	priority_queue<node> q;
	node temp;
	temp.id = 1;  temp.ml = Ml;  temp.mr = Mr;  temp.sum = 0;
	q.push(temp);
	int ans = mp[1].price;

	while(!q.empty())
	{
		node tmp = q.top();
		q.pop();
		int id = tmp.id;

		if(ans>tmp.sum+mp[tmp.id].price)
			ans = tmp.sum+mp[tmp.id].price;
		if(tmp.sum>mp[1].price)
			continue;

		for(i=0; i<vec1[id].size(); i++)
		{
			temp.id = vec1[id][i];
			if(mp[temp.id].level>tmp.ml && mp[temp.id].level<tmp.mr ) 
			{
				temp.ml = tmp.ml,  temp.mr = tmp.mr;
				temp.sum = tmp.sum + vec2[id][i];
				q.push(temp);
				//vis[temp.id] = true;
			}
			else if(mp[temp.id].level<=tmp.ml && mp[temp.id].level>=tmp.mr-m ) 
			{
				temp.ml = mp[temp.id].level,  temp.mr = tmp.mr;
				temp.sum = tmp.sum + vec2[id][i];
				q.push(temp);
				//vis[temp.id] = true;
			}
			else if(mp[temp.id].level>=tmp.mr && mp[temp.id].level<=tmp.ml+m ) 
			{
				temp.ml = tmp.ml,  temp.mr = mp[temp.id].level;
				temp.sum = tmp.sum + vec2[id][i];
				q.push(temp);
				//vis[temp.id] = true;
			}
		}
	}

	cout << ans << endl;


	return 0;
}

#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int n, m;

struct point{
	int x[12];
	int id;
	//operator = (const point &a)const{
	//	memcpy(x, a.x, sizeof(x));
	//	id = a.id;
	//}
	
}mp[105];

struct node{
	int x;
	int id;
}mm[12];

bool cmp1(const node &a, const node &b){
	return a.x<b.x;
}

bool cmp2(const point &a, const point &b){
	int id;
	for(int i=0; i<m; i++){
		id = mm[i].id;
		if(a.x[id]==b.x[id]){
			continue;
		}
		else{
			return a.x[id]<b.x[id];
		}
	}
	return a.id<b.id;
}

int main()
{
	int tc;
	int i, j;
	int Q;

	cin >> tc;
	while(tc--){
		cin >> n >> m;
		for(i=0; i<n; i++){
			mp[i].id = i;
			for(j=0; j<m; j++){
				cin >> mp[i].x[j];
			}
		}
		
		cin >> Q;
		
		for(i=0; i<Q; i++){
			for(j=0; j<m; j++){
				cin >> mm[j].x;
				mm[j].id = j;
			}

			sort(mm, mm+m, cmp1);
			sort(mp, mp+n, cmp2);

			for(j=0; j<n-1; j++){
				cout << mp[j].id << " ";
			}
			cout << mp[n-1].id << endl;
		}

	}

	return 0;
}


/*
2
6 3
1 1 1
1 2 3
2 2 4
2 2 3
3 1 2
3 2 2
4
1 2 3
0 1 2
30 20 10
0 -1 1
5 4
1 1 1 1
1 1 4 4
2 2 3 4
2 2 3 4
3 1 2 3
4
1 2 3 4
-1 2 -3 4
10 2 3 4
0 1 2 -1
*/
/*
K==1,   prime=997    1704ms

K==2,   prime=1999   1438ms

K==8,   prime=7993   1110ms

K==10,  prime=9973   1063ms

K==30,  prime=29989  1000ms

K==50,  prime=49999  1016ms

K==100, prime=99991  1000ms
*/
#include<iostream>
#include<vector>

using namespace std;

const int prime = 1999;

struct point{
	int x,y;
	point(){};
	point(int a, int b):x(a),y(b){};
}mp[1005];

vector<point> hash[2000];

void Hash(int a, int b){
	int x=0,y=0;
	if(a<0) x = -a;
	if(b<0) y = -b;
	//int key = (x*37199+y*19) % prime;      //  Time Limit Exceeded
	int key = (x+y) % prime;
	hash[key].push_back(point(a, b));
}

bool find(int a, int b){
	int i, x=0, y=0;
	if(a<0) x = -a;
	if(b<0) y = -b;
	int key = (x+y) % prime;
	//int key = (a*a+b*b) % prime;
	if(hash[key].size()==0)  return false;
	else{
		for(i=0; i<hash[key].size(); i++){
			if(hash[key][i].x==a && hash[key][i].y==b)
				return true;
		}
	}
	return false;
}

int main()
{
	int n;
	int i, j, ans;
	int x3, y3, x4, y4;
	int a, b;

	while(cin >> n && n!=0){
		for(i=0; i<2000; i++)
			hash[i].clear();

		for(i=0; i<n; i++){
			scanf("%d%d", &mp[i].x, &mp[i].y);
			Hash(mp[i].x, mp[i].y);
		}

		ans = 0;
		for(i=0; i<n-1; i++){
			for(j=i+1; j<n; j++){
				a = mp[i].y - mp[j].y;
				b = mp[j].x - mp[i].x;
				x3 = mp[i].x + a;
				y3 = mp[i].y + b;
				x4 = mp[j].x + a;
				y4 = mp[j].y + b;

				if(find(x3, y3) && find(x4, y4)){
					//cout << i << " " << j << endl;
					ans++;
				}

				a = mp[j].y - mp[i].y;
				b = mp[i].x - mp[j].x;
				x3 = mp[i].x + a;
				y3 = mp[i].y + b;
				x4 = mp[j].x + a;
				y4 = mp[j].y + b;

				if(find(x3, y3) && find(x4, y4)){
					//cout << i << " " << j << endl;
					ans++;
				}
			}
		}

		cout << ans/4 << endl;
	}

	return 0;
}

/*
9
-19999 -19999
-19999 0
0 -19999
0 0
-19999 19999
0 19999
19999 19999
19999 0
19999 -19999
4 --> 6

9
-19999 -19999
-19999 0
-19999 19999
0 -19999
0 0
0 19999
19999 19999
19999 0
19999 -19999

9
0 0
1 0
2 0
0 2
1 2
2 2
0 1
1 1
2 1
6
*/

/*    376K	1704MS	C++	1428B
#include<iostream>
#include<vector>

using namespace std;

const int prime = 1999;

struct point{
	int x,y;
	point(){};
	point(int a, int b):x(a),y(b){};
}mp[1005];

vector<point> hash[2000];

void Hash(int a, int b){
	int key = (a*a+b*b) % prime;
	hash[key].push_back(point(a, b));
}

bool find(int a, int b){
	int i;
	int key = (a*a+b*b) % prime;
	if(hash[key].size()==0)  return false;
	else{
		for(i=0; i<hash[key].size(); i++){
			if(hash[key][i].x == a && hash[key][i].y == b)
				return true;
		}
	}
	return false;
}

int main()
{
	int n;
	int i, j, ans;
	int x3, y3, x4, y4;
	int a, b;

	while(cin >> n && n!=0){
		for(i=0; i<2000; i++)
			hash[i].clear();

		for(i=0; i<n; i++){
			scanf("%d%d", &mp[i].x, &mp[i].y);
			Hash(mp[i].x, mp[i].y);
		}

		ans = 0;
		for(i=0; i<n-1; i++){
			for(j=i+1; j<n; j++){
				a = mp[i].y - mp[j].y;
				b = mp[j].x - mp[i].x;
				x3 = mp[i].x + a;
				y3 = mp[i].y + b;
				x4 = mp[j].x + a;
				y4 = mp[j].y + b;

				if(find(x3, y3) && find(x4, y4)){
					//cout << i << " " << j << endl;
					ans++;
				}

				a = mp[j].y - mp[i].y;
				b = mp[i].x - mp[j].x;
				x3 = mp[i].x + a;
				y3 = mp[i].y + b;
				x4 = mp[j].x + a;
				y4 = mp[j].y + b;

				if(find(x3, y3) && find(x4, y4)){
					//cout << i << " " << j << endl;
					ans++;
				}
			}
		}
		cout << ans/4 << endl;
	}
	return 0;
}
*/
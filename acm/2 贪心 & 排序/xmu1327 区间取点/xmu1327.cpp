/*
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 1000005;
struct point{
	long long x, y;
}mp[N];

bool cmp(const point &a, const point &b){
	if(a.y==b.y)
		return a.x>b.x;   // 这步很关键
	return a.y<b.y; 
}

int main()
{
	int n;
	int i;
	long long k;

	cin >> n; 
	if(n<=0 || n>=1000000)
		return 0;
	for(i=0; i<n; i++){
		scanf("%lld%lld", &mp[i].x, &mp[i].y);
	}
	if(n==1)
		cout << 1 << endl;
	else{
		sort(mp, mp+n, cmp);

		long long ans = 1;
		k = mp[0].y;
		for(i=1; i<n; i++){
			if(k<mp[i].x){
				ans++;
				k = mp[i].y;
			}
		}

		printf("%lld\n", ans);
	}

	return 0;
}
*/
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 1000005;
struct point{
	__int64 x, y;
}mp[N];

bool cmp(const point &a, const point &b){
	if(a.y==b.y)
		return a.x>b.x;   // 这步很关键
	return a.y<b.y; 
}

int main()
{
	int n;
	int i;
	__int64 k;

	cin >> n; 
	if(n<=0 || n>=1000000)
		return 0;
	for(i=0; i<n; i++){
		scanf("%I64d%I64d", &mp[i].x, &mp[i].y);
	}
	if(n==1)
		cout << 1 << endl;
	else{
		sort(mp, mp+n, cmp);

		int ans = 1;
		k = mp[0].y;
		for(i=1; i<n; i++){
			if(k<mp[i].x){
				ans++;
				k = mp[i].y;
			}
		}

		cout << ans << endl;
	}

	return 0;
}
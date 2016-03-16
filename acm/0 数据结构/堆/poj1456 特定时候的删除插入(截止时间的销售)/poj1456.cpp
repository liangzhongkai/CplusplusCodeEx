

/*    284K	63MS	C++	1752B      ¶ÑÊµÏÖ
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 10005;

struct point{
	int x, t;
}mp[N];

bool cmp(const point &a, const point &b){
	if(a.t==b.t)
		return a.x>b.x;
	else 
		return a.t<b.t;
}

int minheap[N], len;

bool kctless(const int &a, const int &b){
	return a>b;
}

void insert(int a){
	minheap[len++] = a;
	push_heap(minheap, minheap+len, kctless);
}

void remove(){
	pop_heap(minheap, minheap+len--, kctless);
}


int main()
{
	int n; 
	int time, num, count;
	int i;
	int ans;

	while(scanf("%d", &n)!=EOF){
		for(i=0; i<n; i++){
			scanf("%d %d", &mp[i].x, &mp[i].t);
		}

		sort(mp, mp+n, cmp);

		len = 0;
		count = 1;
		time = num = mp[0].t;
		num--;
		insert(mp[0].x);
		for(i=1; i<n; i++){
			if(time!=mp[i].t){
				num = mp[i].t - count;
				time = mp[i].t;
			}
			if(num>0){
				insert(mp[i].x);
				count++;
				num--;
			}
			else if(num<=0){
				if(minheap[0]<mp[i].x){
					remove();
					insert(mp[i].x);
				}
			}
		}

		ans = 0;
		for(i=0; i<len; i++){
			ans += minheap[i];
		}

		printf("%d\n", ans);
	}

	return 0;
}
//*/

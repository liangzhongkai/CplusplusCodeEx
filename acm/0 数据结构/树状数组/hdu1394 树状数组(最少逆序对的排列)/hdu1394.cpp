//  15MS	284K	776 B	C++	
#include<iostream>

using namespace std;

const int N = 6000;
int tree[N];
int maxn;

inline int Lowbit(int x)
{
	return x & (-x);
}
void Update(int x, int c)
{
	int i;
	for (i = x; i <= maxn; i += Lowbit(i)) 
		tree[i] += c; 
}
int Getsum(int x)
{
	int i;
	int temp(0);
	for (i = x; i >= 1; i -= Lowbit(i)) 
	 	temp += tree[i];
	return temp;
}

int main()
{
	int i;
	int mp[N];

	while(~scanf("%d", &maxn)){
		int sum = 0; 
		memset(tree, 0, sizeof(tree));
		for(i=0; i<maxn; i++){
			scanf("%d", &mp[i]);
			sum += Getsum(maxn) - Getsum(mp[i]+1);
			Update(mp[i]+1, 1);
		}

		int ret = sum;
		for(i=0; i<maxn; i++){
			sum += maxn - mp[i] - mp[i] - 1;
			ret = ret<sum?ret:sum;
		}

		printf("%d\n", ret);
	}

	return 0;
}
//*  4532K	1469MS	C++	1245B
// 这里线段树的作用只是想知道前面还有多少个空位
#include<iostream>
#include<vector>
#include<cstdio>

using namespace std;



#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
const int N = 222222;
int sum[N<<2];

int mp1[N], mp2[N];
int value[N];

void pushup(int rt){
	sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}

void build(int l, int r, int rt){
	if(l==r){
		sum[rt] = 1;
		return ;
	}
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
	pushup(rt);
}

void update(int p, int val, int l, int r, int rt){
	if(l==r){
		sum[rt]--;
		value[l] = val;
		return;
	}
	int m = (l + r) >> 1;
	if(p<=sum[rt<<1])
		update(p, val, lson);
	else
		update(p-sum[rt<<1], val, rson);
	pushup(rt);
}


int main()
{
	int n;
	int i;

	while(~scanf("%d", &n)){
		build(1, n, 1);

		for(i=0; i<n; i++){
			scanf("%d%d", &mp1[i], &mp2[i]);
		}
		for(i=n-1; i>=0; i--){
			update(mp1[i]+1, mp2[i], 1, n, 1);
		}
		for(i=1; i<n; i++){
			printf("%d ", value[i]);
		}
		printf("%d\n", value[n]);
	}

	return 0;
}
//*/

/*   8724K	1766MS	C++	1202B

#include <iostream>
using namespace std;

#define maxn 200001

int per[maxn][2];
int s[maxn*3],e[maxn*3],c[maxn*3];

int value[maxn];

void init(int start, int end, int num)
{
    if (start == end)
    {
        s[num] = start;
        e[num] = end;
        c[num] = 1;
    }
    else
    {
        s[num] = start;
        e[num] = end;
        c[num] = end-start+1;
        int temp = (start+end)/2;
        init(start,temp,2*num);
        init(temp+1,end,2*num+1);
    }
}

void change(int first,int second,int num)
{
    --c[num];
    if (s[num] == e[num]){
		//printf("%d %d\n", second, s[num]);
        value[s[num]] = second;
        return;
    }
    if (c[num*2] > first){
        change(first,second,num*2);
    }
    else{
        change(first - c[num*2],second,num*2+1);
    }
}

int main()
{
    int n;
    while (cin >> n)
    {
        int i;
        init(1,n,1);
		
        for (i = 0; i < n; ++i)
            scanf("%d %d", &per[i][0], &per[i][1]);
        for (i = n-1; i >= 0; --i)
            change(per[i][0],per[i][1],1);
        for (i = 1; i < n; ++i)
            printf("%d ", value[i]);
        printf("%d\n",value[i]);
    }
    return 0;
}
//*/



/*      11944K	1657MS	C++	1272B
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 200001;

int post[MAXN];
int value[MAXN];

struct Node {
	Node() : value(-1){};
	int left, right, num, value;
};

Node array[3 * MAXN];

int result[MAXN];

void BuildTree(int v, int l, int r) {
	array[v].left = l;
	array[v].right = r;
	array[v].num = r - l + 1;
	array[v].value = -1;

	if (l >= r) return;

	int mid = (l + r) / 2;

	BuildTree(2 * v, l , mid);
	BuildTree(2 * v + 1, mid + 1, r);
}

void Insert(int v, int i, int pos)
{
	array[v].num--;

	if (array[v].left == array[v].right) {
		array[v].value = value[i];
		result[array[v].left] = value[i];
		return;
	}

	if (array[2 * v].num > pos) {
		Insert(2 * v, i, pos);
	} else {
		Insert(2 * v + 1, i, pos - array[2 * v].num);
	}
}

int main() {
//	freopen("input","r",stdin);

	int N;
	int i;
	while (cin >> N) {
		for ( i = 1; i <= N; i++) {
			scanf("%d %d", &post[i], &value[i]);
		}

		BuildTree(1, 1, N);

		for ( i = N; i >= 1; i--) {
			Insert(1, i, post[i]);
		}

		for ( i = 1; i <= N; i++) {
			if (i != N) {
				printf("%d ", result[i]);
			} else {
				printf("%d", result[i]);
			}
		}
		printf("%c", '\n');

	}
	return 0;
}
//*/
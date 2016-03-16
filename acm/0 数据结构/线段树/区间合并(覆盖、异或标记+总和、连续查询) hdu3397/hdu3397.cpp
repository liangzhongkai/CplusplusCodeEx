/*    1000MS	5416K	3375 B	C++
//    984MS	    5416K	3308 B	C++
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)>(b)?(b):(a))

const int N = 100010;
int sum[N<<2];
int cover[N<<2];                   // -2为没染色， -1为混色，0,1为两种颜色
int msum[N<<2], lsum[N<<2], rsum[N<<2];

void pushup(int rt, int m){
	sum[rt] = sum[rt<<1] + sum[rt<<1|1];

	lsum[rt] = lsum[rt<<1];
	rsum[rt] = rsum[rt<<1|1];
	msum[rt] = max(msum[rt<<1], msum[rt<<1|1]);
			
	if(lsum[rt]==m-(m>>1))   lsum[rt] += lsum[rt<<1|1];
	if(rsum[rt]==(m>>1))   rsum[rt] += rsum[rt<<1];
	msum[rt] = max(msum[rt], rsum[rt<<1]+lsum[rt<<1|1]);

	if(msum[rt]==m)   cover[rt] = 1;
	else if(msum[rt]==0)   cover[rt] = 0;
	else cover[rt] = -1;
}

void pushdown(int rt, int m){
	if(cover[rt]!=-1){
		cover[rt<<1] = cover[rt<<1|1] = cover[rt];

		sum[rt<<1] = cover[rt] * (m-(m>>1));
		sum[rt<<1|1] = cover[rt] * (m>>1);

		msum[rt<<1] = lsum[rt<<1] = rsum[rt<<1] = cover[rt]?m-(m>>1):0;
		msum[rt<<1|1] = lsum[rt<<1|1] = rsum[rt<<1|1] = cover[rt]?(m>>1):0;

		cover[rt] = -1;
	}
}

void build(int l, int r, int rt){
	if(l==r){
		scanf("%d", &sum[rt]);
		cover[rt] = msum[rt] = lsum[rt] = rsum[rt] = sum[rt];
		return ;
	}
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
	pushup(rt, r-l+1);
}

void update(int L, int R, int p, int l, int r, int rt){
	if(L<=l && r<=R){
		cover[rt] = p;
		sum[rt] = msum[rt] = lsum[rt] = rsum[rt] = p * (r-l+1);
		return ;
	}
	pushdown(rt, r-l+1);
	int m = (l + r) >> 1;
	if(L<=m)   update(L, R, p, lson);
	if(m<R)   update(L, R, p, rson);
	pushup(rt, r-l+1);
}

void updatex(int L, int R, int l, int r, int rt){
	if(L<=l && r<=R && cover[rt]!=-1){
		cover[rt] ^= 1;
		sum[rt] = msum[rt] = lsum[rt] = rsum[rt] = cover[rt] * (r-l+1);
		return ;
	}
	pushdown(rt, r-l+1);
	int m = (l + r) >> 1;
	if(L<=m)   updatex(L, R, lson);
	if(m<R)   updatex(L, R, rson);
	pushup(rt, r-l+1);
}

int query(int L, int R, int l, int r, int rt){
	if(L<=l && r<=R){
		return sum[rt];
	}
	pushdown(rt, r-l+1);
	int m = (l + r) >> 1 ;
	int ans = 0;
	if(L<=m)   ans += query(L, R, lson);
	if(m<R)   ans += query(L, R, rson);
	return ans;
}

int queryx(int L, int R, int l, int r, int rt){
	if(L<=l && r<=R){
		return msum[rt];
	}
	pushdown(rt, r-l+1);
	int m = (l + r) >> 1 ;
	if(R<=m){
		return queryx(L, R, lson);
	}
	if(L>m){
		return queryx(L, R, rson);
	}
	else{
		int ans = max(queryx(L, m, lson), queryx(m+1, R, rson));
		ans = max(ans, min(m-L+1, rsum[rt<<1])+min(R-m, lsum[rt<<1|1]));
		return ans;
	}
}

int main()
{
	freopen("data.in", "r", stdin);
	int tc;
	int n, m;
	int i;
	int op, a, b;

	scanf("%d", &tc);
	while(tc--){
		scanf("%d %d", &n, &m);
		build(1, n, 1);
		for(i=0; i<m; i++){
			scanf("%d %d %d", &op, &a, &b);
			if(op==0){
				update(a+1, b+1, 0, 1, n, 1);
			}
			else if(op==1){
				update(a+1, b+1, 1, 1, n, 1);
			}
			else if(op==2){
				updatex(a+1, b+1, 1, n, 1);
			}
			else if(op==3){
				printf("%d\n", query(a+1, b+1, 1, n, 1));
			}
			else{
				printf("%d\n", queryx(a+1, b+1, 1, n, 1));
			}
		}
	}

	return 0;
}
//*/


/*        968MS	12980K      	4396 B	C++
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#define MAXN 100005
#define eps 1e-11
#define L(x) x<<1
#define R(x) x<<1|1
#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b
using namespace std;
int a[MAXN];

struct node{
    int left, right, mid;
    int Cover, Xor, cnt;
    int lmx, rmx, mx;
    int lmx0, rmx0, mx0;
}tree[4 * MAXN];

void fun_xor(int C){
	// 处理标记
    if(tree[C].Cover != -1) tree[C].Cover ^= 1;
    else tree[C].Xor ^= 1;

	// 两个主要操作
	//  求和数组
    tree[C].cnt = tree[C].right - tree[C].left + 1 - tree[C].cnt;
	//  合并数组（6个）
    swap(tree[C].lmx, tree[C].lmx0);
    swap(tree[C].rmx, tree[C].rmx0);
    swap(tree[C].mx, tree[C].mx0);
}

void fun_cover(int p, int C){
	//  两个标记
    tree[C].Cover = p;
    tree[C].Xor = 0;

	//  两个主要操作
	//  求和数组
    tree[C].cnt = p ? tree[C].right - tree[C].left + 1 : 0;
	//  合并数组（6个）
    tree[C].lmx = tree[C].rmx = tree[C].mx = p ? tree[C].right - tree[C].left + 1 : 0;
    tree[C].lmx0 = tree[C].rmx0 = tree[C].mx0 = p ? 0 : tree[C].right - tree[C].left + 1;
}

void down(int C){
    if(tree[C].Cover != -1){
        fun_cover(tree[C].Cover, L(C));
        fun_cover(tree[C].Cover, R(C));
        tree[C].Cover = -1;
    }
    if(tree[C].Xor){
        fun_xor(L(C));
        fun_xor(R(C));
        tree[C].Xor = 0;
    }
}

void up(int C){
    tree[C].cnt = tree[L(C)].cnt + tree[R(C)].cnt;

	// 下面两部分是为了完成异或操作的
    tree[C].lmx = tree[L(C)].lmx;
    tree[C].rmx = tree[R(C)].rmx;
    if(tree[L(C)].lmx == tree[L(C)].right - tree[L(C)].left + 1) tree[C].lmx += tree[R(C)].lmx;
    if(tree[R(C)].rmx == tree[R(C)].right - tree[R(C)].left + 1) tree[C].rmx += tree[L(C)].rmx;
    tree[C].mx = max(tree[L(C)].rmx + tree[R(C)].lmx, max(tree[L(C)].mx, tree[R(C)].mx));

    tree[C].lmx0 = tree[L(C)].lmx0;
    tree[C].rmx0 = tree[R(C)].rmx0;
    if(tree[L(C)].lmx0 == tree[L(C)].right - tree[L(C)].left + 1) tree[C].lmx0 += tree[R(C)].lmx0;
    if(tree[R(C)].rmx0 == tree[R(C)].right - tree[R(C)].left + 1) tree[C].rmx0 += tree[L(C)].rmx0;
    tree[C].mx0 = max(tree[L(C)].rmx0 + tree[R(C)].lmx0, max(tree[L(C)].mx0, tree[R(C)].mx0));
}

void make_tree(int s, int e, int C){
    tree[C].left = s;
    tree[C].right = e;
    tree[C].mid = (s + e) >> 1;
    tree[C].Cover = -1;            // 覆盖标记
    tree[C].Xor = 0;               // 异或标记
    if(s == e){
        tree[C].cnt = a[s] ? 1 : 0;     
        tree[C].lmx = tree[C].rmx = tree[C].mx = a[s] ? 1 : 0;
        tree[C].lmx0 = tree[C].rmx0 = tree[C].mx0 = a[s] ? 0 : 1;    
        return;
    }
    make_tree(s, tree[C].mid, L(C));
    make_tree(tree[C].mid + 1, e, R(C));
    up(C);
}

void update(int s, int e, int op, int C){
    if(s <= tree[C].left && tree[C].right <= e){
        if(op < 2)
            fun_cover(op, C);
        else if(op == 2)
            fun_xor(C);
        return;
    }
    down(C);
    if(tree[C].mid >= s)    update(s, e, op, L(C));
    if(tree[C].mid < e)    update(s, e, op, R(C));
    up(C);
}

int query(int s, int e, int op, int C){
    if(s <= tree[C].left && tree[C].right <= e){
        if(op == 3) return tree[C].cnt;
        else if(op == 4) return tree[C].mx;
    }
    down(C);
    if(op == 3){
        int t = 0;
        if(tree[C].mid >= s) t += query(s, e, op, L(C));
        if(tree[C].mid < e) t += query(s, e, op, R(C));
        return t;
    }
    else{
        int t = 0;
        if(tree[C].mid >= s) t = max(t, query(s, e, op, L(C)));     // 在mid的左边有，进入
        if(tree[C].mid < e) t = max(t, query(s, e, op, R(C)));      // 在mid的右边有，进入
        t = max(t, min(tree[L(C)].rmx, tree[C].mid - s + 1) + min(tree[R(C)].lmx, e - tree[C].mid));
        return t;
    }
}

int main()
{
    int op, x, y;
    int T, n, m;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);

        make_tree(1, n, 1);

        while(m--){
            scanf("%d%d%d", &op, &x, &y);
            x++; y++;
            if(op <= 2) update(x, y, op, 1);
            else printf("%d\n", query(x, y, op, 1));
        }
    }
    return 0;
}
//*/









//*     1031MS	5416K	3606 B	C++             单“覆盖”标记
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 111111;
int sum[maxn<<2], llen1[maxn<<2], rlen1[maxn<<2], mlen1[maxn<<2];
int cov[maxn<<2];

void f_cov(int c, int l, int r, int rt)
{
    cov[rt] = c;
    sum[rt] = llen1[rt] = rlen1[rt] = mlen1[rt] = c ? r - l + 1 : 0;
}

void pushUp(int l, int r, int rt)
{
    int m = (l + r) >> 1;
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
    llen1[rt] = llen1[rt<<1];
    rlen1[rt] = rlen1[rt<<1|1];
    if (llen1[rt] == m - l + 1)
        llen1[rt] += llen1[rt<<1|1];
    if (rlen1[rt] == r - m)
        rlen1[rt] += rlen1[rt<<1];
    mlen1[rt] = max(rlen1[rt<<1] + llen1[rt<<1|1], max(mlen1[rt<<1], mlen1[rt<<1|1]));
}

void pushDown(int l, int r, int rt)
{
    if (cov[rt] != -1)
    {
        int m = (l + r) >> 1;
        f_cov(cov[rt], l, m, rt << 1);
        f_cov(cov[rt], m + 1, r, rt << 1 | 1);
        cov[rt] = -1;
    }
}

void build(int l, int r, int rt)
{
    cov[rt] = -1;
    if (l == r)
    {
        scanf("%d", &sum[rt]);
        cov[rt] = llen1[rt] = rlen1[rt] = mlen1[rt] = sum[rt];
        return ;
    }
    int m = (l + r) >> 1;
    build(l, m, rt << 1);
    build(m + 1, r, rt << 1 | 1);
    pushUp(l, r, rt);
}

void update_change(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        f_cov(c, l, r, rt);
        return ;
    }
    pushDown(l, r, rt);
    int m = (l + r) >> 1;
    if (L <= m) update_change(L, R, c, l, m, rt << 1);
    if (R > m) update_change(L, R, c, m + 1, r, rt << 1 | 1);
    pushUp(l, r, rt);
}

void update_xor(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        if (cov[rt] != -1)
        {
            cov[rt] ^= 1;
            sum[rt] = llen1[rt] = rlen1[rt] = mlen1[rt] = cov[rt] ? r - l + 1 : 0;
            return ;
        }
    }
    pushDown(l, r, rt);
    int m = (l + r) >> 1;
    if (L <= m) update_xor(L, R, l, m, rt << 1);
    if (R > m) update_xor(L, R, m + 1, r, rt << 1 | 1);
    pushUp(l, r, rt);
}

int query_sum(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return sum[rt];
    pushDown(l, r, rt);
    int m = (l + r) >> 1;
    int ret = 0;
    if (L <= m) ret += query_sum(L, R, l, m, rt << 1);
    if (R > m) ret += query_sum(L, R, m + 1, r, rt << 1 | 1);
    return ret;
}

int query_len(int L, int R, int l, int r, int rt)
{
    if (L == l && R == r)
        return mlen1[rt];
    pushDown(l, r, rt);
    int m = (l + r) >> 1;
    if (R <= m) return query_len(L, R, l, m, rt << 1);
    else if (L > m) return query_len(L, R, m + 1, r, rt << 1 | 1);
    else
    {
        int a = query_len(L, m, l, m, rt << 1);
        int b = query_len(m + 1, R, m + 1, r, rt << 1 | 1);
        int c = 0;
        c += min(rlen1[rt<<1], m - L + 1);
        c += min(llen1[rt<<1|1], R - m);

        return max(a, max(b, c));
    }
}

int main()
{
    int t, n, m;
    int op, a, b;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &n, &m);
        build(0, n - 1, 1);
        while (m--)
        {
            scanf("%d %d %d", &op, &a, &b);
            if (op == 0 || op == 1)
                update_change(a, b, op, 0, n - 1, 1);
            else if(op == 2)
                update_xor(a, b, 0, n - 1, 1);
            else if (op == 3)
                printf("%d\n", query_sum(a, b, 0, n - 1, 1));
            else printf("%d\n", query_len(a, b, 0, n - 1, 1));
        }
    }
    return 0;
}

//*/



/*    1156MS	9548K	      4058 B	C++    “覆盖”和“异或”双标记
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 111111;
int sum[maxn<<2], cov[maxn<<2], XOR[maxn<<2];
int llen1[maxn<<2], rlen1[maxn<<2], mlen1[maxn<<2];
int llen0[maxn<<2], rlen0[maxn<<2], mlen0[maxn<<2];

void f_cov(int c, int l, int r, int rt) // 覆盖操作
{
    cov[rt] = c;
    XOR[rt] = 0; // 覆盖时，异或标记直接清零
    sum[rt] = c ? r - l + 1 : 0;
    llen0[rt] = rlen0[rt] = mlen0[rt] = c ? 0 : r - l + 1;
    llen1[rt] = rlen1[rt] = mlen1[rt] = c ? r - l + 1 : 0;
}

void f_xor(int l, int r, int rt) // 异或操作
{
    if (cov[rt] != -1) cov[rt] ^= 1;
    else XOR[rt] ^= 1;
    sum[rt] = (r - l + 1) - sum[rt];
    swap(llen0[rt], llen1[rt]);
    swap(rlen0[rt], rlen1[rt]);
    swap(mlen0[rt], mlen1[rt]);
}

void pushUp(int l, int r, int rt)
{
    int m = (l + r) >> 1;
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];

    llen1[rt] = llen1[rt<<1];
    rlen1[rt] = rlen1[rt<<1|1];
    if (llen1[rt] == m - l + 1)
        llen1[rt] += llen1[rt<<1|1];
    if (rlen1[rt] == r - m)
        rlen1[rt] += rlen1[rt<<1];
    mlen1[rt] = max(rlen1[rt<<1] + llen1[rt<<1|1], max(mlen1[rt<<1], mlen1[rt<<1|1]));

    llen0[rt] = llen0[rt<<1];
    rlen0[rt] = rlen0[rt<<1|1];
    if (llen0[rt] == m - l + 1)
        llen0[rt] += llen0[rt<<1|1];
    if (rlen0[rt] == r - m)
        rlen0[rt] += rlen0[rt<<1];
    mlen0[rt] = max(rlen0[rt<<1] + llen0[rt<<1|1], max(mlen0[rt<<1], mlen0[rt<<1|1]));
}

void pushDown(int l, int r, int rt)
{
    int m = (l + r) >> 1;
    if (cov[rt] != -1)
    {
        f_cov(cov[rt], l, m, rt << 1);
        f_cov(cov[rt], m + 1, r, rt << 1 | 1);
        cov[rt] = -1;
    }
    if (XOR[rt])
    {
        f_xor(l, m, rt << 1);
        f_xor(m + 1, r, rt << 1 | 1);
        XOR[rt] = 0;
    }
}

void build(int l, int r, int rt)
{
    cov[rt] = -1;
    XOR[rt] = 0;
    if (l == r)
    {
        scanf("%d", &sum[rt]);
        cov[rt] = llen1[rt] = rlen1[rt] = mlen1[rt] = sum[rt];
        llen0[rt] = rlen0[rt] = mlen0[rt] = 1 - sum[rt];
        return ;
    }
    int m = (l + r) >> 1;
    build(l, m, rt << 1);
    build(m + 1, r, rt << 1 | 1);
    pushUp(l, r, rt);
}

void update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        if (c == 0 || c == 1)
            f_cov(c, l, r, rt);
        if (c == 2)
            f_xor(l, r, rt);
        return ;
    }
    pushDown(l, r, rt);
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, c, l, m, rt << 1);
    if (R > m) update(L, R, c, m + 1, r, rt << 1 | 1);
    pushUp(l, r, rt);
}

int query_sum(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return sum[rt];
    pushDown(l, r, rt);
    int m = (l + r) >> 1;
    int ret = 0;
    if (L <= m) ret += query_sum(L, R, l, m, rt << 1);
    if (R > m) ret += query_sum(L, R, m + 1, r, rt << 1 | 1);
    return ret;
}

int query_len(int L, int R, int l, int r, int rt)
{
    if (L == l && R == r)
        return mlen1[rt];
    pushDown(l, r, rt);
    int m = (l + r) >> 1;
    if (R <= m) return query_len(L, R, l, m, rt << 1);
    else if (L > m) return query_len(L, R, m + 1, r, rt << 1 | 1);
    else
    {
        int a = query_len(L, m, l, m, rt << 1);
        int b = query_len(m + 1, R, m + 1, r, rt << 1 | 1);
        int c = 0;
        c += min(rlen1[rt<<1], m - L + 1);
        c += min(llen1[rt<<1|1], R - m);

        return max(a, max(b, c));
    }
}

int main()
{
    int t, n, m;
    int op, a, b;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &n, &m);
        build(0, n - 1, 1);
        while (m--)
        {
            scanf("%d %d %d", &op, &a, &b);
            if (op <= 2)
                update(a, b, op, 0, n - 1, 1);
            else if (op == 3)
                printf("%d\n", query_sum(a, b, 0, n - 1, 1));
            else printf("%d\n", query_len(a, b, 0, n - 1, 1));
        }
    }
    return 0;
}

//*/


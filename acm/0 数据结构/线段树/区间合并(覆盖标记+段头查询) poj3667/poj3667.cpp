//*  2228K	625MS	C++	2022B
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

#define max(a, b) ((a)>(b)?(a):(b))

#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
 
const int maxn = 55555;
int lsum[maxn<<2];        // lsum[rt]��ʾ��m=(l+r)>>1�����������Ķ��ٸ���λ
int rsum[maxn<<2];
int msum[maxn<<2];        // msum[rt]��ʾ
int cover[maxn<<2];       // cover[i]==-1,�����ǻ�ɫ����δ��Ⱦɫ

// �ӱ��޸���������
void PushDown(int rt,int m) {
	if (cover[rt] != -1) {
		cover[rt<<1] = cover[rt<<1|1] = cover[rt];
		// ֻ�� ȫ0 �� ȫ1 �����
		msum[rt<<1] = lsum[rt<<1] = rsum[rt<<1] = cover[rt] ? 0 : m - (m >> 1);
		msum[rt<<1|1] = lsum[rt<<1|1] = rsum[rt<<1|1] = cover[rt] ? 0 : (m >> 1);
		cover[rt] = -1;                                                               // �����޸Ĺ��ķ�ס��, ������pushup��cover[rt] = -1����һ��
	}
}
// �ӱ��޸���������
void PushUp(int rt,int m) {  
	lsum[rt] = lsum[rt<<1];
	rsum[rt] = rsum[rt<<1|1];
	// ����˵����lsum rsum�п��ܴ��� msum
	if (lsum[rt] == m - (m >> 1)) lsum[rt] += lsum[rt<<1|1];                          //  lsum == rsum == msumʱ��֤����Ӧ��[l, r]���䶼����ֵΪ1
	if (rsum[rt] == (m >> 1)) rsum[rt] += rsum[rt<<1];
	msum[rt] = max(lsum[rt<<1|1] + rsum[rt<<1] , max(msum[rt<<1] , msum[rt<<1|1]));   // ȡ��ߡ��ұߡ�����+��������ֵ
	//cover[rt] = -1;                                                                 //   2228K	625MS	C++	2638B
}

void build(int l,int r,int rt) {
	msum[rt] = lsum[rt] = rsum[rt] = r - l + 1;
	cover[rt] = -1;
	if (l == r) return ;
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
}

void update(int L,int R,int c,int l,int r,int rt) {
	if (L <= l && r <= R) {
		msum[rt] = lsum[rt] = rsum[rt] = c ? 0 : r - l + 1;
		cover[rt] = c;
		return ;
	}
	PushDown(rt , r - l + 1);
	int m = (l + r) >> 1;
	if (L <= m) update(L , R , c , lson);
	if (m < R) update(L , R , c , rson);
	PushUp(rt , r - l + 1);
}

int query(int w,int l,int r,int rt) {
	//if (l == r){  return l;}       //    û����䣺  2228K	594MS	C++	2477B
	PushDown(rt , r - l + 1);
	int m = (l + r) >> 1;
	// ����ֻ������ѡ���ԭ���ǣ�ȷ����[l, r]������һ���д���w��һ��
	if (msum[rt<<1] >= w) 
		return query(w , lson);
	else if (rsum[rt<<1] + lsum[rt<<1|1] >= w)    // ��ߵ��� + �ұߵ���
		return m - rsum[rt<<1] + 1;               // �ؼ������ж����������
	return query(w , rson);
}

int main() 
{
	int n , m;
	scanf("%d%d",&n,&m);
	build(1 , n , 1);
	while (m --) {
		int op , a , b;
		scanf("%d",&op);
		if (op == 1) {
			scanf("%d",&a);
			if (msum[1] < a) puts("0");
			else { 
				int p = query(a , 1 , n , 1);             //  �����
				printf("%d\n",p);
				update(p , p + a - 1 , 1 , 1 , n , 1);    //  ������[p, p+a-1]����ֵ1
			}
		} 
		else {
			scanf("%d%d",&a,&b);
			update(a , a + b - 1 , 0 , 1 , n , 1);
		}
	}
	return 0;
}

/*
10 6
1 3
1 3
1 3
1 1
2 5 5
1 6

1
4
7
0
5

*/
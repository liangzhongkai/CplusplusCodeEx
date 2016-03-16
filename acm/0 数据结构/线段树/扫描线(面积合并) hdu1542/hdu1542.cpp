//   0ms   356k
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include<iostream>

using namespace std;

#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
 
const int maxn = 2222;
int cnt[maxn << 2];                           // ����Ϊ�Ĳ���߳����Ƿ�����������
double sum[maxn << 2];                        // �����˵�֮��ĳ���
double X[maxn];                               // �ײ�������������ȣ���������sum[]��

struct Seg{
	double h , l , r;
	int s;
	Seg(){}
	Seg(double a,double b,double c,int d) : l(a) , r(b) , h(c) , s(d) {}
	bool operator < (const Seg &cmp) const {
		return h < cmp.h;
	}
}ss[maxn];

// ��������������²� ���� �ϲ�  �Ĵ���
// ���и��²��зֶ�  0 �� ��0  �Ĵ���
void PushUp(int rt,int l,int r) {
	if (cnt[rt]) sum[rt] = X[r+1] - X[l];      // �������䳤�ȡ�����ǵ㣬�Ǿ�������һ����(����������)�ľ���
	else if (l == r) sum[rt] = 0;              // ����1ʱ����Ͳ㱻��Ϊ0ʱ����������
	else sum[rt] = sum[rt<<1] + sum[rt<<1|1];  // ����ȫ����������ϲ㲿��
}

void update(int L,int R,int c,int l,int r,int rt) {
	if (L <= l && r <= R) {
		cnt[rt] += c;
		PushUp(rt , l , r);
		return ;
	}
	int m = (l + r) >> 1;
	if (L <= m)   update(L , R , c , lson);
	if (m < R)   update(L , R , c , rson);
	PushUp(rt , l , r);
}

// ��X[]��[0, k)��Χ����key�����к�
int Bin(double key,int n,double X[]) {
	int l = 0 , r = n - 1;
	while (l <= r) {
		int m = (l + r) >> 1;
		if (X[m] == key) return m;
		if (X[m] < key) l = m + 1;
		else r = m - 1;
	}
	return -1;
}

int main() {
	freopen("in.txt", "r", stdin);
	int n , i, cas = 1;
	while (~scanf("%d",&n) && n) {
		int m = 0;
		while (n --) {
			double a , b , c , d;
			scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
			X[m] = a;
			ss[m++] = Seg(a , c , b , 1);
			X[m] = c;
			ss[m++] = Seg(a , c , d , -1);
		}

		sort(X , X + m);
		sort(ss , ss + m);

		// ��������ɢ��
		int k = 1;
		for (i = 1 ; i < m ; i ++) {
			if (X[i] != X[i-1]) X[k++] = X[i];
		}

		//for (i = 0 ; i < m ; i ++) {
		//	cout << ss[i].l << " " << ss[i].r << endl;
		//}

		memset(cnt , 0 , sizeof(cnt));
		memset(sum , 0 , sizeof(sum));
		double ret = 0;
		for (i = 0 ; i < m - 1 ; i ++) {
			//cout << "**";
			int l = Bin(ss[i].l , k , X);        // ss[i].l�ǵ�i�����ε��������
			int r = Bin(ss[i].r , k , X) - 1;    // ss[i].r�ǵ�i�����ε��Һ�����
			//cout << l << " " << r << " " << ss[i].l << " " << ss[i].r << " " << ss[i].s << endl;
			if (l <= r)   update(l , r , ss[i].s , 0 , k - 1, 1);
			ret += sum[1] * (ss[i+1].h - ss[i].h);
			//  ����߾��ηֳ�һ��һ���
			//cout << sum[1] * (ss[i+1].h - ss[i].h) << " " << sum[1] << " " << ss[i+1].h << " " << ss[i].h << endl;  
		}
		printf("Test case #%d\nTotal explored area: %.2lf\n\n", cas++ , ret);
	}
	return 0;
}
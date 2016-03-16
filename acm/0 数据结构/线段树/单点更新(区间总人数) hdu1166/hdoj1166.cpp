//*  93MS	792K	1337 B	C++
#include<iostream>
#include<cstdio>

using namespace std;

#define lson l,   m, rt<<1
#define rson m+1, r, rt<<1|1

const int N = 55555;
int sum[N<<2];

void pushup(int rt)
{
	sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}

void build(int l, int r, int rt)
{
	if(l==r)
	{
		scanf("%d", &sum[rt]);
		return ;
	}
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
	pushup(rt);
}

void update(int p, int add, int l, int r, int rt)
{
	if(l==r)
	{
		sum[rt] += add;
		return ;
	}
	int m = (l + r) >> 1;
	if(p<=m)
		update(p, add, lson);
	else
		update(p, add, rson);
	pushup(rt);
}

int query(int L, int R, int l, int r, int rt)
{
	if(l>=L && r<=R)
	{
		return sum[rt];
	}
	int m = (l + r) >> 1;
	int ans = 0;
	if(L<=m)
		ans += query(L, R, lson);
	if(R>m)
		ans += query(L, R, rson);
	return ans;

}

int main()
{
	int tc, n;
	int a, b;
	int cnt = 1;
	char temp[10];

	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d", &n);
		build(1, n, 1);

		printf("Case %d:\n", cnt);
		while(scanf("%s", temp)==1 && temp[0]!='E')
		{
			scanf("%d%d", &a, &b);
			if(temp[0]=='Q')
			{
				cout << query(a, b, 1, n, 1) << endl;
			}
			else if(temp[0]=='A')
			{
				update(a, b, 1, n, 1);
			}
			else
			{
				update(a, -b, 1, n, 1);
			}
		}
		cnt++;
	}

	return 0;
}
//*/



/*          46MS	744K	1667 B	C++
#include <cstdio>

#define lson l , m , rt << 1             // 3���������һ������
#define rson m + 1 , r , rt << 1 | 1

const int maxn = 55555;
int sum[maxn<<2];                        // �߶�������Ҫ��4��

void PushUP(int rt) 
{
	sum[rt] = sum[rt<<1] + sum[rt<<1|1]; // 2*rt �� 2*rt+1
}

void build(int l,int r,int rt) 
{
	if (l == r) 
	{
		scanf("%d",&sum[rt]);
		return ;
	}
	int m = (l + r) >> 1;  // l r m ���Ǳ�ʾ��������±꣬��ʾ�ڼ���Ԫ��
	build(lson);
	build(rson);
	PushUP(rt);
}

void update(int p,int add,int l,int r,int rt) 
{
	if (l == r) 
	{
		sum[rt] += add;
		return ;
	}
	int m = (l + r) >> 1;
	if (p <= m)
		update(p , add , lson);// p m r l �����þ��� �Ӹ���λ��Ҷ���ϣ���ʾ��������ĵڼ���Ԫ��
	else                       //      rt �����þ��� ȷ���±�
		update(p , add , rson);  
	PushUP(rt);
}

int query(int L,int R,int l,int r,int rt)
{
	if (L <= l && r <= R)
	{
		return sum[rt];
	}
	int m = (l + r) >> 1;
	int ret = 0;
	if (L <= m)
		ret += query(L , R , lson);
	if (R > m)
		ret += query(L , R , rson);
	return ret;
}

int main() 
{
	int T , n;
	scanf("%d",&T);
	for (int cas = 1 ; cas <= T ; cas ++) 
	{
		printf("Case %d:\n",cas);
		scanf("%d",&n);
		build(1 , n , 1);
		//for(int i=0; i<30; i++)
		//	printf("%d\n", sum[i]);
		char op[10];
		while (scanf("%s",op)) 
		{
			if (op[0] == 'E') break;
			int a , b;
			scanf("%d%d",&a,&b);
			if (op[0] == 'Q')
				printf("%d\n",query(a , b , 1 , n , 1));
			else if (op[0] == 'S')
				update(a , -b , 1 , n , 1);  // ��1~n�����ȥ�ҵ�a��ʵ�ּ�ȥb
			else
				update(a , b , 1 , n , 1);
		}
	}
	return 0;
}
//*/


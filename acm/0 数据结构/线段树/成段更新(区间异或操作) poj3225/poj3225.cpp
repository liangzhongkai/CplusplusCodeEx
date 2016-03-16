/*
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1

const int N = 131080;
int col[N<<2];
int flag;

void pushdown(int rt, int m){
	if(col[rt]!=-1){
		col[rt<<1] = col[rt<<1|1] = col[rt];
		col[rt] = -1;
	}
}

void update(char op, int L, int R, int l, int r, int rt){
	if(L<=l && r<=R){
		if (op == 'U') {                    // U:������[L,R]���ǳ�1
			col[rt] = 1;
		} 
		else if (op == 'D') {               // D:������[L,R]���ǳ�0
			col[rt] = 0;
		} 
		else if (op == 'C' || op == 'S') {  // [L,R]����0/1�����������������Ҫ���嵽�ײ�ĵ㣿���������XOR������ֵ�ԭ��
			col[rt] = 1->0;   0->1;
			if == -1,  �ݹ���ȥ��
		}
		return ;
	}
	pushdown(rt);

	int m = (l + r) >> 1;
	if(L<=m)   update(L, R, f, lson);
	else if(op=='I' || op=='C')  col[rt<<1] = 0;

	if(m<R)   update(L, R, f, rson);
	else if(op=='I' || op=='C')  col[rt<<1] = 0;
}


int find(int a, int l, int r, int rt){
	if(l==r){
		return rt;
	}
	int m = 
}

int main()
{
	char ch, l, r, m;
	int a, b;

	memset(col, 0, sizeof(col));

	while(scanf("%c %c%d%c%d%c", &ch, &l, &a, &m, &b, &r)!=EOF){
		if(l=='[')   a = a*2-1;
		else   a = a<<1;
		if(r==']')   b = b*2-1;
		else   b = b*2-2;
		getchar();
		if(ch=='U'){
			update(a, b, 1, 1, n, 1);
		}
		else if(ch=='I'){
			update(1, a-1, 0, 1, n, 1);
			update(b+1, n, 0, 1, n, 1);
		}
		else if(ch=='D'){
			update(a, b, 0, 1, n, 1);
		}
		else if(ch=='C'){
			update(1, a-1, 0, 1, n, 1);
			update(b+1, n, 0, 1, n, 1);
			exchange(a, b, 1, n, 1);
		}
		else{
			exchange(a, b, 1, n, 1);
		}
	}

	

	return 0;
}
//*/

//*      2356K	907MS	C++	2157B
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
 
const int maxn = 131072;
bool hash[maxn+1];
int cover[maxn<<2];   //  ��0��1��ʾ�Ƿ��������,-1��ʾ�������ڼ��а������в�����
int XOR[maxn<<2];     //  0��û������� ��1���������

void FXOR(int rt) {
	if (cover[rt] != -1) cover[rt] ^= 1;   // ����ǵײ�����ĵ㣬��ô�϶�������-1
	else XOR[rt] ^= 1;                     // �ı�rtλ�õ�������
}

void PushDown(int rt) {
	if (cover[rt] != -1) {
		cover[rt<<1] = cover[rt<<1|1] = cover[rt];
		XOR[rt<<1] = XOR[rt<<1|1] = 0;
		cover[rt] = -1;
	}
	if (XOR[rt]) {
		FXOR(rt<<1);
		FXOR(rt<<1|1);
		XOR[rt] = 0;
	}
}

void update(char op,int L,int R,int l,int r,int rt) {
	if (L <= l && r <= R) {
		if (op == 'U') {                    // U:������[L,R]���ǳ�1
			cover[rt] = 1;
			XOR[rt] = 0;
		} 
		else if (op == 'D') {               // D:������[L,R]���ǳ�0
			cover[rt] = 0;
			XOR[rt] = 0;
		} 
		else if (op == 'C' || op == 'S') {  // [L,R]����0/1����
			FXOR(rt); 
		}
		return ;
	}
	PushDown(rt);
	int m = (l + r) >> 1;

	if (L <= m) update(op , L , R , lson);
	else if (op == 'I' || op == 'C') {      // ��[-��,L)(R,��]���ǳ�0
		XOR[rt<<1] = cover[rt<<1] = 0;
	}

	if (m < R) update(op , L , R , rson);
	else if (op == 'I' || op == 'C') {
		XOR[rt<<1|1] = cover[rt<<1|1] = 0;
	}
}

void query(int l,int r,int rt) {
	if (cover[rt] == 1) {
		for (int it = l ; it <= r ; it ++) {
			hash[it] = true;
		}
		return ;
	} 
	else if (cover[rt] == 0) return ;

	if (l == r) return ;

	PushDown(rt);
	int m = (l + r) >> 1;
	query(lson);
	query(rson);
}

int main() 
{
	freopen("in.txt", "r", stdin);
	cover[1] = XOR[1] = 0;
	char op , l , r;
	int a , b;
	while ( ~scanf("%c %c%d,%d%c\n",&op , &l , &a , &b , &r) ) {
		a <<= 1 , b <<= 1;
		if (l == '(') a ++;
		if (r == ')') b --;
		if (a > b) {
			if (op == 'C' || op == 'I')
				cover[1] = XOR[1] = 0;
		} 
		else
			update(op , a , b , 0 , maxn , 1);
	}

	query(0 , maxn , 1);    // ��һ��hash����ѵײ����������װ������������Ƿ񱻸���

	bool flag = false;
	int s = -1 , e;
	for (int i = 0 ; i <= maxn ; i ++) {
		if (hash[i]) {
			if (s == -1) s = i;
			e = i;
		} 
		else {
			if (s != -1) {
				if (flag) printf(" ");
				flag = true;
				printf("%c%d,%d%c",s&1?'(':'[' , s>>1 , (e+1)>>1 , e&1?')':']');
				s = -1;
			}
		}
	}
	if (!flag) printf("empty set");
	puts("");  // ��ӡһ�У�����ʲô��û�� == \n
	return 0;
}
//*/
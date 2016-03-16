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
		if (op == 'U') {                    // U:把区间[L,R]覆盖成1
			col[rt] = 1;
		} 
		else if (op == 'D') {               // D:把区间[L,R]覆盖成0
			col[rt] = 0;
		} 
		else if (op == 'C' || op == 'S') {  // [L,R]区间0/1互换：这个操作不是要具体到底层的点？可能这就是XOR数组出现的原因
			col[rt] = 1->0;   0->1;
			if == -1,  递归下去将
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
int cover[maxn<<2];   //  用0和1表示是否包含区间,-1表示该区间内既有包含又有不包含
int XOR[maxn<<2];     //  0：没有异或标记 ，1：有异或标记

void FXOR(int rt) {
	if (cover[rt] != -1) cover[rt] ^= 1;   // 如果是底层区间的点，那么肯定不等于-1
	else XOR[rt] ^= 1;                     // 改变rt位置的异或情况
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
		if (op == 'U') {                    // U:把区间[L,R]覆盖成1
			cover[rt] = 1;
			XOR[rt] = 0;
		} 
		else if (op == 'D') {               // D:把区间[L,R]覆盖成0
			cover[rt] = 0;
			XOR[rt] = 0;
		} 
		else if (op == 'C' || op == 'S') {  // [L,R]区间0/1互换
			FXOR(rt); 
		}
		return ;
	}
	PushDown(rt);
	int m = (l + r) >> 1;

	if (L <= m) update(op , L , R , lson);
	else if (op == 'I' || op == 'C') {      // 把[-∞,L)(R,∞]覆盖成0
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

	query(0 , maxn , 1);    // 用一个hash数组把底层的区间序列装起来，并标记是否被覆盖

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
	puts("");  // 打印一行，里面什么都没有 == \n
	return 0;
}
//*/
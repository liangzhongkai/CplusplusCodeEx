//*   5448K	375MS	C++	762B
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>

using namespace std;

#define M 100000

int list[M];
int stack[M*10];
char ans[M*10];
int s, a;   // 两个栈的指针

void search(int v, int m){    // 从n-1位数状态v出发，一直走边，走到尽头为止，   但是如何做到最小序的？
	int w;
	//cout << list[v] << "***" << v << "***";
	while(list[v]<10){        // 10条边，由n-1位数状态 v 之间互连
		w = v*10 + list[v];
		list[v]++;            // 每一个n-1位数状态v发出去的边是按照从小到大的顺序的。
		stack[s++] = w;       // n位数状态 = n-1位数状态 + 边(list[v])
		cout << list[v] << " " << v << "   ";
		v = w%m;              // 析出：这个由v出发的，边是list[v]到达的n-1位数状态
	}
	cout << "*" << list[v] ;
	//cout << s << " ";
}

int main()
{
	int n, m, i, v;
	while(scanf("%d", &n) && n!=0){
		if(n==1){
			printf("0123456789\n");
			continue;
		}

		s = a = v = 0;
		m = pow(10.0, double(n-1));   // n-1位的状态，只要再加一位，就转化为其他的状态，m表示为n-1位状态的个数，走完所有边一次的回路就是答案
		for(i=0; i<m; i++){
			list[i] = 0;
		}
		search(v, m);

		while(s){
			v = stack[--s];  ans[a++] =  v%10 + '0';
			v /= 10;
			search(v, m);
		}

		for(i=1; i<n; i++)   printf("0");
		while(a)   printf("%c", ans[--a]);
		printf("\n");
	}

	return 0;
}
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
int s, a;   // ����ջ��ָ��

void search(int v, int m){    // ��n-1λ��״̬v������һֱ�߱ߣ��ߵ���ͷΪֹ��   �������������С��ģ�
	int w;
	//cout << list[v] << "***" << v << "***";
	while(list[v]<10){        // 10���ߣ���n-1λ��״̬ v ֮�以��
		w = v*10 + list[v];
		list[v]++;            // ÿһ��n-1λ��״̬v����ȥ�ı��ǰ��մ�С�����˳��ġ�
		stack[s++] = w;       // nλ��״̬ = n-1λ��״̬ + ��(list[v])
		cout << list[v] << " " << v << "   ";
		v = w%m;              // �����������v�����ģ�����list[v]�����n-1λ��״̬
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
		m = pow(10.0, double(n-1));   // n-1λ��״̬��ֻҪ�ټ�һλ����ת��Ϊ������״̬��m��ʾΪn-1λ״̬�ĸ������������б�һ�εĻ�·���Ǵ�
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
/*
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 30010;
int a[N];
int u[N];
int heap[2][N];
int hlen[2];

bool kctless(const int& s, const int& t){
	return s>t;
}
bool kctgreater(const int& s, const int& t){
	return s<t;
}
void insert(int t, int k){ 
	heap[k][hlen[k]++] = t;
	if(k==0)  // ������С��
		push_heap(heap[k], heap[k]+hlen[k], kctless);
	else      // ��������
		push_heap(heap[k], heap[k]+hlen[k], kctgreater);
}
void remove(int k){
	if(k==0)  // Ԫ������
		pop_heap(heap[k], heap[k]+hlen[k]--, kctless);
	else
		pop_heap(heap[k], heap[k]+hlen[k]--, kctgreater);
}


int main()
{
	int n, m;
	int i, j;

	scanf("%d%d", &n, &m);
	for(i=0; i<n; i++)
		scanf("%d", a+i);
	for(i=0; i<m; i++)
		scanf("%d", u+i);

	j = 1;
	hlen[0] = 0;   // ��С��   
	hlen[1] = 0;   // ���ѣ�װ��С��ǰn����
	int tmp = 0;
	for(i=1; i<=m; i++){
		for(; j<=u[i-1]; j++){
			//printf("%d ", a[j-1]);
			if(hlen[1]==0){
				insert(a[j-1], 1);
			}
			else if(heap[1][0]>a[j-1]){
				tmp = heap[1][0];
				remove(1);
				insert(a[j-1], 1);
				if(hlen[1]<i)
					insert(tmp, 1);
				else
					insert(tmp, 0);
			}
			else if(heap[0][0]<a[j-1]){
				tmp = heap[0][0];
				remove(0);
				insert(a[j-1], 0);
				if(hlen[1]<i)
					insert(tmp, 1);
				else
					insert(tmp, 0);
			}
			else{
				if(hlen[1]<i)
					insert(a[j-1], 1);
				else
					insert(a[j-1], 0);
			}
		}
		while(hlen[1]<i){
			tmp = heap[0][0];
			remove(0);
			insert(tmp, 1);
		}
		//printf("\n");
		// debug �����ѵ����
		//printf("***%d\n", i);
		//printf("xiao:");
		//for(int k=0; k<hlen[0]; k++)
		//	 printf("%d ", heap[0][k]);
		//printf("\n");
		//printf("da:");
		//for(k=0; k<hlen[1]; k++)
		//	 printf("%d ", heap[1][k]);
		//printf("\n");
		printf("%d\n", heap[1][0]);
	}

	return 0;
}
//*/



//      528K	125MS	C++	1280B
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 30010;
int a[N];
int u[N];
int heap[2][N];
int hlen[2];

bool kctless(const int& s, const int& t){
	return s>t;
}
bool kctgreater(const int& s, const int& t){
	return s<t;
}
void insert(int t, int k){ 
	heap[k][hlen[k]++] = t;
	if(k==0)  // ������С��
		push_heap(heap[k], heap[k]+hlen[k], kctless);
	else      // ��������
		push_heap(heap[k], heap[k]+hlen[k], kctgreater);
}
void remove(int k){
	if(k==0)  // Ԫ������
		pop_heap(heap[k], heap[k]+hlen[k]--, kctless);
	else
		pop_heap(heap[k], heap[k]+hlen[k]--, kctgreater);
}


int main()
{
	int n, m;
	int i, j;

	scanf("%d%d", &n, &m);
	for(i=0; i<n; i++)
		scanf("%d", a+i);
	for(i=0; i<m; i++)
		scanf("%d", u+i);

	j = 1;
	hlen[0] = 0;   // ��С��   
	hlen[1] = 0;   // ���ѣ�װ��С��ǰn����
	int tmp = 0;
	int temp = 0;
	for(i=1; i<=m; i++){
		for(; j<=u[i-1]; j++){
			insert(a[j-1], 0);
		}
		while(hlen[1]<i){
			tmp = heap[0][0];
			remove(0);
			insert(tmp, 1);
		}
		while(hlen[0]>0 && hlen[1]>0 && heap[0][0]<heap[1][0]){
			tmp = heap[0][0];
			temp = heap[1][0];
			remove(0);  remove(1);
			insert(temp, 0);  insert(tmp, 1);
		}
		printf("%d\n", heap[1][0]);
	}

	return 0;
}
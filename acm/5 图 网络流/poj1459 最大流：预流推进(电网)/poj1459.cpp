//   416K	204MS	C++	2031B
#include<iostream>
#include<cstdio>
#include<deque>
#include<cstring>

using namespace std;

const int N = 105;
const int F = 0x7fffffff;
int n, np, nc, m;
int resi[N][N]; // ��������
deque<int> act; // ��Ծ�������
int h[N];       // �߶� 
int ef[N];      // ӯ�� 
int s, t;       // Դ���
int V;          // ��������

void push_ralabel(){
	int i;
	int sum = 0;
	int u, v, p;

	for(i=1; i<=V; i++){
		h[i] = 0;
	}
	h[s] = V;
	memset(ef, 0, sizeof(ef));
	ef[s] = F;   ef[t] = -F;
	act.push_front(s);
	printf("%d %d\n", s, t);
	
	while(!act.empty()){
		u = act.back();
		act.pop_back();
		for(i=1; i<=V; i++){
			v = i;
			if(resi[u][v]<ef[u]){  // ������ӽڵ�Ƚϣ�ef[u]Խ��ԽС 
				p = resi[u][v];
				/*
				if(u==s || h[u]==h[v]+1){
					printf("%d\n", p);
				}
				*/
			}
			else{
				p = ef[u];
				/*
				if(u==s || h[u]==h[v]+1){
					printf("%d\n", p);
				}
				*/
			}
			if(p>0 && (u==s || h[u]==h[v]+1)){
				resi[u][v] -= p;   resi[v][u] += p;
				if(v==t)   sum += p;
				ef[u] -= p;   ef[v] += p;
				if(v!=s && v!=t){
					act.push_front(v);    // ������ǰͷ����
				}
				/*
				printf("***%d    %d\n", h[u], h[v]);
				for(i=1; i<=V; i++){
					printf("%d  ", ef[i]);   
				}
				printf("\n");
				*/
			}
		}
		if(u!=s && u!=t && ef[u]>0){
			h[u]++;
			act.push_front(u);
		}
	}

	//                       << ���� >>
	//                         <<һ>>
	// ���ø߶ȵ�Ŀ�ģ���Ϊ����ĳ��<u,v>��һ���ƽ��Ѿ���u�����ƽ�
	// �������ƽ��ˣ���Ϊ��ӵĽڵ�߶ȶ�Ҫ�ͣ�����������һֱ����
	// ���������t�㣬��Щ������t��Ļ᷵������s�㡣
	//                         <<��>>
	// ������е��ƽ���������s��t���㣬���õ����������s,t����ʱ��
	// �߻���������Ϊ��������������������Ǿ�����s���ӵı������ƣ�
	// ����һ����������s�㣬���е�����������s�󣬾ʹ���û�л�Ծ��
	// �㣬���˳�ѭ����
/*
	for(i=1; i<=V; i++){
		printf("%d  ", ef[i]);   // �������⣬ȫ��������0
	}
	printf("\n");
*/
	printf("%d\n", sum);
}

int main()
{
	int i;
	int u, v, val;
	// ��ͼ
	while(scanf("%d %d %d %d", &n, &np, &nc, &m)!=EOF){
		s = n + 1;   t = n + 2;   V = n + 2;
		memset(resi, 0, sizeof(resi));

		// �м�ڵ�ı�
		for(i=0; i<m; i++){
			while(getchar()!='(')   ;
			scanf("%d,%d)%d", &u, &v, &val);
			resi[u+1][v+1] = val;
		}

		// Դ����ڵ�ı�
		for(i=0; i<np; i++){
			while(getchar()!='(')   ;
			scanf("%d)%d", &u, &val);
			resi[s][u+1] = val;
		}

		// �ڵ�����ı�
		for(i=0; i<nc; i++){
			while(getchar()!='(')   ;
			scanf("%d)%d", &u, &val);
			resi[u+1][t] = val;
		}

		// Ԥ���ƽ��㷨
		push_ralabel();
	}

	return 0;
}

/*
2 1 1 2 (0,1)20 (1,0)10 (0)15 (1)20
7 2 3 13 (0,0)1 (0,1)2 (0,2)5 (1,0)1 (1,2)8 (2,3)1 (2,4)7
         (3,5)2 (3,6)5 (4,2)7 (4,3)5 (4,5)1 (6,0)5
         (0)5 (1)2 (3)2 (4)1 (5)4
2 1 1 2 (0,1)20 (1,0)10 (0)15 (1)10
7 2 3 13 (0,0)1 (0,1)2 (0,2)5 (1,0)1 (1,2)8 (2,3)1 (2,4)7
         (3,5)2 (3,6)5 (4,2)7 (4,3)5 (4,5)1 (6,0)5
         (0)5 (1)2 (3)2 (4)1 (5)4
*/
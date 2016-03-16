/*
#include<iostream>

using namespace std;

int main()
{
	int tc;
	int n, t;
	int i;
	int x1, y1, x2, y2;
	char inst;

	cin >> tc;

	while(tc--){
		cin >> n >> t;
		for(i=0; i<t; i++){
			cin >> inst;
			if(inst=='C'){
				cin >> x1 >> y1 >> x2 >> y2;
			}
			else{
				cin >> x1 >> y1;
			}
		}
	}

	return 0;
}
//*/


/*
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

using namespace std;
 
#define maxn 1005
 
int c[maxn][maxn];
int Row, Col;
 
inline int Lowbit(const int &x){
    return x & (-x);
}
int Sum(int i, int j){
    int tempj, sum = 0;
    while (i > 0){
        tempj = j;
        while (tempj > 0){
            sum += c[i][tempj];
            tempj -= Lowbit(tempj);
        }
        i -= Lowbit(i);
    }
    return sum;
}
void Update(int i, int j, int num){
    int tempj;
    while (i <= Row){
        tempj = j;
        while (tempj <= Col){
            c[i][tempj] += num;
            tempj += Lowbit(tempj);
        }
        i += Lowbit(i);
    }
}
int main()
{
//  freopen("t.txt", "r", stdin);
    int x, n, t;
	int j, k;
    scanf("%d", &x);
    while (x--)
    {
        memset(c, 0, sizeof(c));
        scanf("%d%d", &n, &t);
        getchar();
        Row = n;
        Col = n;
        for (int i = 0; i < t; i++){
            char ch;
            int x1, x2, y2, y1;
            scanf("%c", &ch);
            if (ch == 'C'){
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                x2++;
                y2++;
                Update(x1, y1, 1);
				//for(j=1; j<=4; j++){
				//	for(k=1; k<=4; k++){
				//		 cout << c[j][k] << " ";
				//	}
				//	cout << endl;
				//}
				//cout << "*************************" << endl;
                Update(x1, y2, -1);
				//for(j=1; j<=4; j++){
				//	for(k=1; k<=4; k++){
				//		 cout << c[j][k] << " ";
				//	}
				//	cout << endl;
				//}
				//cout << "*************************" << endl;
                Update(x2, y1, -1);
				//for(j=1; j<=4; j++){
				//	for(k=1; k<=4; k++){
				//		 cout << c[j][k] << " ";
				//	}
				//	cout << endl;
				//}
				//cout << "*************************" << endl;
                Update(x2, y2, 1);
				//for(j=1; j<=4; j++){
				//	for(k=1; k<=4; k++){
				//		 cout << c[j][k] << " ";
				//	}
				//	cout << endl;
				//}
				//cout << "*************************" << endl;
            }
            else{
                scanf("%d%d", &x1, &y1);
				// �鿴(x1,y1)�����Ͼ��󱻶��˶��ٴΣ�
				// �����һ�β鿴ʱ��(1,1)��ߵ������޸Ĺ����Σ���������Ϊ1
                printf("%d\n", Sum(x1, y1));  // (1 & Sum(x1, y1))
            }
            getchar();
        }
        printf("\n");
    }
    return 0;
}
//*/
/*
2
2 10
C 2 1 2 2
Q 2 2
C 2 1 2 1
Q 1 1
C 1 1 2 1
C 1 2 1 2
C 1 1 2 2
Q 1 1
C 1 1 2 1
Q 2 1

1
4 3
C 1 1 3 2
C 2 3 4 4
Q 2 3

*/



/*    ����֮��
#include<iostream>
using namespace std;
#define H 5
#define L 5
int c[H][L];
int lowbit (int t){
	return t&(-t);
}
int sum(int x, int y){
	int ans = 0;
	for(int i=x; i>0; i-=lowbit(i)){
		for(int j=y; j>0; j-=lowbit(j)){
			ans += c[i][j];
		}
	}
	return ans;
}
void add(int x, int y, int num){
	for(int i=x; i<H; i+=lowbit(i)){   // ע�⣺����i<H,����ΪH������ı߽�
		for(int j=y; j<L; j+=lowbit(j)){
			c[i][j] += num;
		}
	}
}
int getsum(int l,int d,int r,int g){     // l����r���ң�g���ߣ�d����
    return sum(r,g) - sum(r,d-1) - sum(l-1,g) + sum(l-1,d-1);  
}
int main()
{
	int i, j;
	memset(c, 0,sizeof(c));
	add(1, 1, 1);
	add(3, 1, -1);
	add(1, 3, -1);
	add(3, 3, 1);
	
	for(i=1; i<H; i++){
		for(j=1; j<L; j++){
			cout << c[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for(i=1; i<H; i++){
		for(j=1; j<L; j++){
			cout << sum(i, j) << " ";  // ����߳�Ϊ2����ĵ������
		}
		cout << endl;
	}
	return 0;
}
//*/
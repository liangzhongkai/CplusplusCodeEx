//  240K	16MS	C++	1002B
#include<iostream>

using namespace std;

int a[20][20], b[20][20];
int d[16];

void change(){
	int i, j;
	int sum;
	for(i=0; i<20; i++){
		for(j=0; j<20; j++){
			sum = a[i][j];
			if(i-1>=0) sum += a[i-1][j];
			if(j-1>=0) sum += a[i][j-1];
			if(i+1<20) sum += a[i+1][j];
			if(j+1<20) sum += a[i][j+1];
			b[i][j] = sum;
		}
	}
}

void add(){
	int i, j;
	for(i=0; i<20; i++){
		for(j=0; j<20; j++){
			a[i][j] += d[b[i][j]];
			if(a[i][j]>3) a[i][j] = 3;
			else if(a[i][j]<0) a[i][j] = 0;
		}
	}
}

int main()
{
	int n;
	int i, j;
	
	cin >> n;
	for(i=0; i<16; i++)
		cin >> d[i];

	for(i=0; i<20; i++){
		for(j=0; j<20; j++){
			cin >> a[i][j];
		}
	}

	while(n--){
		change();
		add();
	}

	for(i=0; i<20; i++){
		for(j=0; j<20; j++){
			if(a[i][j]==0)
				cout << ".";
			else if(a[i][j]==1)
				cout << "!";
			else if(a[i][j]==2)
				cout << "X";
			else if(a[i][j]==3)
				cout << "#";
		}
		cout << endl;
	}


	return 0;
}
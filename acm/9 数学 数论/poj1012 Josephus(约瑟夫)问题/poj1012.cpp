//   打表之后   204K	235MS	C++	536B
#include<iostream>
#include<fstream>
using namespace std;
/*
ifstream  fin("data.txt");
#define  cin  fin 
//*/
int n;

int main()
{
	int f[15]; 
	int i;
	for(n=1; n<14; n++){
		int m = n+1;
		while(1){
			int s = 0;
			int k = 0;
			for(i=0; i<n; i++){
				s = (s+m-1)%(2*n-i);
				if(s<n){
					k = 1;
					break;
				}
			}
			if(k==1){
				m++;   //   Time Limit Exceeded
			}
			else{
				f[n] = m;
				break;
			}
		}
	}
	while(cin >> n && n!=0){
		cout << f[n] << endl;
	}
	return 0;
}

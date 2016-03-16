//  248K	16MS	C++	647B
#include<iostream>

using namespace std;

int a[25];
int b[25];

int main()
{
	int tc;
	int n, i, j, cnt;
	int ans[25];
	
	cin >> tc;

	while(tc--){
		cin >> n;
		a[0] = 0;
		for(i=1; i<=n; i++){
			cin >> a[i];
		}
		for(i=1; i<=n; i++){
			b[i] = a[i] - a[i-1]; // b[i]表示第i个右括号前有b[i]个左括号
		}
		
		for(i=1; i<=n; i++){
			cnt = 0;
			j = i;
			if(b[j]>0){
				b[j]--;
				ans[i] = 1;
			}	
			else{
				while( j>0 && b[j]==0){
					cnt++;
					j--;
				}
				ans[i] = cnt + 1;
				b[j]--;
			}
		}
		
		for(i=1; i<n; i++){
			cout << ans[i] << " "; 
		}
		cout << ans[n] << endl;
	}

	return 0;	
}
#include<iostream>

using namespace std;

int map[105][105];
int dist[105][105];
bool vis[105][105];
int sum1;
int n;

void folyd(){
	int i,j,k;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			for(k=1;k<=n;k++){
				if(map[j][i] + map[i][k] < dist[j][k]){
					dist[j][k] = map[j][i] + map[i][k];
					if(!vis[j][k]){
						sum1 = sum1 + 2;
						vis[j][k] = true;
					}
				}
			}
		}
	}
}


int main()
{
	int i, j;
	int sum;

	while(cin >> n && n!=0){
		sum = 0;
		for(i=1; i<=n; i++){
			for(j=1; j<=n; j++){
				cin >> map[i][j];
				dist[i][j] = map[i][j];
				if(i>j && map[i][j])
					sum++;
			}
		}
		//cout << sum << endl;

		sum1 = 0;
		memset(vis, false, sizeof(vis));
		folyd();
		for(i=1; i<=n; i++){
			for(j=1; j<=n; j++){
				cout << dist[i][j] << " ";
			}
			cout << endl;
		}
		cout << sum - sum1 << endl;
	}

	return 0;
}
/*
3
0 1 2
1 0 1
2 1 0

4
0 1 2 5
1 0 3 6
2 3 0 4
5 6 4 0

0
*/
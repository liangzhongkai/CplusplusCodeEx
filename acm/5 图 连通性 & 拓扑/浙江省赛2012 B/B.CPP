#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<stack>

using namespace std;

const int N = 30010;

map<string, int> mp;
int adj[N][N];
string str[25];

int main()
{
	int tc;
	int n, m, q;
	int nu;
	int i, j, l, k;
	string str1, str2;
	int cn;

	cin >> tc;
	while(tc--){
		cin >> n >> m >> q;
		memset(adj, 0, sizeof(adj));
		mp.clear();
		cn = 1;

		for(i=0; i<n; i++){
			cin >> str1 >> nu;
			mp[str1] =  i+1;

			for(j=0; j<nu; j++){
				cin >> str2;
				if(mp.find(str2)==mp.end()){
					l = cn;
					mp[str2] = l;
					cn++;
				}
				else
					l = mp[str2];
				adj[i+1][l] = 1;
			}
		}

		for(i=0; i<m; i++){
			cin >> str1 >> nu;
			if(mp.find(str1)==mp.end()){
				l = cn;
				mp[str1] = l;
				cn++;
			}
			else
				l = mp[str1];
			for(j=0; j<nu; j++){
				cin >> str2;
				adj[mp[str2]][l] = 2;
			}
		}

		
		//map<string,int>::iterator itt;
		//for(itt=mp.begin(); itt!=mp.end(); itt++){
		//	cout << (*itt).first <<  " " << (*itt).second << endl;
		//}


		int key = 0;
		int ans = 0;
		for(j=0; j<q; j++){
			cin >> nu;
			for(i=0; i<nu; i++){
				cin >> str[i];
			}
			for(i=0; i<nu; i++){
				int e = mp[str[i]];
				for(l=0; l<nu; l++){
					if(i!=l && adj[e][mp[str[l]]]==1 ){
						key++;
					}
				}
				if(key==nu){
					ans = i;
					break;
				}
			}
			if(ans==0)
				cout << 0 << endl;
			else 
				cout << 1 << " " << str[ans] << endl;
		}

		
	}

	return 0;
}
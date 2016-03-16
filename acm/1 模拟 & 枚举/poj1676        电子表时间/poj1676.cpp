#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<set>

using namespace std;

char a[4][9], b[4][9];
char mp[10][9];
vector<int> x[4], y[4];
set<int> se;

bool is(char *p, int q){
	int i;
	for(i=0; i<9; i++){
		if((p[i]=='|' || p[i]=='_')  && p[i]!=mp[q][i])
			return false;
	}
	return true;

}

int main()
{
	int tc;
	int i, j, k, l;
	int ans;

	memset(mp, 0, sizeof(mp));
	mp[0][1] = '_', mp[0][3] = '|',mp[0][5] = '|',mp[0][6] = '|',mp[0][7] = '_', mp[0][8] = '|';
	mp[1][5] = '|', mp[1][8] = '|';
	mp[2][1] = '_',mp[2][4] = '_', mp[2][5] = '|', mp[2][6] = '|', mp[2][7] = '_';
	mp[3][1] = '_',mp[3][4] = '_', mp[3][5] = '|', mp[3][7] = '_', mp[3][8] = '|';
	mp[4][3] = '|', mp[4][4] = '_', mp[4][5] = '|', mp[4][8] = '|';
	mp[5][1] = '_',mp[5][3] = '|', mp[5][4] = '_', mp[5][7] = '_', mp[5][8] = '|';
	mp[6][1] = '_',mp[6][3] = '|', mp[6][4] = '_', mp[6][6] = '|', mp[6][7] = '_', mp[6][8] = '|';
	mp[7][2] = '_', mp[7][5] = '|', mp[7][8] = '|';
	mp[8][1] = '_', mp[8][3] = '|',mp[8][4] = '_', mp[8][5] = '|',mp[8][6] = '|',mp[8][7] = '_', mp[8][8] = '|';
	mp[9][1] = '_', mp[9][3] = '|',mp[9][4] = '_', mp[9][5] = '|',mp[9][7] = '_', mp[9][8] = '|';
	

	scanf("%d", &tc);

	while(tc--){
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		for(i=0; i<4; i++){
			while(!x[i].empty())  x[i].pop_back();
			while(!y[i].empty())  y[i].pop_back();
		}
		
		se.clear();
		set<int>::iterator it;

		for(i=0; i<3; i++){
			getchar();
			for(j=0; j<4; j++){
				for(k=0; k<3; k++)
					scanf("%c", &b[j][i*3+k]);
			}
			getchar();
			for(j=0; j<4; j++){
				for(k=0; k<3; k++)
					scanf("%c", &a[j][i*3+k]);
			}
		}

		for(i=0; i<4; i++){
			if(i==0){
				for(j=0; j<3; j++)
					if(is(a[i], j))
						x[i].push_back(j);
			}
			else if(i==2){
				for(j=0; j<6; j++)
					if(is(a[i], j))
						x[i].push_back(j);
			}
			else{ 
				for(j=0; j<10; j++)
					if(is(a[i], j))
						x[i].push_back(j);
			}
		}
/*
		for(i=0; i<4; i++){
			for(j=0; j<x[i].size(); j++)
				cout << x[i][j] << " ";
			cout << "***" << endl;
		}
*/
		int tmp = 0;
		int yu = 0;
		for(i=0; i<x[0].size(); i++)
			for(j=0; j<x[1].size(); j++)
				for(k=0; k<x[2].size(); k++)
					for(l=0; l<x[3].size(); l++){
						if(x[0][i]==2){
							if(x[1][j]<4){
								tmp = x[0][i]*1000 + x[1][j]*100 + x[2][k]*10 + x[3][l];
								yu = tmp%100;
								if(yu<45)   tmp += 15;
								else if(x[1][j]<3)  tmp = tmp/100*100 + 100 + yu + 15 - 60 ;
								else if(x[1][j]==3) tmp = yu + 15 - 60;
								se.insert(tmp);
							}
						}
						else{
							tmp = x[0][i]*1000 + x[1][j]*100 + x[2][k]*10 + x[3][l];
							yu = tmp%100;
							if(yu<45)   tmp += 15;
							else if(tmp%1000/100==9)   tmp = tmp/1000*1000 + 1000 + yu + 15 - 60;
							else tmp = tmp/100*100 + 100 + yu + 15 - 60;
							se.insert(tmp);
						}
					}
/*	
		for(it=se.begin(); it!=se.end(); it++)
			cout << *it << " ";
		cout << endl;
*/
		for(i=0; i<4; i++){
			if(i==0){
				for(j=0; j<3; j++)
					if(is(b[i], j))
						y[i].push_back(j);
			}
			else if(i==2){
				for(j=0; j<6; j++)
					if(is(b[i], j))
						y[i].push_back(j);
			}
			else{ 
				for(j=0; j<10; j++)
					if(is(b[i], j))
						y[i].push_back(j);
			}
		}
/*
		for(i=0; i<4; i++){
			for(j=0; j<y[i].size(); j++)
				cout << y[i][j] << " ";
			cout << "***" << endl;
		}
*/
		int key = 0;
		ans = 0;
		for(i=0; i<y[0].size(); i++)
			for(j=0; j<y[1].size(); j++)
				for(k=0; k<y[2].size(); k++)
					for(l=0; l<y[3].size(); l++){
						tmp = y[0][i]*1000 + y[1][j]*100 + y[2][k]*10 + y[3][l];
						if(se.find(tmp)!=se.end()){
							key++;
							ans = tmp;
						}
					}

		int left = ans/100, right = ans%100;
		if(key==1){
			if(left==0){
				if(right==0)
					cout << "0000" << endl;
				else if(right<10)
					cout << "000" << right << endl;
				else
					cout << "00" << right << endl;
			}
			else if(left<10){
				if(right==0)
					cout << "0" << left << "00" << endl;
				else if(right<10)
					cout << "0" << left << "0" << right << endl;
				else
					cout << "0" << left << right << endl;	
			}
			else{
				if(right==0)
					cout << left << "00" << endl;
				else if(right<10)
					cout << left << "0" << right << endl;
				else
					cout << left << right << endl;
			}
		}
		else
			cout <<"Not Sure" << endl;
	
	}

	return 0;
}






/*
4
    _  _  _      _     _ 
  | _  _||       _   ||  
  | _ |_   |   | _    |_|
    _  _  _   _  _     _ 
  ||_  _||       _|  ||  
  | _ |_   |   ||     |_|
 _  _  _  _   _  _  _  _ 
|_||_||_||_| |_||_||_||_|
|_||_||_||_| |_||_||_||_|
 _  _  _  _      _     _ 
| || || || |     _||_||_ 
|_||_||_||_|     _|  | _|

*/

/*
	mp[0][1] = '_', mp[0][3] = '|',mp[0][5] = '|',mp[0][6] = '|',mp[0][7] = '_', mp[0][8] = '|';
	mp[1][5] = '|', mp[1][8] = '|';
	mp[2][1] = '_',mp[2][4] = '_', mp[2][5] = '|', mp[2][6] = '|', mp[2][7] = '_';
	mp[3][1] = '_',mp[3][4] = '_', mp[3][5] = '|', mp[3][7] = '_', mp[3][8] = '|';
	mp[4][3] = '|', mp[4][4] = '_', mp[4][5] = '|', mp[4][8] = '|';
	mp[5][1] = '_',mp[5][3] = '|', mp[5][4] = '_', mp[5][7] = '_', mp[5][8] = '|';
	mp[6][1] = '_',mp[6][3] = '|', mp[6][4] = '_', mp[6][6] = '|', mp[6][7] = '_', mp[6][8] = '|';
	mp[7][2] = '_', mp[7][5] = '|', mp[7][8] = '|';
	mp[8][1] = '_', mp[8][3] = '|',mp[8][4] = '_', mp[8][5] = '|',mp[8][6] = '|',mp[8][7] = '_', mp[8][8] = '|';
	mp[9][1] = '_', mp[9][3] = '|',mp[9][4] = '_', mp[9][5] = '|',mp[9][7] = '_', mp[9][8] = '|';
*/
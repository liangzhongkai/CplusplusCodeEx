//  240K	172MS	C++	1124B
#include<iostream>

using namespace std;

int x, y, z;
int a;

void add(int dir){
	if(dir==0)   x += a;
	else if(dir==3)   x -= a;
	else if(dir==1)   y += a;
	else if(dir==4)   y -= a;
	else if(dir==2)   z += a;
	else if(dir==5)   z -= a;
}

int main()
{
	int tc;
	int n;
	int i, t;
	int df, du, dr;
	char dir[10];

	scanf("%d", &tc);
	while(tc--){
		scanf("%d", &n);
		x = 0; y = 0; z = 0; df = 0; du = 2; dr = 1;
		for(i=0; i<n; i++){
			scanf("%s%d", dir, &a);
			if(strcmp(dir, "left")==0){
				t = df, df = (dr + 3) % 6, dr = t;
				add(df);
			}
			else if(strcmp(dir, "right")==0){
				t = df, df = dr, dr = (t + 3) % 6;
				add(df);
			}
			else if(strcmp(dir, "up")==0){
				t = df, df = du, du = (t + 3) % 6;
				add(df);
			}
			else if(strcmp(dir, "down")==0){
				t = df, df = (du + 3) % 6, du = t;
				add(df);
			}
			else if(strcmp(dir, "forward")==0){
				add(df);
			}
			else if(strcmp(dir, "back")==0){
				df = (df + 3) % 6;
				dr = (dr + 3) % 6;
				add(df);
			}
		}
		cout << x << " " << y << " " << z << " " << df << endl;
	}

	return 0;
}
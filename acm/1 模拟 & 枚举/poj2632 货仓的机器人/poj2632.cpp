//  296K	16MS	C++	5095B
#include<iostream>

using namespace std;

struct point{
	int x, y;
	int der;
}mp[105];

int map[105][105];

int main()
{
	int tc;
	int n, m;
	int a, b;
	int i, j;
	int p, num;
	char d, ch;

	cin >> tc;
	while(tc--){
		memset(map, 0, sizeof(map));
		cin >> n >> m >> a >> b;

		for(i=1; i<=a; i++){
			cin >> mp[i].x >> mp[i].y >> ch;
			switch(ch){
			case'E':mp[i].der = 0;break;
			case'S':mp[i].der = 1;break;
			case'W':mp[i].der = 2;break;
			case'N':mp[i].der = 3;break;
			}
			map[mp[i].x][mp[i].y] = i;
		}

		int key = 0 ;
		int pp = 0, qq = 0;
		int flag = 0;
		for(i=0; i<b; i++){
			cin >> p >> d >> num ;
				
				
			if(flag==0){
				if(d=='L'){
					num = num % 4;
					mp[p].der = (mp[p].der - num + 4) % 4;
				}
				else if(d=='R'){
					num = num % 4;
					mp[p].der = (mp[p].der + num) % 4;
				}
				else{
					if(mp[p].der==0){
							 int xx, yy;
							 xx = mp[p].x;   yy = mp[p].y;
							 map[xx][yy] = 0; 
							 mp[p].x += num;
							 for(j=xx; j<=mp[p].x; j++){
								 if(j>n){
									 pp = p;
									 key = 2;
									 break;
								 }
								 if(map[j][yy]){
									 pp = p;
									 qq = map[j][yy];
									 key = 1;
									 break;
								 }
							}
							if(mp[p].x<=n)
								map[mp[p].x][yy] = p; 
					}
					else if(mp[p].der==1){
							 int xx, yy;
							 xx = mp[p].x;   yy = mp[p].y;
							 map[xx][yy] = 0; 
							 mp[p].y -= num;
							 for(j=yy; j>=mp[p].y; j--){
								 if(j<1){
									pp = p;
									key = 2;
									break;
								 }
								 if(map[xx][j]){
									 pp = p;
									 qq = map[xx][j];
									 key = 1;
									 break;
								 }
							 }
							 if(mp[p].y>0)
								map[xx][mp[p].y] = p; 
					}
					else if(mp[p].der==2){
							 int xx, yy;
							 xx = mp[p].x;   yy = mp[p].y;
							 map[xx][yy] = 0; 
							 mp[p].x -= num;
							 for(j=xx; j>=mp[p].x; j--){
								 if(j<1){
									pp = p;
									key = 2;
									break;
								 }
								 if(map[j][yy]){
									 pp = p;
									 qq = map[j][yy];
									 key = 1;
									 break;
								 }
							 }
							 if(mp[p].x>0)
								map[mp[p].x][yy] = p; 
					}
					else{
							 int xx, yy;
							 xx = mp[p].x;   yy = mp[p].y;
							 map[xx][yy] = 0;
							 mp[p].y += num;
							 for(j=yy; j<=mp[p].y; j++){
								 if(j>m){
									 pp = p;
									 key = 2;
									 break;
								 }
								 if(map[xx][j]){
									 pp = p;
									 qq = map[xx][j];
									 key = 1;
									 break;
								 }
							 }
							 if(mp[p].y<=m)
								map[xx][mp[p].y] = p;
					}
				}//else
			}
			if(key==2||key==1){
				flag = 1;
			}
		}//for
		if(key==0){
			 cout << "OK" << endl;
		}
		else if(key==1){
			cout << "Robot " << pp << " crashes into robot " << qq << endl;
		}
		else{
			cout << "Robot " << pp << " crashes into the wall" << endl;
		}

	}

	return 0;
}


/*
#include <iostream>

using namespace std;

#define SIZE 101

int ew,ns;
int i,j;
int map[SIZE][SIZE];

struct robot
{
 int x,y,dir;
} rob[SIZE];

struct instruction
{
 int ro_id,act,repeat;
} ins[SIZE];

bool judge( struct instruction instru)
{
     int id = instru.ro_id;
	 switch ( instru.act )
	 {

		 case -1: rob[id].dir = ( rob[id].dir+instru.repeat )%4; break;

		 case  1: rob[id].dir = ( rob[id].dir+4-instru.repeat%4 )%4; break;

		 case  0: while( instru.repeat-- )

				  {

					 map[rob[id].x][rob[id].y] = 0;

					 switch ( rob[id].dir )
					 {
						 case 0: rob[id].x--;break;
						 case 1: rob[id].y--;break;
						 case 2: rob[id].x++;break;
						 case 3: rob[id].y++;break;
					 }

					 if ( rob[id].x < 1 || rob[id].y < 1 || rob[id].x > ew || rob[id].y > ns )
					 {
						  cout << "Robot " << id << " crashes into the wall" << endl;
						  return false;
					 }

					 else if ( map[rob[id].x][rob[id].y] )
					 {
						  cout << "Robot " << id << " crashes into robot " << map[rob[id].x][rob[id].y] << endl;
						  return false;
					 }

					 else { map[rob[id].x][rob[id].y] = id;}

					} break;

		 default:break;
	 }

     return true;
} 

int main()
{
	 int k,n,m;
	 char ch;

	 cin >> k;

	 while (k--)
	 {
		  memset( map, 0, sizeof(map) );

		  cin >> ew >> ns;
		  cin >> n >> m;

		  for ( i = 1; i <= n; i++ )
		  {
		   cin >> rob[i].x >> rob[i].y >> ch;

		   if ( ch == 'W' ) rob[i].dir = 0;

		   else if ( ch == 'S' ) rob[i].dir = 1;

		   else if ( ch == 'E' ) rob[i].dir = 2;

		   else rob[i].dir = 3;

		   map[rob[i].x][rob[i].y] = i;

		  }

		  for ( i = 1; i <= m; i++ )
		  {
			   cin >> ins[i].ro_id >> ch >> ins[i].repeat;

			   if ( ch == 'L' ) ins[i].act = -1;

			   else if ( ch == 'R' ) ins[i].act = 1;

			   else ins[i].act = 0;
		  }

		  for ( i = 1; i <= m; i++ )
		  {
			   if ( !judge(ins[i]) )
					break;
		  }

		  if ( i > m ) 
			  cout << "OK" << endl; 

	 }

	 return 0;

}
//*/
#include<iostream>
#include<algorithm>
#include<cstdio>

using namespace std;

const int N = 100005;

struct point{
	int x, y;
}mp[N];

bool cmp(const point &a, const point &b){
	return a.x<b.x;
}

int main()
{
	int n;
	int a, b;
	int i, j;

	while(scanf("%d", &n) && n!=0){
		for(i=0; i<n; i++){
			scanf("%d%d", &a, &b);
			if(a>b){
				a = a^b; 
				b = a^b; 
				a = a^b;
			}
			mp[i].x = a;  mp[i].y = b;
		}

		sort(mp, mp+n, cmp);

		int key = 0;
		for(i=0; i<n; i++){
			for(j=i; j<n; j++){
				if(mp[i].y>mp[j].x && mp[i].y<mp[j].y){
					key = 1;
					break;
				}
				else if(mp[i].y<mp[j].x){
					i = j-1;
					break;
				}
				else if(mp[i].y>mp[j].y){

					if(j+1<n&&mp[j+1].x<mp[j].y){
						i = j - 1;
						break;
					}
				}
			}
			if(key==1)
				break;
		}
		if(key==1)
			cout << "No" << endl;
		else
			cout << "Yes" << endl;
	}

	return 0;
}


/*




#include<iostream>
#include<cstdlib>
#include<algorithm>

using namespace std;

struct node
{
       int x, y;
};
node circle[100005];

bool cmp( const node& a, const node& b )
{
     return a.x<b.x;
}

int main()
{
    int n;
    int i, j, a, b;
    while( cin >> n && n!=0 )
    {
           for( i=1; i<=n; i++ )
           {
                cin >> a >> b; 
                    
                if( a>b )
                {
                    circle[i].x = b;
                    circle[i].y = a; 
                }
                else
                {
                    circle[i].x = a;
                    circle[i].y = b;
                }
           }
           
           sort( circle, circle+n, cmp );
         
           int flag = 0;
           int pos = 1;
           for( i=2; i<=n; i++ )
           {
                 if( circle[pos].y>circle[i].x && circle[pos].y<circle[i].y )
                 {
                     flag = 1;
                     break;
                 }
                 else if( circle[pos].y<circle[i].x )
                 {
                      pos = i;
                 }
                 else if( circle[pos].y>circle[i].y )
                 {
                      if( circle[i+1].x<circle[i].y && i+1<=n )
                          pos = i;
                 }
           }
           if( flag==1 )
               cout << "No" << endl;
           else
               cout << "Yes" << endl;
    }
    return 0;    
}                                 
//*/


//*
#include "iostream" 
#include "stack" 
#include "map" 
using namespace std; 
 
 
int main() 
{     
   int N;    
   while (cin >> N && N != 0)     
   {       
    map<int, int> m;         
    stack<int> s;         
    int pos1, pos2;         
    for (int i = 0; i < N; i++)        
    {             
        cin >> pos1 >> pos2;             
        m[pos1] = pos2;             
        m[pos2] = pos1;         
    }         
    for (int i = 1; i <= N * 2; i++)         
    {             
        if (!s.empty() && m[i] == s.top())                 
			s.pop();             
        else if (!s.empty() && m[i] != s.top())                
			s.push(i);             
        else                 
			s.push(i);        
    }        
    if (s.empty())             
       cout << "Yes" << endl;         
    else           
       cout << "No" << endl;     
    } 
}                                 
//*/
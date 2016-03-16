/*

#include <iostream>  
#include <string.h>  
#include <cstdio>  
#include <iostream>

using namespace std;  

int x,y,q;  
int gcd(int a,int b){  
    if(b==0)  
        return a;  
    return gcd(b,a%b);  
}  

int extend_uclid(int a,int b){  
    if(b==0){  
      x=1;  
      y=0;  
      q=a;  
      return q;  
    }  
    else{  
      extend_uclid(b,a%b);  
      int tmp=x;  
      x=y;  
      y=tmp-a/b*y;  
    }  
}  

int main()
{  
    //freopen("2.txt","r",stdin);  
    int numcase;  
    int a,m;  

    scanf("%d",&numcase);  
    while(numcase--){  
      scanf("%d%d",&a,&m);  
      if(m==1){  
          if(a%m==0){  
             puts("1");  
          }  
          else if(m%a==0){  
            printf("%d\n",m/a);  
          }  
          else{  
            puts("Not Exist");  
          }  
      }  
      else{  
        int flag=gcd(a,m);  
        if(flag!=1)puts("Not Exist");  
        else{  
          extend_uclid(a,m);  
		  cout << x << " " << y << endl;
          while(x<0){  
            x+=m;  
          }  
          printf("%d\n",x);  
        }  
      }  
    }  
    return 0;  
}
//*/


/*


#include<iostream>

using namespace std;

int main()
{
	int tc;
	int key;
	int i;
	int a, b;
	cin >> tc;

	while(tc--){
		cin >> a >> b;
		key = 0;
		if(b==1){
			cout << 1 << endl;
			continue;
		}
		else{
			for(i=1; i<=b; i++){
				if((a*i)%b==1){
					key = 1;
					break;
				}
			}
		}
		if(key==0)
			cout << "Not Exist" << endl;
		else 
			cout << i << endl;
	}

	return 0;
}
//*/
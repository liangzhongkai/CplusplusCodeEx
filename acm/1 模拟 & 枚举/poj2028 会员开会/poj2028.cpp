//  248K	47MS	C++	534B
#include<iostream>
#include<cstring>

using namespace std;

int main()
{
	int n, q;
	int m, l;
	int i, j;
	int a[100];

	while(cin >> n >> q && n!=0 && q!=0 )
	{
		for(i=1; i<100; i++)
			a[i] = 0;

		for(j=0; j<n; j++)
		{
			 cin >> m;
			 for(i=0; i<m; i++)
			 {
				 cin >> l;
				 a[l]++;
			 }
		}

		int ans=0;
		int key=0;
		for(i=1; i<100; i++)
			if(a[i]>ans)
			{
				ans = a[i];
				key = i;
			}
		if(ans>=q)
			cout << key << endl;
		else
			cout << 0 << endl;
	}

	return 0;
}




/*   168K	16MS	C++	470B
#include<stdio.h>
int n,q,m,a,f[999],s;
int main()
{
    while (scanf("%d%d",&n,&q),n!=0)
    {
          for (s=800;s>0;s--) f[s]=0;
          while (n--)
          {
                scanf("%d",&m);
                while (m--)
                {
                      scanf("%d",&a);
                      f[a]++;
                }
          }
          for (m=0;m<800;m++) if (f[m]>=q&&f[m]>f[s]) s=m;
          printf("%d\n",s); 
    }
	return 0;
}
//*/


/*
#include <fstream>  
#include <stdio.h>  
#include <iostream>  
#include <string.h>  
#include <string>  
#include <vector>  
#include <stack>  
#include <queue>  
#include <deque>  
#include <map>  
#include <math.h>  
#include <algorithm>  
#include <numeric>  
#include <functional>  
#include <memory.h>  
  
using namespace std;  
  
int main(void)  
{  
//  ifstream cin("data.txt");  
    int N,Q, i;  
    int index,M;  
  
    while(cin>>N>>Q && (N||Q))  
    {  
        vector<int> myvec(100,0);  
        vector<int>::iterator iter;  
  
        for(i=0;i<N;++i)  
        {  
            cin>>M;  
            for(int j=0;j<M;++j)  
            {  
                cin>>index;  
                ++myvec.at(index);  
            }  
        }  
  
        for(i=N;i>=Q;--i)  
        {  
            iter=find(myvec.begin(),myvec.end(),i);  
            if(iter !=myvec.end())  
            {  
                cout<<distance(myvec.begin(),iter)<<endl;  
                break;  
            }  
            else if(i==Q)  
            {  
                cout<<0<<endl;  
            }  
        }  
  
    }  
  
  
    return 0;  
}  
//*/



/*
#include<iostream>
#include<memory.h>
using namespace std;
int index[1001];
int main(){
    int m,n,i,j,t,s,max1,max2,temp;
    while(cin>>m>>n){
        if(m==0&&n==0)break;
        max1=-1;max2=-1;
        memset(index,0,sizeof(index));
        for(i=0; i<m; i++){
            cin>>t;
            for(j=0; j<t; j++){
                    cin>>s;
                    index[s]++;
            }
        }
        for(j=0;j<101;j++){
            if(max2<index[j]) {max2=index[j];temp=j;}
        }
        if(max2>=n)
             cout<<temp<<endl;
        else cout<<0<<endl;
    }
    return 0;
}
//*/
/*
#include<iostream>
#include<fstream>
using namespace std;

ifstream  fin("data.txt");
#define  cin  fin 

int main()
{
	

	return 0;
}
//*/

//*       Memory: 268K		Time: 0MS

    #include<iostream>
	#include<fstream>

    using namespace std;

	ifstream  fin("data.txt");
	#define  cin  fin

    const int MAX=110;

    int dis[MAX][MAX];
    int n;
    int i,j,k;

    void Floyd()
    {
    	int k,i,j;
		
		
    	for(k=1; k<=n; k++)
    		for(i=1; i<=n; i++)
    			for(j=1; j<=n; j++)
    				if(dis[i][j]>dis[i][k]+dis[k][j])   //即使将dis[i][i]的值改变了，没所谓，下面的过程不用用到！
    					dis[i][j] = dis[i][k] + dis[k][j];
    }


    int main()
    {
    	int a,b,p,n1;

    	while(cin>>n&&n!=0)
    	{
    		memset(dis,10000,sizeof(dis));

    		for(i=1; i<=n; i++)
    		{
    			cin>>n1;
    			for(j=0; j<n1; j++)
    			{
    				cin>>a>>b;
    				dis[i][a]=b;
    			}
    		}

    		Floyd();
    		int max,min=10000;
    		p=1;
    		for(i=1; i<=n; i++)
    		{
    			max=0;
    			for(j=1; j<=n; j++)
    			{
    				if(max<dis[i][j]&&i!=j)
    					max=dis[i][j];
    			}
    			if(min>max)
    			{
    				min=max;   p=i;
    			}
    		}
    		min<10000?(cout<<p<<" "<<min<<endl):(cout<<"disjoint"<<endl);
    	}
    	return 0;
    }



//*/
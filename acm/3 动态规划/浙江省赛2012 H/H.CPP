/*
5
6
4 3 1 9 9 1
1 3 6 10 11 12
4
4 3 1 9
1 3 6 10
4
4 3 1 9
1 4 6 7
4
1 2 3 4
1 3 6 10
3
4 3 2
1 3 6
*/
/*
#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

int b[1005];
int c[1005];

int main()
{
	int tc;
	int n;
	int i;
	int a, num1, num2;
	double tmp, ans;

	cin >> tc;

	while(tc--){
		cin >> n;
		tmp = ans = 0;
		num1 = 1; num2 = 0;
		for(i=0; i<n; i++){
			cin >> a;
			tmp += a;
			num2++;
			if(double(tmp/num2)>double(ans/num1)){
				ans += tmp;
				num1 += num2;
				if(i==0)
					num1--;
				num2 = 0;
				tmp = 0;
			}
		}
		memset(b, 0, sizeof(b));
		memset(c, 0, sizeof(c));
		for(i=0; i<n; i++){
			cin >> b[i];
		}
		c[0] = b[0];
		for(i=1; i<n; i++){
			c[i] = b[i] - b[i-1];
		}
		for(i=1; i<n; i++){
			if(c[i]<c[i-1])
				c[i] = c[i-1];
		}
		///cout << c[num1-1] << " " << ans/num1 << endl;

		printf("%.6lf %.6lf\n", double(c[num1-1]), double(ans/num1));
	}
		
	return 0;
}
//*/

//*
#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

const int N = 1010;
int a[N], b[N], c[N];

int main()
{
	int tc;
	int n, i;
	double ans, tmp, tim;
	 
	scanf("%d", &tc);

	while(tc--){
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		memset(c, 0, sizeof(c));

		scanf("%d", &n);

		a[0] = 0;
		for(i=1; i<=n; i++){
			scanf("%d", a+i);
			a[i] += a[i-1];
		}
	
		b[0] = 0;
		for(i=1; i<=n; i++){
			scanf("%d", b+i);
		}

		c[0] = 0;
		for(i=1; i<=n; i++){
			c[i] = b[i] - b[i-1];
		}
		for(i=1; i<=n; i++){
			if(c[i]<c[i-1])
				c[i] = c[i-1];
		}

		ans = double(a[1]);
		tim = double(c[1]);
		for(i=2; i<=n; i++){
			tmp = double(a[i])/i;
			if(tmp>ans ){
				if(i==n){
					ans = tmp;
					tim = double(c[i]);
					continue;
				}
				if(c[i]<b[i+1]-b[i]){
					ans = tmp;
					tim = double(c[i]);
				}
			}
		}
		printf("%.6lf %.6lf\n", tim, ans);
	}
}
//*/




/*   C++ 	20s 	188kb
#include<iostream>  
#include<stdio.h>  

using namespace std;  
  
int main()  
{  
    int pi[1001],ti[1001];  
    double temp,Maxtime,Max,Time;  
    int t,n,i,sum;  

    scanf("%d",&t);  

    while(t--)  
    {  
        scanf("%d",&n);  
        for(i=1;i<=n;i++)  
        {  
            scanf("%d",&pi[i]);  
        }  
        ti[0]=0;  
        for(i=1;i<=n;i++)  
        {  
            scanf("%d",&ti[i]);   
        }  
        sum=0;  
        Max=0;  
        Maxtime=0;  

        for(i=1;i<=n;i++)  
        {  
            sum+=pi[i];  
            temp=(double)sum/(i);//当前的平均价格 
			
            if(Maxtime<(ti[i]-ti[i-1]))  
            {
                Maxtime=ti[i]-ti[i-1];  
            }
            if(i==n)  
            {
                if(temp>Max)  
                {
                    Max=temp;  
                    Time=Maxtime;  
                }
                continue;  
            }
            if(Maxtime<(ti[i+1]-ti[i])&&temp>Max)  
            {
                Max=temp;  
                Time=Maxtime;  
            }
        }

        printf("%.6lf %.6lf\n",Time,Max);  
    }  
    return 0;  
}  
//*/

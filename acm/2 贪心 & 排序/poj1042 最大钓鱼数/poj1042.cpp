
//*       256K	235MS	C++	1380B

#include<iostream>
#include<fstream>
#include<queue>
using namespace std;

ifstream  fin("data.txt");
#define  cin  fin 

struct point
{
	int f, d, id;
	bool operator<(const point &a)const
	{
		if(f==a.f)
			return id>a.id;
		return f<a.f;
	}
};

point mp[26];
int cost[26];
int cot[26];
int size[26];

priority_queue<point> q;

int main()
{
	int n, h;
	int i, j;

	while(cin >> n && n!=0)
	{
		cin >> h;
		h = h * 12;
		for(i=1; i<=n; i++)
			cin >> mp[i].f;
		for(i=1; i<=n; i++)
		{
			cin >> mp[i].d;
			mp[i].id = i;
		}
		cost[1] = 0;
		for(i=2; i<=n; i++)
		{
			cin >> cost[i];
			cost[i] += cost[i-1];
		}

		memset(size, 0, sizeof(size));
		int ans = -1;                 // 如果初始f值都为0，ans = 0, 那么sum永远都不会比ans大
		for(i=1; i<=n; i++)
		{
			memset(cot, 0, sizeof(cot));
			int hh = h - cost[i];
			int sum = 0;

			while(!q.empty())  q.pop();

			for(j=1; j<=i; j++)
				q.push(mp[j]);

			while(hh>0)
			{
				point tmp = q.top();
				q.pop();
				sum += tmp.f;
				cot[tmp.id]++;
				tmp.f -= tmp.d;
				while(tmp.f<0)
					tmp.f = 0;
				q.push(tmp);
				hh--;
			}
			if(sum>ans)
			{
				ans = sum;
				for(j=1; j<=i; j++)
					size[j] = cot[j];
			}
		}

		for(i=1; i<n; i++)
			cout << size[i]*5 << ", ";
		cout << size[n]*5 << endl;
		cout << "Number of fish expected: " << ans << endl;
		cout << endl;
		
	}

	return 0;
}
//*/








/*     180K	204MS	C++	1778B

#include <iostream>
#include <queue>

using namespace std;

struct data {
       int f,d,id;
}a[30],b;

int n,t,tran[30],x,ans,maxi,save[30],tmp[30],tt;
priority_queue <data> q;

bool operator<(data a,data b) {
     if (a.f==b.f) return a.id>b.id;
     else return a.f<b.f;
}

int main() {
	int i, j;
    while (~scanf("%d",&n)) {
          if (n==0) break;
          scanf("%d",&t);
          t *= 12;
          for (i=1;i<=n;i++)
              scanf("%d",&a[i].f);
          for (i=1;i<=n;i++) {
              scanf("%d",&a[i].d);
              a[i].id = i;
          }
          tran[1] = 0;
          for (i=2;i<=n;i++) {
              scanf("%d",&x);
              tran[i] = tran[i-1] + x;
          }
          
          ans = -1;
          memset(save,0,sizeof(save));

          for (i=1;i<=n;i++) {
              maxi = 0;
              memset(tmp,0,sizeof(tmp));
              tt = t - tran[i];            // 总时间减去去第i个岛的时间

              while (!q.empty()) q.pop();
              for (j=1;j<=i;j++)
                  q.push(a[j]);

              while (tt>0) {
                    b = q.top();
                    q.pop();
                    tt--;
                    maxi += b.f;
                    tmp[b.id]++;
                    b.f -= b.d;
                    if (b.f<=0) b.f = 0;
                    q.push(b);
              }
              if (maxi>ans) {
                    ans = maxi;
                    for (j=1;j<=i;j++)
                        save[j] = tmp[j];
              }
          }
          
          for (i=1;i<n;i++)
              printf("%d, ",save[i]*5);
          printf("%d\n",save[n]*5);
          printf("Number of fish expected: %d\n\n",ans);
    }
    return 0;
}

//*/
/*
#include<iostream>
#include<queue>
#include<vector>

using namespace std;

typedef pair<int, int> pii;
queue<pii> q;

vector<int> vec;

int main()
{
	int n, m;
	int a, b;
	int i, j;
	int count;
	int file[10001] = {0};

	cin >> n >> m;
	count = 1;
	for(i=1; i<=m; i++)
	{
		cin >> a;
		for(j=1; j<=a; j++)
		{
			cin >> b;
			vec.push_back(b);
			file[b] = count++;
		}
	}

	count = 0;
	for(i=0; i<vec.size(); i++)
	{
		if(file[i+1]==vec[i])
		{
			count++;
		}
		else
		{
			 if(file[i+1]==0)
			 {
				 file[i+1] = i+1;
				 file[vec[i]] = 0;
				 q.push(make_pair(vec[i],i+1));
				 count++;
			 }
		}
	}

	for(i=1; i<=n; i++)
	{
		if(file[i]!=i)
			break;
	}

	file[n] = file[i];
	q.push(make_pair(i, n));
	file[i] = 0;

	while(count!=vec.size())
	{
		for(j=1; j<=n; j++)
		{
			 if(file[j]==i)
			 {
				 file[i] = file[j];
				 file[j] = 0;
				 q.push(make_pair(j, i));
				 i = j;
				 count++;
				 break;
			 }
		}
	}

	while(!q.empty())
	{
		pii temp;
		temp = q.front();
		cout << temp.first << " " << temp.second << endl;
		q.pop();
	}


	return 0;
}
//*/



//*Memory: 404K  Time: 157MS    Language: C++   Result: Accepted
#include <stdio.h>
#include <string.h>

 
int position[10001];
bool visited[10001];
int n, flag, free_c;   //  free_c为最后找的位置  flag为


int find_free()
{
	 int i;

	 for (i = n;i >= 1; i--)
			if (position[i] == 0)
				   break;

	 return i;
}

void move(int from, int to)
{
	 position[to] = position[from];
	 position[from] = 0;
	 printf("%d %d\n", from, to);
}

 

void dfs(int from, int to)
{
	 if (position[to]!= 0)  // to的目标位置有人坐了
	 {
			if (visited[to]== false)
			{
				   visited[from]= true;
				   dfs(to,position[to]);
			}
			else  // 这个to
			{
				   flag = to;
				   free_c = find_free();
				   move(to,free_c);
			}
	 }

	 if (from !=flag)   // flag只记录那个被放到最后的位置号 
			move(from,to);
	 else
			move(free_c,to);

}

 

void solve()
{
	 int i, move = 0;

	 for (i = 1;i <= n; i++)
	 {
			if (position[i]== 0 || position[i] == i)
				   continue;
			dfs(i,position[i]);   // 第i位置不是i的情况
			move++;
	 }

	 if (! move)
			printf("No optimization needed\n");

}

 

int main()
{
	 int k, num_cluster,cluster, i, j, cur = 1;

	 scanf("%d%d", &n, &k);

	 memset(position,0, sizeof(position));
	 memset(visited,false, sizeof(visited));

	 flag = 0;

	 for (i = 1;i <= k; i++)
	 {
			scanf("%d",&num_cluster);
			for (j= 1; j <= num_cluster; j++)
			{
				   scanf("%d",&cluster);
				   position[cluster]= cur++;
			}
	 }
 
	 solve();

	 return 0;

}
//*/



/*         244K	188MS	C++	1609B
//          244K	110MS	C++	1883B(省掉  // 找最后空闲的位)
#include <iostream>

using namespace std;

int n,k,tmp,t,index,pi;
int q[10000];
int d[10000];
bool optneed;

int main()
{
	int i;
	 optneed=false;
	 memset(q,-1,10000*sizeof(int));
	 memset(d,-1,10000*sizeof(int));

	 //freopen("t.txt","rt",stdin);
	 //freopen("out.txt","w",stdout);

	 scanf("%d%d",&n,&k);
	 int counter=0;
	 for(int j=0;j<k;j++)
	 {
		 scanf("%d",&t);
		 for(int i=0;i<t;i++)
		 {
			  scanf("%d",&tmp);
			  tmp--;
			  q[tmp]=counter;   //用来记录该盘块应放位置
			  d[counter]=tmp;   //用来记录第i盘块所放位置
			  counter++;
		 }
	 }

	 //put nodes whose correct place is empty and solve the chains.
	 for(i=0;i<n;i++)
	 {
		  if(q[i]==i||q[i]==-1) continue;
		  optneed=true;
		  if(q[q[i]]==-1)    // 应放位置为空，可以放入
		  {
			  printf("%d %d\n",i+1,q[i]+1);
			  q[q[i]]=q[i];q[i]=-1;  // 当前位置 -> 应放位置 ，当前位置设为空
			  index=i;           
			  while(d[index]!=-1)   // 不断补位    dfs的味道
			  {
				  printf("%d %d\n",d[index]+1,index+1);
				  q[d[index]]=-1;q[index]=index;
				  index=d[index];
			  }
		  }
	 }
	 if(optneed==true)
	 {
		 //solve the rings
		 for(int i=0;i<n;i++)
		 {
			  if(q[i]==i||q[i]==-1) continue;
			  index=i;
			  //for(tmp=n-1;tmp>=0;tmp--) if(q[tmp]==-1) break;  // 找最后空闲的位
			  tmp = n - 1;
			  printf("%d %d\n",i+1,tmp+1);
			  q[tmp]=q[i];q[index]=-1;
			  while(index!=q[tmp])      // 不断补位，直到被抽到 最后的那个数 放回原位
			  {                                                     //
				  printf("%d %d\n",d[index]+1,index+1);            //
				  q[index]=index;q[d[index]]=-1;                  //
				  index=d[index];                                // 
			  }                                                 //
			  printf("%d %d\n",tmp+1,index+1);   // <===========            
			  q[index]=q[tmp];q[tmp]=-1;
		 }
	 }
	 else
		printf("No optimization needed\n");

	 //system("pause");
	 return 0;
}
//*/

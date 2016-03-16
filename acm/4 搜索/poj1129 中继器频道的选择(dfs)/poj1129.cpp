/*          224K	16MS	C++	1064B
#include<iostream>
#include<vector>

using namespace std;

int main()
{
	int cn;
	int i, j, k;
	char tmp;

	while( cin >> cn && cn!=0 )
	{
		vector<int> mp[30];
		tmp = cin.get();
		for(i=0; i<cn; i++)
		{
			tmp = cin.get();   //scanf("%c", &tmp);
			tmp = cin.get();
			while(tmp = cin.get())
			{
				if(tmp==10)  break;
				int a = tmp-65;
				mp[i].push_back(a);
			}
		}
		
		//for(i=0; i<cn; i++)
		//{
		//	for(j=0; j<mp[i].size(); j++)
		//		cout << mp[i][j] << " ";
		//	cout << endl;
		//}
		

		int color[30] = {0};
		for(i=0; i<cn; i++)
		{
			for(k=1; k<5; k++)
			{
				int key = 0;
				for(j=0; j<mp[i].size(); j++)
				{
					if(color[mp[i][j]]==k)
					{
						key = 1;
						break;
					}
				}
				if(key==1)
					continue;
				else
				{
					color[i] = k;
					break;
				}
			}
		}

		int ans = 0;
		for(i=0; i<cn; i++)
		{
			if(ans<color[i])
				ans = color[i];
		}
		
		if(ans!=1)
			cout << ans << " channels needed." << endl;
		else
			cout << "1 channel needed." << endl;
		 
	}

	return 0;
}
//*/






/*      160K	0MS	    C++	1500B
//*      160K	16MS	C++	1471B    
#include <iostream>
#include <cstdio>
#include <cstring>
 
using namespace std;
 
bool map[26][26];
int n;
int color[26];
int color_index;
int min_color;
 
bool isOk(int depth, int clr)
{
    for(int i=0; i<n; i++)
    {
        if(map[depth][i] && color[i]==clr)
        {
            return false;
        }
    }
    return true;
}
 
void DFS(int depth)
{
    if(color_index>min_color)   //  ����ȵ�20��֮��һ���Ѿ��������ɫ��������δ��20��ķ�֧��Ҫ�ϵ���
    {
        return;
    }
    if(depth>=n)
    {
        if(min_color>color_index)
        {
            min_color=color_index;
        }
        return;
    }
 
    for(int k=1; k<=color_index; k++)  // ֻ��֮ǰ�ù�����ɫ
    {
        if(isOk(depth,k))
        {
            color[depth]=k;
            DFS(depth+1);
            color[depth]=0;
        }
    }

    // ���µ���ɫ
    color_index++;
    color[depth]=color_index;
    DFS(depth+1);
    color[depth]=0;
    color_index--;
 
}
 
int main()
{
    char temp[32];
 
    while(scanf("%d",&n) && n)
    {
        memset(map,0,sizeof(map));
        memset(color,0,sizeof(color));
        color_index=1;
        min_color=99999;
        for(int i=0; i<n; i++)
        {
            scanf("%s",temp);
            for(int j=2; temp[j]!='\0'; j++)
            {
                map[i][temp[j]-'A']=true;
            }
        }
        DFS(0);
        if(min_color==1)
            printf("%d channel needed.\n",min_color);
        else
            printf("%d channels needed.\n",min_color);
    }
    return 0;
}
//*/



/*   ̰��+dfs��        240K	0MS	C++	1081B  
#include<iostream>
#include<stack>

using namespace std;


int maze[26][26];
int n;
int sign[26];
int s_num;

int dfs()
{
	stack<int>s;
	s_num=1;
	memset(sign,0,sizeof(sign));
	for(int i=0;i<n;i++)   // ÿ�ε�s_num�������п���ȾΪ��ͬ��ɫ�Ķ���ֵ����sign[ i ]�� ��಻����4�Ρ�
	{
		if(sign[i]==0)
		{
			s.push(i);
			sign[i]=s_num++;
			while(!s.empty())
			{
				int p=s.top();  s.pop();
				int k=0;
				for(int j=0;j<n;j++)
				{
					if(maze[p][j]==1 && sign[j]==0)   // ��ֵΪ-1��Ŀ���ǽ�ֹͬ���������������
						sign[j]=-1;
					if(j!=p && maze[p][j]==0 && sign[j]==0 && k==0) //kΪ��ÿ��ֻ��һ����ջ
					{
						s.push(j);
						sign[j]=sign[p];
						k=1;
					}
				}
			}
		}

		for(int j=0;j<n;j++)
			if(sign[j]==-1)
			{
				sign[j]=0;
			}
	}

	return s_num-1;
}

int main()
{
	char c;
	cin>>n;
	while(n)
	{
		c=getchar();
		memset(maze,0,sizeof(maze));
		for(int i=0;i<n;i++)
		{
			int flag=0;
			c=getchar();
			while(c!='\n')
			{
				if(c==':')flag=1;
				if(flag==1&&c>='A'&&c<='Z')
				maze[i][c-'A']=1;
				c=getchar();
			}
		}
		int ans=dfs();

		if(ans<=1)
			printf("%d channel needed.\n",ans);
		else 
			printf("%d channels needed.\n",ans);
		cin>>n;
	}
	return 0;
}
//*/




//*��ɫ����_Ⱦɫ�㷨��  236K	16MS	C++	1210B
#include<iostream>
using namespace std;

int maze[26][26];
int color[26];
int num;

bool ok(int k)
{
	for(int j=0;j<k;j++)
	{
		if(maze[k][j]==1&&color[j]==color[k])
		return false;
	}
	return true;
}

int GraphColor(int n,int m)
{
	memset(color,0,sizeof(color[0])*n);
	int k=0;
	while(k>=0)
	{
		color[k]=color[k]+1;
		while(color[k]<=m)
		{
			if(ok(k))
				break;
			else
				color[k]=color[k]+1;
		}
		if(color[k]<=m&&k==n-1)
			return 1;
		else if(color[k]<=m&&k<n-1)
			k=k+1;
		else                                     // ����
		{
			color[k]=0;
			k=k-1;
		}
	}
	return 0;
}

int solve()
{
	int tag=0;
	for(int i=0;i<num;i++)
		for(int j=i+1;j<num;j++)
		if(i!=j&&maze[i][j]==1)
		{
			tag=1;break;
		}

	if(tag==0)
		return 1;
	for(int k=2;k<=4;k++)
	{
		if(GraphColor(num,k))
		return k;
	}
}

int main()
{
char c;
cin>>num;
while(num){
c=getchar();
memset(maze,0,sizeof(maze));
for(int i=0;i<num;i++){
int flag=0;
c=getchar();
while(c!='\n'){
if(c==':')flag=1;
if(flag==1&&c>='A'&&c<='Z')
maze[i][c-'A']=1;
c=getchar();
}
}
int ans=solve();
if(ans<=1)
printf("%d channel needed.\n",ans);
else 
printf("%d channels needed.\n",ans);
cin>>num;
}
return 0;
}

//*/
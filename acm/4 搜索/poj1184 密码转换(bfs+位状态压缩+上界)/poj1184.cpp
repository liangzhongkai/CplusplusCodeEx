/*   1348K	32MS	C++	2718B

#include<iostream>
#include<queue>
#include<cmath>

using namespace std;

struct point
{
	int node;
	int step;
	int last;
	bool find;
};

int start[6], end[6]; 
bool vis[10000000];

int change1(point n)
{
	int ans = 0;
	int i;
	int mm[6];
	int tn = n.node/10;
	for(i=5; i>=0; i--)
	{
		mm[i] = tn%10;
		tn /= 10;
	}

	i = mm[0];
	mm[0] = mm[n.node%10];
	mm[n.node%10] = i;

	for(i=0; i<6; i++)
	{
		ans = ans*10 + mm[i];
	}
	ans = ans*10 + n.node%10;
	return ans;
}

int change6(point n)
{
	int ans = 0;
	int i;
	int mm[6];
	int tn = n.node/10;
	for(i=5; i>=0; i--)
	{
		mm[i] = tn%10;
		tn /= 10;
	}

	i = mm[5];
	mm[5] = mm[n.node%10];
	mm[n.node%10] = i;

	for(i=0; i<6; i++)
	{
		ans = ans*10 + mm[i];
	}
	ans = ans*10 + n.node%10;
	return ans;
}

int cal(point n)
{
	int mm[7];
	int i;
	int ans = 0;
	int num = n.node/10;

	for(i=5; i>=0; i--)
	{
		mm[i] = num%10;
		num = num/10;
	}
	if(n.find)
	{
		for(i=0; i<5; i++)     // 这里的5呀，坑人！
			if(mm[i]!=end[i])
			{
				if(i>n.last)
					return 9999999;
				ans += abs(mm[i]-end[i]);
			}
		ans += abs(mm[5]-end[5]);
	}
	else
	{
		for(i=0; i<6; i++)
			if(mm[i]!=end[i])
			{
				if(i>n.last)
					return 9999999;
				ans += abs(mm[i]-end[i]);
			}
	}
	return ans;
}

int main()
{
	int s1, s2;
	int i;

	cin >> s1 >> s2;

	point tmp;
	tmp.node = s1*10;
	tmp.step = 0;
	tmp.last = 0;
	tmp.find = false;

	for(i=5; i>=0; i--)
	{
		start[i] = s1%10;
		s1/=10;
		end[i] = s2%10;
		s2/=10;
	}

	queue<point> q;
	q.push(tmp);
	vis[tmp.node] = true;

	int up;  // 上界
	up = cal(tmp);

	while(!q.empty())
	{
		point temp;
		temp = q.front();
		q.pop();

		if(temp.step>=up)    // 坑人！
			 break;
		int p = temp.node%10;
		if(p!=0)
		{
			tmp = temp;
			tmp.step++;
			tmp.node--;
			if(!vis[tmp.node])
			{
				q.push(tmp);
				vis[tmp.node] = true;
			}

			tmp = temp;
			tmp.step++;
			tmp.node = change1(tmp);
			if(!vis[tmp.node])
			{
				q.push(tmp);
				vis[tmp.node] = true;
				up = up>(cal(tmp)+tmp.step)?(cal(tmp)+tmp.step):up;   //// 坑人！
			}
		}
		if(p!=5)
		{
			tmp = temp;
			tmp.step++;
			tmp.node++;
			tmp.last = tmp.last>(tmp.node%10)?tmp.last:(tmp.node%10);  //// 坑人！
			if(!vis[tmp.node])
			{
				q.push(tmp);
				vis[tmp.node] = true;
				up = up>(cal(tmp)+tmp.step)?(cal(tmp)+tmp.step):up;
			}

			tmp = temp;
			tmp.step++;
			tmp.node = change6(tmp);
			tmp.find = true;   //// 坑人！
			if(!vis[tmp.node])
			{
				q.push(tmp);
				vis[tmp.node] = true;
				up = up>(cal(tmp)+tmp.step)?(cal(tmp)+tmp.step):up;
			}
		}
	}

	cout << up << endl;
	

	return 0;
}
//*/


/*            59012K	282MS	C++	5428B
#include<stdio.h>
#include<algorithm>
#include<queue>
#include<string.h>
#include<stdlib.h>


using namespace std;

bool used[6][10][10][10][10][10][10][10];

int start[6];
int end[6];
bool flag[6];

int in;

void setflag(int x,bool flag[])
{
    int i;
    for(i=0;i<6;i++)
         flag[i] = 0;
    if(x>=6)
     {
        int t = x - 6;
        for(i=0;i<=t;i++)
         {
             flag[i] = 1;
         }
         flag[5] = 1;
     }
    else
     {
        for(i=0;i<=x;i++)
         {
             flag[i] = 1;
         }
     }
}

int getflag(bool flag[])
{
    if(flag[0]&&!flag[1]&&!flag[2]&&!flag[3]&&!flag[4]&&!flag[5])    return 0;
    if(flag[0]&&flag[1]&&!flag[2]&&!flag[3]&&!flag[4]&&!flag[5])    return 1;
    if(flag[0]&&flag[1]&&flag[2]&&!flag[3]&&!flag[4]&&!flag[5])        return 2;
    if(flag[0]&&flag[1]&&flag[2]&&flag[3]&&!flag[4]&&!flag[5])        return 3;
    if(flag[0]&&flag[1]&&flag[2]&&flag[3]&&flag[4]&&!flag[5])        return 4;
    if(flag[0]&&flag[1]&&flag[2]&&flag[3]&&flag[4]&&flag[5])        return 5;
    if(flag[0]&&!flag[1]&&!flag[2]&&!flag[3]&&!flag[4]&&flag[5])    return 6;
    if(flag[0]&&flag[1]&&!flag[2]&&!flag[3]&&!flag[4]&&flag[5])        return 7;
    if(flag[0]&&flag[1]&&flag[2]&&!flag[3]&&!flag[4]&&flag[5])        return 8;
    if(flag[0]&&flag[1]&&flag[2]&&flag[3]&&!flag[4]&&flag[5])        return 9;
}

int cmp(int start[],int end[],bool flag[])
{
    int result = 0;
    int i;
    for(i=0;i<6;i++)
     {
        if(!flag[i] && start[i]!=end[i])
            return -1;
         result += abs(start[i]-end[i]);
     }
    return result;
}

struct pp
{
    int start[6];
    int cur;
    int to;
    int step;
};

queue<pp> my;

void dfs(void)
{
    while(!my.empty())
         my.pop();
     pp temp;
     temp.cur = 0;
     temp.to = 0;
     temp.step = 0;
     memcpy(temp.start,start,sizeof(temp.start));
     my.push(temp);
    while(!my.empty())
     {
         temp = my.front();
         my.pop();
         setflag(temp.to,flag);
        int t = cmp(temp.start,end,flag);
        if(t!=-1)                                         // 判断是否能只通过加减得出目标状态
             in = in < temp.step + t ? in : temp.step + t;
        if(temp.cur>0)
         {
             swap(temp.start[0],temp.start[temp.cur]);
            if(!used[temp.cur][temp.start[0]][temp.start[1]][temp.start[2]][temp.start[3]][temp.start[4]][temp.start[5]][temp.to])
             {
                 temp.step++;
                 used[temp.cur][temp.start[0]][temp.start[1]][temp.start[2]][temp.start[3]][temp.start[4]][temp.start[5]][temp.to] = 1;
                 my.push(temp);
                 temp.step--;   // 不是回溯，只是为了恢复原貌，作其他的转变
             }
             swap(temp.start[0],temp.start[temp.cur]);
         }
        if(temp.cur<5)
         {
             swap(temp.start[5],temp.start[temp.cur]);
            bool tt = flag[5];
             flag[5] = 1;
             temp.to = getflag(flag);
            if(!used[temp.cur][temp.start[0]][temp.start[1]][temp.start[2]][temp.start[3]][temp.start[4]][temp.start[5]][temp.to])
             {
                 temp.step++;
                 used[temp.cur][temp.start[0]][temp.start[1]][temp.start[2]][temp.start[3]][temp.start[4]][temp.start[5]][temp.to] = 1;
                 my.push(temp);
                 temp.step--;
             }
             flag[5] = tt;
             temp.to = getflag(flag);
             swap(temp.start[5],temp.start[temp.cur]);
         }
        if(temp.cur<5)
         {
             temp.cur++;
            bool tt = flag[temp.cur];
             flag[temp.cur] = 1;
             temp.to = getflag(flag);
            if(!used[temp.cur][temp.start[0]][temp.start[1]][temp.start[2]][temp.start[3]][temp.start[4]][temp.start[5]][temp.to])
             {
                 temp.step++;
                 used[temp.cur][temp.start[0]][temp.start[1]][temp.start[2]][temp.start[3]][temp.start[4]][temp.start[5]][temp.to]=1;
                 my.push(temp);
                 temp.step--;
             }
             flag[temp.cur] = tt;
             temp.to = getflag(flag);
             temp.cur--;
         }
        if(temp.cur>0)
         {
             temp.cur--;
            bool tt = flag[temp.cur];
             flag[temp.cur] = 1;
             temp.to = getflag(flag);
            if(!used[temp.cur][temp.start[0]][temp.start[1]][temp.start[2]][temp.start[3]][temp.start[4]][temp.start[5]][temp.to])
             {
                 temp.step++;
                 used[temp.cur][temp.start[0]][temp.start[1]][temp.start[2]][temp.start[3]][temp.start[4]][temp.start[5]][temp.to]=1;
                 my.push(temp);
                 temp.step--;
             }
             flag[temp.cur] = tt;
             temp.to=getflag(flag);
             temp.cur++;
         }
     }
}

int main(void)
{
    char Start[10],End[10];
    while(scanf("%s%s",Start,End)==2)
     {
        int i;
        if(strcmp(Start,End)==0)
         {
             puts("0");
            continue;
         }
        for(i=0;i<6;i++)
         {
             start[i] = Start[i] - '0';
             end[i] = End[i] - '0';
         }
         memset(used,0,sizeof(used));
         in = 0x7fffffff;
         used[0][start[0]][start[1]][start[2]][start[3]][start[4]][start[5]][0] = 1;
         dfs();
         printf("%d\n",in);
     }
    return 0;
}
//*/









/*        10036K	79MS	C++	3413B

#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

#define N 1000000

int start, end, v[6];
bool s[N][10];

struct node
{
    int state;//当前状态
    int step;//移动步数
    int visited;//光标到达过的位置

//0:0
//1:0, 1
//2:0, 1, 2
//3:0, 1, 2, 3
//4:0, 1, 2, 3, 4
//5:0, 5
//6:0, 1, 5
//7:0, 1, 2, 5
//8:0, 1, 2, 3, 5
//9:0, 1, 2, 3, 4, 5

};

void toArray(int n, int *v)
{
    for (int i = 5; i >= 0; i--)
    {
        v[i] = n % 10;
        n /= 10;
    }
}

int toNum(int *v)
{
    int ans, i;

    for (i = 0, ans = 0; i < 6; i++)
        ans = ans * 10 + v[i];
   
    return ans;
}

//pos1:0 or 5, pos2:当前光标位置
int swapNum(int pos1, int pos2, int *v)
{
    int tmp, ans;

    //swap pos1 and pos2
    tmp = v[pos1];
    v[pos1] = v[pos2];
    v[pos2] = tmp;

    ans = toNum(v);

    //把数组恢复原样
    tmp = v[pos1];
    v[pos1] = v[pos2];
    v[pos2] = tmp;

    return ans;
}

int check(node& in)
{
    int tmp, res, i, a[6];

    toArray(in.state, a);
   
    tmp = in.visited;
    if (tmp <= 4)
    {
        for (i = tmp + 1; i < 6; i++)       
            if (a[i] != v[i]) return -1;

        for (res = 0, i = 0; i <= tmp; i++)
            res += abs(a[i] - v[i]);
    }
    else
    {
        tmp -= 5;
        for (i = tmp + 1; i < 5; i++)   
            if (a[i] != v[i]) return -1;

        for (res = 0, i = 0; i <= tmp; i++)
            res += abs(a[i] - v[i]);   
       
        res += abs(a[5] - v[5]);
    }

    return res;
}

int BFS()
{
    queue<node> q;
    node p;
    int ori, visited, tmp, a[6], res, minimum = N;
    memset(s, false, sizeof(s));

    p.state = start;
    p.step = 0;
    p.visited = 0;
    q.push(p);
    s[start][0] = true;

    while (!q.empty())
    {
        p = q.front();
        q.pop();

        ori = p.state;
        visited = p.visited;
        res = check(p);

        if (res != -1)
        {
            if (minimum > res + p.step) minimum = p.step + res;
        }

        p.step++;
        if (p.step >= minimum) continue;//剪枝

        toArray(p.state, a);
        //swap0
        if (p.visited > 0)
        {
            if (p.visited >= 5) tmp = swapNum(0, p.visited - 5, a);
            else tmp = swapNum(0, p.visited, a);

            if (!s[tmp][p.visited])
            {
                p.state = tmp;
                q.push(p);
                s[tmp][p.visited] = true;
            }
        }

        //swap1
        if (p.visited < 5)
        {
            tmp = swapNum(5, p.visited, a);
            p.visited += 5;           
        }
        else tmp = swapNum(5, p.visited - 5, a);

        if (!s[tmp][p.visited])
        {
            p.state = tmp;               
            q.push(p);
            s[tmp][p.visited] = true;
        }       

        //right
        p.state = ori;
        p.visited = visited;
        if (p.visited < 5)
        {           
            p.visited++;
            if (!s[p.state][p.visited]) q.push(p);
        }
        else if (p.visited < 9)
        {
            p.visited++;
            if (!s[p.state][p.visited]) q.push(p);
        }
    }

    return minimum;
}

int main()
{
    while (cin >> start >> end)
    {
        toArray(end, v);

        cout << BFS() << endl;
    }

    return 0;
}
//*/







/*             1300K	0MS  	C++ 	3243B

#include<stdio.h>
#include<math.h>

typedef struct
{
        int data;   //  数字 + 位置
        int last;   //  已访问了多少位
        int step;   //  步数
        bool find;  //  针对与第六位交换的操作
}node;

node q[100000];
int h=0,r=0,st,e,std[7];

int max(int x,int y)
{
    return x>y?x:y;
}
int min(int x,int y)
{
    return x<y?x:y;
}
bool empty()
{
     return h==r?1:0;
}
node pop()
{
     h=(++h)%100000;
     return q[h];
}
void push(node pos)
{
     r=(++r)%100000;
     q[r]=pos;
}
bool used[10000000];

void change1(node *pos)
{
     int s[7];
     int i,num=pos->data/10;
     for(i=6;i>=1;i--)
     {
        s[i]=num%10;
        num/=10;
     }

     int temp=s[1];
     s[1]=s[pos->data%10];
     s[pos->data%10]=temp;

     num=0;
     for(i=1;i<=6;i++)
        num=num*10+s[i];
     pos->data=num*10+pos->data%10;
}

void change2(node *pos)
{
     int s[7];
     int i,num=pos->data/10;
     for(i=6;i>=1;i--)
     {
        s[i]=num%10;
        num/=10;
     }
     int temp=s[6];
     s[6]=s[pos->data%10];
     s[pos->data%10]=temp;
     num=0;
     for(i=1;i<=6;i++)
        num=num*10+s[i];
     pos->data=num*10+pos->data%10;
     pos->find=1;    
}

int cal(node pos)    // 当前状态变成目标状态最多的步数
{
     int s[7],total=0;
     int i,num=pos.data/10;
     for(i=6;i>=1;i--)
     {
        s[i]=num%10;   
        num/=10;
     }
     if(!pos.find)        //  已被访问过的才加上
     {                    //  未被访问过的，如果不相等，就默认999999步。
        for(i=1;i<=6;i++)
          if(s[i]!=std[i])
            {
               if(i>pos.last)
				   return 999999;
               total+=abs(s[i]-std[i]);  
            }
        return total;
     }
     else
     {
         for(i=1;i<6;i++)
          if(s[i]!=std[i])
            {
               if(i>pos.last)
				   return 999999;
               total+=abs(s[i]-std[i]);
            }
        total+=abs(s[6]-std[6]);
        return total;
     }
	 
}

int main()
{
    int i;
    scanf("%d %d",&st,&e);
    for(i=6;i>=1;i--) 
           std[i]=e%10,e/=10;

    node now,pos;
    int up=9999999;

    now.data=st*10+1;
    now.find=0;
    now.last=1;
    now.step=0;

    used[now.data]=1;
    push(now);
    up=min(cal(now),up);    //  这个up是 上界

    while(!empty())
    {
		  pos=pop();
		  if(pos.step>=up)    //  高效之处！！！
			  break;
		  int p = pos.data%10;   //  p为移到第几位
		  if(p!=1)
		  {
			  //  向左移位
			  now=pos;
			  now.step++;
			  now.data--;
			  if(!used[now.data]) 
			  {
				  push(now);
				  used[now.data]=1;
			  }
			  //  与第一位交换
			  now=pos;
			  now.step++;
			  change1(&now);
			  if(!used[now.data])
			  {
				  push(now);
				  used[now.data]=1;
				  up=min(cal(now)+now.step,up);   //  cal(now)是计算增加减少这两个操作的次数
			  }
		  }
		  if(p!=6)
		  {
			  //  向右移位
			  now=pos;
			  now.step++;
			  now.data++;
			  now.last=max(now.last,now.data%10);
			  if(!used[now.data])
			  {
				  push(now);
				  used[now.data]=1;
				  up=min(cal(now)+now.step,up);
			  }
			  //  与第六位交换
			  now=pos;
			  now.step++;
			  change2(&now);
			  if(!used[now.data]) 
			  {
				  push(now);
				  used[now.data]=1;
				  up=min(cal(now)+now.step,up);
			  }
		  }
    }
    printf("%d\n",up);
    return 0;
}
//*/







/*       2968K	32MS	C++	4337B

#include<iostream>
#include<queue>
#include<cmath>
using namespace std;

class oper  //记录每步操作情况(只针对移位和换位操作，并不包括值大小的改变操作)，得到所有排列的状态
{
public:
	int num[6];  //第step步操作后的 "数字串"
	int state;  //第step步操作后对 "数字串各个位置的访问状态" ,其值对应VistState的行数，分别为0~9
	int pos;  //第step步操作后 "光标在数字串中的位置" ，分别为0~5
	int step; //当前操作的 "步数"
};

int VistState[10][6]=    //访问状态数组，通过swap0、swap1与右移操作得到的"数字串各个位置的访问状态"
{                        //一行代表一种访问状态，1表示数字串该位置被访问了，0表示没有访问

	1,0,0,0,0,0,  //访问状态0: 初始状态(pos=0)
	1,1,0,0,0,0,  //访问状态1: 状态0通过右移操作得到(pos=1)，或者状态1通过swap0操作得到(pos=1)
	1,1,1,0,0,0,  //访问状态2: 状态1通过右移操作得到(pos=2)，或者状态2通过swap0操作得到(pos=2)
	1,1,1,1,0,0,  //访问状态3: 状态2通过右移操作得到(pos=3)，或者状态3通过swap0操作得到(pos=3)
	1,1,1,1,1,0,  //访问状态4: 状态3通过右移操作得到(pos=4)，或者状态4通过swap0操作得到(pos=4)
	1,0,0,0,0,1,  //访问状态5: 状态0通过swap1操作得到(pos=0)，或者状态5通过swap0操作得到(pos=0)
	1,1,0,0,0,1,  //访问状态6: 状态1通过swap1操作得到(pos=1)，或者状态5通过右移操作得到(pos=1),或者状态6通过swap0操作得到(pos=1)
	1,1,1,0,0,1,  //访问状态7: 状态2通过swap1操作得到(pos=2)，或者状态6通过右移操作得到(pos=2),或者状态7通过swap0操作得到(pos=2)
	1,1,1,1,0,1,  //访问状态8: 状态3通过swap1操作得到(pos=3)，或者状态7通过右移操作得到(pos=3),或者状态8通过swap0操作得到(pos=3)
	1,1,1,1,1,1   //访问状态9: 状态4通过swap1操作得到(pos=4)，或者状态8通过右移操作得到(pos=4),或者状态9通过右移操作得到(pos=5),
	              //           或者状态4通过右移操作得到(pos=5)，或者状态9通过swap0操作得到，或者状态9通过swap1操作得到
};   
     //不难注意到:swap0操作前后,光标位置pos不变,访问状态不变 ; swap0操作前后,pos不变;
     //           右移操作后,pos+1  ; 无需左移操作                                   

int comb[720][8];                    //记录某个数字串num的全部排列组合情况(各个数字值不变，位置不同)，共6!=720种
                                     //comb[][0~5]=num[0~5], comb[][6]=state , comb[][7]=step
int idx=0;                           //comb的行索引
bool vist[6][6][6][6][6][6][6][10];  //标记出现过的状态，前6维为数字串num[]，第7维为光标所在的位置pos，第8维为访问状态state

bool CheckVist(oper* a)             //状态检查
{
	int* p=a->num;
	return vist[*p][*(p+1)][*(p+2)][*(p+3)][*(p+4)][*(p+5)][a->pos][a->state];
}

void ChangeVist(oper* a)            //状态变更
{
	int* p=a->num;
	vist[*p][*(p+1)][*(p+2)][*(p+3)][*(p+4)][*(p+5)][a->pos][a->state]=true;
	return;
}

void BFS(void)                      //搜索所有"通过位移和换位操作"得到的排列组合状态
{
	oper a,b;
	queue<oper> Q;
	
	for(int i=0;i<6;i++)
		a.num[i]=i;
	a.pos=a.state=a.step=0;

	Q.push(a);  //入队
	ChangeVist(&a);

	while(!Q.empty())
	{
		a=Q.front(); //取队尾
		Q.pop();  //队尾元素出队

		//记录所有组合情况

		for(int k=0;k<6;k++)
		{
			comb[idx][k]=a.num[k];
		//	cout << a.num[k];
		}
		//cout << " " << a.state;
		//cout << "  ";
		comb[idx][6]=a.state;
		comb[idx++][7]=a.step;

		if(a.pos>0)  //swap0操作前提条件，注意swap0操作前后的访问状态不变，光标位置也不变
		{            //因此无需处理b.state与b.pos
			//swap0操作

			b=a;  //备份
			b.step=a.step+1;
			swap(b.num[0],b.num[b.pos]);  //交换num第0位与第pos位
			if(!CheckVist(&b))  //状态检查
			{
				ChangeVist(&b);
				Q.push(b);    //入队
			}
		}

		if(a.pos<5)  //右移right或swap1操作前提条件
		{
			//right操作，注意光标位置pos会改变
			b=a;
			b.step=a.step+1;
			b.pos++;
			if(b.state<9)
				b.state++;      //依据状态数组而得 

			if(!CheckVist(&b))  //状态检查
			{
				ChangeVist(&b);
				Q.push(b);      //入队
			}


			//swap1操作,注意光标位置pos不变
			b=a;
			b.step=a.step+1;
			swap(b.num[5],b.num[b.pos]);  //交换num第5位与第pos位
			if(b.state<5)
				b.state+=5;               //依据状态数组而得

			if(!CheckVist(&b))            //状态检查
			{
				ChangeVist(&b);
				Q.push(b);                //入队
			}
		}
	}
	return;
}


int main(void)
{
	memset(vist,false,sizeof(vist)); 
	BFS();                           //预处理: 对每一种排列和光标到达情况，求出最少需要"移位和换位的操作数"。(此过程与输入无关)

	char Init_ANum[6];               //初始字符串
	int Init_DNum[6];                //初始数字串
	char Aim_ANum[6];                //目标字符串
	int Aim_DNum[6];                 //目标数字串
	
	while(cin>>Init_ANum>>Aim_ANum)
	{
		for(int k=0;k<6;k++)         //字符串转换为数字串
		{
			Init_DNum[k]=Init_ANum[k]-'0';
			Aim_DNum[k]=Aim_ANum[k]-'0';
		}

		int MinOper = 1000000;        //从str得到aim最少需要的操作数
		for(int i=0;i<idx;i++)
		{
			int cnt=comb[i][7];       //comb[i][7]=step,为移位和换位的总操作数
			bool flag=true;
			for(int j=0;j<6;j++)
			{                         //comb[i][6]=state
				if(!VistState[ comb[i][6] ][j] && (Init_DNum[ comb[i][j] ]!=Aim_DNum[j]))  //如果这种状态的某位没被操作过，而且这位数字不等于目标状态的那位数字
				{                                                                          // comb[i] 使 Init_DNum一瞬间 发生了 comb[i][7] 次的变化。 
					flag=false;       //  这个state不行。
					break;
				}
				else
					cnt+=abs(Init_DNum[ comb[i][j] ] - Aim_DNum[j]);                       //该位置被操作过，值改变的次数(每一改变1)就是操作数
			}

			if(flag)
				MinOper=MinOper<cnt?MinOper:cnt;
		}

		cout << MinOper << endl;
	}

	return 0;
}
//*/









/*有的解题报告说光标不用左移 真心错的 000159 000519 这组答案是 8 哦
//  11684K	172MS	C++	3483B

#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<time.h>
#include<string.h>

#define sf scanf
#define pf printf
#define wh while
#define st struct
#define me memset
#define spf sprintf
#define ssf sscanf
#define inf 2147483647
#define lnf (1LL<<60)
#define ll long long
#define ull unsigned long long
#define tmax( a,b ) ( (a)>(b)?(a):(b) )
#define tmin( a,b ) ( (a)<(b)?(a):(b) )

//pf("%d ms\n",clock());

using namespace std;

int t,n,m,cas;

const int bit[7]={1,2,4,8,16,32};

const int all[10]={1,3,7,15,31,63,33,35,39,47};

int vis[6][6][6][6][6][6][6][10];

char in[7],out[7];

int a[7],b[7],c[7];

st p
{
    int f[6];
    int x,t,pos;
}now,nt;

queue<p>q;

vector<p>w;

inline int to(int x)
{
    for(int j=0;j<10;j++)
        if( x==all[j] )
			return j;
}

inline void insert(p nt)
{
    if( vis[ nt.f[0] ][ nt.f[1] ][ nt.f[2] ][ nt.f[3] ][ nt.f[4] ][ nt.f[5] ][ nt.pos ][ to(nt.x) ]==-1 )
    {
        vis[ nt.f[0] ][ nt.f[1] ][ nt.f[2] ][ nt.f[3] ][ nt.f[4] ][ nt.f[5] ][ nt.pos ][ to(nt.x) ]=nt.t;
        q.push(nt);
        w.push_back(nt);
    }
}

void initbfs()
{
    wh(!q.empty())
    {
        now=q.front();q.pop();

        nt.t=now.t+1;

        if( now.pos>0 )
        {
            memcpy( nt.f,now.f,sizeof( now.f ) );

            nt.pos=now.pos-1;

            nt.x=( now.x|bit[ nt.pos ] );

            insert(nt);

            nt.pos=now.pos;

            nt.x=( now.x|bit[0] );

            int tmp=nt.f[0];

            nt.f[0]=nt.f[ nt.pos ];

            nt.f[ nt.pos ]=tmp;

            insert(nt);
        }
        if( now.pos<5 )
        {
            memcpy( nt.f,now.f,sizeof( now.f ) );

            nt.pos=now.pos+1;

            nt.x=( now.x|bit[ nt.pos ] );

            insert(nt);

            nt.pos=now.pos;

            nt.x=( now.x|bit[5] );

            int tmp=nt.f[5];

            nt.f[5]=nt.f[ nt.pos ];

            nt.f[ nt.pos ]=tmp;

            insert(nt);
        }
    }
}

void init()
{
    wh(!q.empty()) q.pop();
    w.clear();

    me( vis,-1,sizeof(vis));

    now.t=now.pos=0;

    now.x=1;

    for(int j=0;j<6;j++)
		now.f[j]=j;
    
    q.push(now);

    w.push_back(now);

    vis[ now.f[0] ][ now.f[1] ][ now.f[2] ][ now.f[3] ][ now.f[4] ][ now.f[5] ][ now.pos ][ to(now.x) ]=now.t;

    initbfs();

}

void trans()
{
    for(int i=0;i<6;i++)
    {
        a[i]=in[i]-'0';
        b[i]=out[i]-'0';
    }
}

void sov()
{
	int i, j;
    int ans=inf;
    if( strcmp( in,out )==0 ) ans=0;
    else
    {
        int cal,wlen=w.size(),x;

        for(i=0;i<wlen;i++)
        {
            for(j=0;j<6;j++)
				c[j]=a[ w[i].f[j] ];
            cal=w[i].t;
            x=w[i].x;
            bool f=1;

            for(j=0;j<6;j++)
                if( x&bit[j] ) cal+=abs( c[j]-b[j] );
                else if( c[j]!=b[j] )
                {
                    f=0;
                    break;
                }

            if(f) ans=tmin( ans,cal );
        }
    }
    pf("%d\n",ans);
}

int main(void)
{   
    //freopen("in.txt","r",stdin);freopen("out.txt","w",stdout);
    init();
    wh( sf("%s%s",in,out)>0 )
    {
        trans();

        sov();
    }

    return 0;
}

//*/
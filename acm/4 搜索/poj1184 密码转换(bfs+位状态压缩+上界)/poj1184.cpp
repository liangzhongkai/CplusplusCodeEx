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
		for(i=0; i<5; i++)     // �����5ѽ�����ˣ�
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

	int up;  // �Ͻ�
	up = cal(tmp);

	while(!q.empty())
	{
		point temp;
		temp = q.front();
		q.pop();

		if(temp.step>=up)    // ���ˣ�
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
				up = up>(cal(tmp)+tmp.step)?(cal(tmp)+tmp.step):up;   //// ���ˣ�
			}
		}
		if(p!=5)
		{
			tmp = temp;
			tmp.step++;
			tmp.node++;
			tmp.last = tmp.last>(tmp.node%10)?tmp.last:(tmp.node%10);  //// ���ˣ�
			if(!vis[tmp.node])
			{
				q.push(tmp);
				vis[tmp.node] = true;
				up = up>(cal(tmp)+tmp.step)?(cal(tmp)+tmp.step):up;
			}

			tmp = temp;
			tmp.step++;
			tmp.node = change6(tmp);
			tmp.find = true;   //// ���ˣ�
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
        if(t!=-1)                                         // �ж��Ƿ���ֻͨ���Ӽ��ó�Ŀ��״̬
             in = in < temp.step + t ? in : temp.step + t;
        if(temp.cur>0)
         {
             swap(temp.start[0],temp.start[temp.cur]);
            if(!used[temp.cur][temp.start[0]][temp.start[1]][temp.start[2]][temp.start[3]][temp.start[4]][temp.start[5]][temp.to])
             {
                 temp.step++;
                 used[temp.cur][temp.start[0]][temp.start[1]][temp.start[2]][temp.start[3]][temp.start[4]][temp.start[5]][temp.to] = 1;
                 my.push(temp);
                 temp.step--;   // ���ǻ��ݣ�ֻ��Ϊ�˻ָ�ԭò����������ת��
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
    int state;//��ǰ״̬
    int step;//�ƶ�����
    int visited;//��굽�����λ��

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

//pos1:0 or 5, pos2:��ǰ���λ��
int swapNum(int pos1, int pos2, int *v)
{
    int tmp, ans;

    //swap pos1 and pos2
    tmp = v[pos1];
    v[pos1] = v[pos2];
    v[pos2] = tmp;

    ans = toNum(v);

    //������ָ�ԭ��
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
        if (p.step >= minimum) continue;//��֦

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
        int data;   //  ���� + λ��
        int last;   //  �ѷ����˶���λ
        int step;   //  ����
        bool find;  //  ��������λ�����Ĳ���
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

int cal(node pos)    // ��ǰ״̬���Ŀ��״̬���Ĳ���
{
     int s[7],total=0;
     int i,num=pos.data/10;
     for(i=6;i>=1;i--)
     {
        s[i]=num%10;   
        num/=10;
     }
     if(!pos.find)        //  �ѱ����ʹ��Ĳż���
     {                    //  δ�����ʹ��ģ��������ȣ���Ĭ��999999����
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
    up=min(cal(now),up);    //  ���up�� �Ͻ�

    while(!empty())
    {
		  pos=pop();
		  if(pos.step>=up)    //  ��Ч֮��������
			  break;
		  int p = pos.data%10;   //  pΪ�Ƶ��ڼ�λ
		  if(p!=1)
		  {
			  //  ������λ
			  now=pos;
			  now.step++;
			  now.data--;
			  if(!used[now.data]) 
			  {
				  push(now);
				  used[now.data]=1;
			  }
			  //  ���һλ����
			  now=pos;
			  now.step++;
			  change1(&now);
			  if(!used[now.data])
			  {
				  push(now);
				  used[now.data]=1;
				  up=min(cal(now)+now.step,up);   //  cal(now)�Ǽ������Ӽ��������������Ĵ���
			  }
		  }
		  if(p!=6)
		  {
			  //  ������λ
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
			  //  �����λ����
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

class oper  //��¼ÿ���������(ֻ�����λ�ͻ�λ��������������ֵ��С�ĸı����)���õ��������е�״̬
{
public:
	int num[6];  //��step��������� "���ִ�"
	int state;  //��step��������� "���ִ�����λ�õķ���״̬" ,��ֵ��ӦVistState���������ֱ�Ϊ0~9
	int pos;  //��step�������� "��������ִ��е�λ��" ���ֱ�Ϊ0~5
	int step; //��ǰ������ "����"
};

int VistState[10][6]=    //����״̬���飬ͨ��swap0��swap1�����Ʋ����õ���"���ִ�����λ�õķ���״̬"
{                        //һ�д���һ�ַ���״̬��1��ʾ���ִ���λ�ñ������ˣ�0��ʾû�з���

	1,0,0,0,0,0,  //����״̬0: ��ʼ״̬(pos=0)
	1,1,0,0,0,0,  //����״̬1: ״̬0ͨ�����Ʋ����õ�(pos=1)������״̬1ͨ��swap0�����õ�(pos=1)
	1,1,1,0,0,0,  //����״̬2: ״̬1ͨ�����Ʋ����õ�(pos=2)������״̬2ͨ��swap0�����õ�(pos=2)
	1,1,1,1,0,0,  //����״̬3: ״̬2ͨ�����Ʋ����õ�(pos=3)������״̬3ͨ��swap0�����õ�(pos=3)
	1,1,1,1,1,0,  //����״̬4: ״̬3ͨ�����Ʋ����õ�(pos=4)������״̬4ͨ��swap0�����õ�(pos=4)
	1,0,0,0,0,1,  //����״̬5: ״̬0ͨ��swap1�����õ�(pos=0)������״̬5ͨ��swap0�����õ�(pos=0)
	1,1,0,0,0,1,  //����״̬6: ״̬1ͨ��swap1�����õ�(pos=1)������״̬5ͨ�����Ʋ����õ�(pos=1),����״̬6ͨ��swap0�����õ�(pos=1)
	1,1,1,0,0,1,  //����״̬7: ״̬2ͨ��swap1�����õ�(pos=2)������״̬6ͨ�����Ʋ����õ�(pos=2),����״̬7ͨ��swap0�����õ�(pos=2)
	1,1,1,1,0,1,  //����״̬8: ״̬3ͨ��swap1�����õ�(pos=3)������״̬7ͨ�����Ʋ����õ�(pos=3),����״̬8ͨ��swap0�����õ�(pos=3)
	1,1,1,1,1,1   //����״̬9: ״̬4ͨ��swap1�����õ�(pos=4)������״̬8ͨ�����Ʋ����õ�(pos=4),����״̬9ͨ�����Ʋ����õ�(pos=5),
	              //           ����״̬4ͨ�����Ʋ����õ�(pos=5)������״̬9ͨ��swap0�����õ�������״̬9ͨ��swap1�����õ�
};   
     //����ע�⵽:swap0����ǰ��,���λ��pos����,����״̬���� ; swap0����ǰ��,pos����;
     //           ���Ʋ�����,pos+1  ; �������Ʋ���                                   

int comb[720][8];                    //��¼ĳ�����ִ�num��ȫ������������(��������ֵ���䣬λ�ò�ͬ)����6!=720��
                                     //comb[][0~5]=num[0~5], comb[][6]=state , comb[][7]=step
int idx=0;                           //comb��������
bool vist[6][6][6][6][6][6][6][10];  //��ǳ��ֹ���״̬��ǰ6άΪ���ִ�num[]����7άΪ������ڵ�λ��pos����8άΪ����״̬state

bool CheckVist(oper* a)             //״̬���
{
	int* p=a->num;
	return vist[*p][*(p+1)][*(p+2)][*(p+3)][*(p+4)][*(p+5)][a->pos][a->state];
}

void ChangeVist(oper* a)            //״̬���
{
	int* p=a->num;
	vist[*p][*(p+1)][*(p+2)][*(p+3)][*(p+4)][*(p+5)][a->pos][a->state]=true;
	return;
}

void BFS(void)                      //��������"ͨ��λ�ƺͻ�λ����"�õ����������״̬
{
	oper a,b;
	queue<oper> Q;
	
	for(int i=0;i<6;i++)
		a.num[i]=i;
	a.pos=a.state=a.step=0;

	Q.push(a);  //���
	ChangeVist(&a);

	while(!Q.empty())
	{
		a=Q.front(); //ȡ��β
		Q.pop();  //��βԪ�س���

		//��¼����������

		for(int k=0;k<6;k++)
		{
			comb[idx][k]=a.num[k];
		//	cout << a.num[k];
		}
		//cout << " " << a.state;
		//cout << "  ";
		comb[idx][6]=a.state;
		comb[idx++][7]=a.step;

		if(a.pos>0)  //swap0����ǰ��������ע��swap0����ǰ��ķ���״̬���䣬���λ��Ҳ����
		{            //������账��b.state��b.pos
			//swap0����

			b=a;  //����
			b.step=a.step+1;
			swap(b.num[0],b.num[b.pos]);  //����num��0λ���posλ
			if(!CheckVist(&b))  //״̬���
			{
				ChangeVist(&b);
				Q.push(b);    //���
			}
		}

		if(a.pos<5)  //����right��swap1����ǰ������
		{
			//right������ע����λ��pos��ı�
			b=a;
			b.step=a.step+1;
			b.pos++;
			if(b.state<9)
				b.state++;      //����״̬������� 

			if(!CheckVist(&b))  //״̬���
			{
				ChangeVist(&b);
				Q.push(b);      //���
			}


			//swap1����,ע����λ��pos����
			b=a;
			b.step=a.step+1;
			swap(b.num[5],b.num[b.pos]);  //����num��5λ���posλ
			if(b.state<5)
				b.state+=5;               //����״̬�������

			if(!CheckVist(&b))            //״̬���
			{
				ChangeVist(&b);
				Q.push(b);                //���
			}
		}
	}
	return;
}


int main(void)
{
	memset(vist,false,sizeof(vist)); 
	BFS();                           //Ԥ����: ��ÿһ�����к͹�굽����������������Ҫ"��λ�ͻ�λ�Ĳ�����"��(�˹����������޹�)

	char Init_ANum[6];               //��ʼ�ַ���
	int Init_DNum[6];                //��ʼ���ִ�
	char Aim_ANum[6];                //Ŀ���ַ���
	int Aim_DNum[6];                 //Ŀ�����ִ�
	
	while(cin>>Init_ANum>>Aim_ANum)
	{
		for(int k=0;k<6;k++)         //�ַ���ת��Ϊ���ִ�
		{
			Init_DNum[k]=Init_ANum[k]-'0';
			Aim_DNum[k]=Aim_ANum[k]-'0';
		}

		int MinOper = 1000000;        //��str�õ�aim������Ҫ�Ĳ�����
		for(int i=0;i<idx;i++)
		{
			int cnt=comb[i][7];       //comb[i][7]=step,Ϊ��λ�ͻ�λ���ܲ�����
			bool flag=true;
			for(int j=0;j<6;j++)
			{                         //comb[i][6]=state
				if(!VistState[ comb[i][6] ][j] && (Init_DNum[ comb[i][j] ]!=Aim_DNum[j]))  //�������״̬��ĳλû����������������λ���ֲ�����Ŀ��״̬����λ����
				{                                                                          // comb[i] ʹ Init_DNumһ˲�� ������ comb[i][7] �εı仯�� 
					flag=false;       //  ���state���С�
					break;
				}
				else
					cnt+=abs(Init_DNum[ comb[i][j] ] - Aim_DNum[j]);                       //��λ�ñ���������ֵ�ı�Ĵ���(ÿһ�ı�1)���ǲ�����
			}

			if(flag)
				MinOper=MinOper<cnt?MinOper:cnt;
		}

		cout << MinOper << endl;
	}

	return 0;
}
//*/









/*�еĽ��ⱨ��˵��겻������ ���Ĵ�� 000159 000519 ������� 8 Ŷ
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
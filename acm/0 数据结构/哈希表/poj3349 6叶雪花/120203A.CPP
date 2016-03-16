/*      8008K	3344MS	C++	3236B
#include<iostream>
#include<stdio.h>
#include<math.h>
using namespace std;

struct node
{
 int x1,x2,x3,x4,x5,x0,flag;
 node* link;
};

node a[7][7][7][7][7][7];
int b[110010][6];

bool dog1(int t0,int t1,int t2,int t3,int t4,int t5)
{
	 int x00,x11,x22,x33,x44,x55;
	 int d;
	 node* p;
	 x00=t0%7;
	 x11=t1%7;
	 x22=t2%7;
	 x33=t3%7;
	 x44=t4%7;
	 x55=t5%7;
	 p=&a[x00][x11][x22][x33][x44][x55];
	 d=0;
	 while(1)
	 {
		  if ((p->x0==t0)&&(p->x1==t1)&&(p->x2==t2)&&(p->x3==t3)&&(p->x4==t4)&&(p->x5==t5)) d++;
		  if (p->link==NULL) break;
		  else
		   p=p->link;
	 }
	 if (d>=2)
		 return true;
	 else return false;
}
bool dog(int t0,int t1,int t2,int t3,int t4,int t5)
{
	 int x00,x11,x22,x33,x44,x55;
	 node* p;
	 x00=t0%7;
	 x11=t1%7;
	 x22=t2%7;
	 x33=t3%7;
	 x44=t4%7;
	 x55=t5%7;
	 p=&a[x00][x11][x22][x33][x44][x55];
	 while(1)
	 {
		  if ((p->x0==t0)&&(p->x1==t1)&&(p->x2==t2)&&(p->x3==t3)&&(p->x4==t4)&&(p->x5==t5)) return true;
		  if (p->link==NULL) break;
		  else
		   p=p->link;
	 }
		return false;
}

void pig()
{
	 int i0,i1,i2,i3,i4,i5;
	 node *p,*q;
	 for(i0=0;i0<=6;i0++)
		 for(i1=0;i1<=6;i1++)
			for(i2=0;i2<=6;i2++)
				for(i3=0;i3<=6;i3++)
					 for(i4=0;i4<=6;i4++)
						for(i5=0;i5<=6;i5++)
							if (a[i0][i1][i2][i3][i4][i5].link!=NULL)
							{
								p=&a[i0][i1][i2][i3][i4][i5];
								while(1)
								{
									 q=p->link;
									 p->link=q->link;
									 delete q;
									 if (p->link==NULL) break;
								}
						   }
}

int main()
{
	 int n,i,j,i0,i1,i2,i3,i4,i5,t0,t1,t2,t3,t4,t5;
	 //bool d;
	 node* q;
	 scanf("%d",&n);
	 for(i0=0;i0<=6;i0++)
		 for(i1=0;i1<=6;i1++)
			for(i2=0;i2<=6;i2++)
				for(i3=0;i3<=6;i3++)
					for(i4=0;i4<=6;i4++)
						for(i5=0;i5<=6;i5++)
						{
							a[i0][i1][i2][i3][i4][i5].flag=0;
							a[i0][i1][i2][i3][i4][i5].link=NULL;
						}
	 for(i=1;i<=n;i++)
	 {
	  scanf("%d%d%d%d%d%d",&b[i][0],&b[i][1],&b[i][2],&b[i][3],&b[i][4],&b[i][5]);
	  t0=b[i][0]%7;
	  t1=b[i][1]%7;
	  t2=b[i][2]%7;
	  t3=b[i][3]%7;
	  t4=b[i][4]%7;
	  t5=b[i][5]%7;
	  if (a[t0][t1][t2][t3][t4][t5].flag==1)
	  {
	   q=new node();
	   q->x0=b[i][0];
	   q->x1=b[i][1];
	   q->x2=b[i][2];
	   q->x3=b[i][3];
	   q->x4=b[i][4];
	   q->x5=b[i][5];
	   q->link=a[t0][t1][t2][t3][t4][t5].link;
	   a[t0][t1][t2][t3][t4][t5].link=q;
	  }
	  else
	  {
	   a[t0][t1][t2][t3][t4][t5].flag=1;
	   a[t0][t1][t2][t3][t4][t5].x0=b[i][0];
	   a[t0][t1][t2][t3][t4][t5].x1=b[i][1];
			 a[t0][t1][t2][t3][t4][t5].x2=b[i][2];
			 a[t0][t1][t2][t3][t4][t5].x3=b[i][3];
			 a[t0][t1][t2][t3][t4][t5].x4=b[i][4];
			 a[t0][t1][t2][t3][t4][t5].x5=b[i][5];
	  }
	 }
	 for(i=1;i<=n;i++)
	 {
		  if (dog1(b[i][0],b[i][1],b[i][2],b[i][3],b[i][4],b[i][5]))   {pig();printf("Twin snowflakes found.\n");return 0;}
		  for(j=1;j<=5;j++)
			if (dog(b[i][j],b[i][(j+1)%6],b[i][(j+2)%6],b[i][(j+3)%6],b[i][(j+4)%6],b[i][(j+5)%6])) 
			{
				pig();
				printf("Twin snowflakes found.\n");
				return 0;
			}
		  for(j=0;j<=5;j++)
		   if (dog(b[i][j],b[i][((j-1)%6+6)%6],b[i][((j-2)%6+6)%6],b[i][((j-3)%6+6)%6],b[i][((j-4)%6+6)%6],b[i][((j-5)%6+6)%6]))
		   {
			   pig();
			   printf("Twin snowflakes found.\n");
			   return 0;
		   }
	 }
	 pig();
	 printf("No two snowflakes are alike.\n");
	 return 0;
}
//*/




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/*      	9352K	3110MS	G++	2282B
//Hash Table  开散列法  总结poj discuss的tips
// 1. 直接相加, 总和%大质数为key.
// 2. 平方和相加, 总和%大质数为key.
// 3. 从小到大的顺序, 对v[i]<<(i*3)依次异或, 然后模一个大质数作为key.
// 4. 六个数中非零数的积再乘上一个大质数,然后模一个100w上下的数。
//    自己拿随机数据测下来110w左右的效果最好，随机情况下数据量是10w的时候hash值相同的情况只有6k多个，几乎可以忽略。
// 5. 依次对每个数异或所得的数作为key. (by archerstarlee)
// 6. (a[0]+a[2]+a[4])&(a[1]+a[3]+a[5]), 再模一个大质数. &还可改成'|' 或'^'.非常巧妙!(只对本题适用的hash方法)
//     最后就是用getchar和gets来进行输入转换更为快速. G++比GCC快一些.

#include<iostream>
#include<cstdio>
#include<string>

#define M 99991
#define max 100000

using namespace std;

struct flake
{
    int arm[6];
    bool value;
    flake *next;
}; 
struct flake sonw[max];

void initialize(flake a)
{
    a.value=0;
    a.next=NULL;
}

int hash(int arm[])   // 平方和相加, 总和%大质数为key.
{
    __int64 h;
    for(int i=0;i<6;i++)
        h+= (arm[i]*arm[i]);
    return h%M;
}

void insert(struct flake *p,int arm[6])
{
    if(p->value==0)
	{
        for(int i=0;i<6;i++)
            (p->arm[i])=arm[i];
        p->value = 1;
        p->next = new flake;
        p->next->value = 0;
    }
    else
	{
        p = p->next;
        insert(p,arm);
    }
}

bool judge(int a[6],int b[6])   //一共六个元素，就这样好了。。。囧。。。
{
    if (a[0]==b[0]&&a[1]==b[1]&&a[2]==b[2]&&a[3]==b[3]&&a[4]==b[4]&&a[5]==b[5])      return 1;
    else if(a[0]==b[1]&&a[1]==b[2]&&a[2]==b[3]&&a[3]==b[4]&&a[4]==b[5]&&a[5]==b[0])  return 1;
    else if(a[0]==b[2]&&a[1]==b[3]&&a[2]==b[4]&&a[3]==b[5]&&a[4]==b[0]&&a[5]==b[1])  return 1;
    else if(a[0]==b[3]&&a[1]==b[4]&&a[2]==b[5]&&a[3]==b[0]&&a[4]==b[1]&&a[5]==b[2])  return 1;
    else if(a[0]==b[4]&&a[1]==b[5]&&a[2]==b[0]&&a[3]==b[1]&&a[4]==b[2]&&a[5]==b[3])  return 1;
    else if(a[0]==b[5]&&a[1]==b[0]&&a[2]==b[1]&&a[3]==b[2]&&a[4]==b[3]&&a[5]==b[4])  return 1;
    else return 0;
}

bool search(struct flake *q,int arm[6])
{
    int c[6];           //arm的倒置
    for(int i=0;i<6;i++)
        c[i]=arm[5-i];

    while(q->value)
	{
        int stand[6];

        for(int i=0;i<6;i++)
            stand[i]=(q->arm[i]);

        if(judge(stand,arm)==1||judge(stand,c)==1)
			return 1;
        else
			q=q->next;
    }

    if(q->value==0)
		return 0;
}

int main()
{
    for(int i=0;i<max;i++)
        initialize(sonw[i]);
    int n,arm[6];
    cin >> n;
    while(n--)
	{
        for(int i=0;i<6;i++)
            scanf("%ld",&arm[i]);

        int k=hash(arm);
        struct flake *p;
        p=&sonw[k];

        //多路判定。。。。。。不能 if...if....if...的啊啊啊啊啊啊啊啊啊
        if(search(p,arm)==0)
            insert(p,arm);
        else if(search(p,arm)==1)
		{
            printf("Twin snowflakes found.\n");
            return 0;
        }
    }
    printf("No two snowflakes are alike.\n");
    return 0;
}
//*/




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/*   Time Limit Exceeded
#include <cstdio>
#include <cstring>
#include <time.h>
#include <iostream>

using namespace std;

#define hashPrime 1444409   //哈希取余素数
#define hashTableNums 1444505   //哈希表长度
#define initNum -1          //哈希表初始化值

int hashTableKeys[hashTableNums];//哈希表键值
int hashTableValues[hashTableNums];//键值相对应的数据

//哈希表初始化
void hashTableInit()
{
    if(initNum==0) 
	{
        memset(hashTableKeys,0,sizeof(hashTableKeys));
        memset(hashTableValues,0,sizeof(hashTableValues));
	}
    else for (int i=0;i<hashTableNums;i++)
	{
        hashTableKeys[i]=initNum;
        hashTableValues[i]=initNum;
	}
}
//哈希规则
int hashTableRules(int hashKey)
{
    return hashKey%hashPrime;
}

//向哈希表中添加数据
int hashTableAdd(int hashKey,int hashValue)
{
    int hashTablePos=hashTableRules(hashKey);
    bool first=1;
    for (int i=hashTablePos;;i++)
	{
        i %=hashTableNums;
        if(i == hashTablePos && first==0) 
		{
			return -1;
		}
        first=0;
        if(hashTableKeys[i] == initNum)
		{
            hashTableKeys[i]=hashKey;
			hashTableValues[i]=hashValue; 
			return i;
		}
    }
}

//查找哈希表
int hashTableFind(int hashKey)
{
    int hashTablePos=hashTableRules(hashKey);
    bool first=1;
    for (int i=hashTablePos;;i++)
	{
        i %=hashTableNums;
        if(i == hashTablePos && first==0) { return -2;}
        first=0;
        if(hashTableKeys[i] == hashKey) return i;
        if(hashTableKeys[i] == initNum) return -1;
    }
}

int snows[100019][7];
bool isSame(int a, int b) {
    for(int i=0;i<6;i++)
    {
        if(//顺时针方向
          (snows[a][1] == snows[b][i+1] &&
           snows[a][2] == snows[b][(i+1)%6+1] &&
           snows[a][3] == snows[b][(i+2)%6+1] &&
           snows[a][4] == snows[b][(i+3)%6+1] &&
           snows[a][5] == snows[b][(i+4)%6+1] &&
           snows[a][6] == snows[b][(i+5)%6+1])
           ||
            //逆时针方向
           (snows[a][1] == snows[b][i+1] &&
            snows[a][2] == snows[b][(i+5)%6+1] &&
            snows[a][3] == snows[b][(i+4)%6+1] &&
            snows[a][4] == snows[b][(i+3)%6+1] &&
            snows[a][5] == snows[b][(i+2)%6+1] &&
            snows[a][6] == snows[b][(i+1)%6+1])
           )
        return true;
    }   
    return false;
}

int main()
{
    //freopen("1.txt","r",stdin);
    hashTableInit();
    memset(snows,0,sizeof(snows));
    int n=0;
    int flag=0;
    scanf("%d",&n);
    for (int i=0;i<n;i++)
    {
        for (int j=1;j<=6;j++)
        {
            scanf("%d",&snows[i][j]);
        }
        snows[i][0]=(snows[i][1]+snows[i][3]+snows[i][5]) ^ (snows[i][2]+snows[i][4]+snows[i][6]) ;
        int nowpos=hashTableAdd(snows[i][0],i);
        int serchpos=hashTableFind(snows[i][0]);
        if(nowpos!=serchpos){
            int first=1;
            for (int k=serchpos;;k++)
            {
                k %=hashTableNums;
                if(k == serchpos && first==0) break;
                if( hashTableKeys[k]==initNum ) break;
                if(k==nowpos) break;
                if(snows[hashTableValues[nowpos]][0] ==snows[hashTableValues[k]][0]){
                    if(isSame(hashTableValues[nowpos],hashTableValues[k])){
                        flag=1;
                        break;}
                }
            }
        }
        if(flag){
            printf("Twin snowflakes found.\n");
            break;
        }
    }
    if(!flag){
        printf("No two snowflakes are alike.\n");
    }
    //printf("%f",(double)clock()/CLOCKS_PER_SEC);

	return 0;
}  
//*/



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//*         5180K	2985MS	G++	1398B
//          4076K	3204MS	C++	1468B
#include<iostream>
#include<vector>
#include<cstdio>
#include <time.h>
using namespace std;

const int N = 9997;//足够大的素数
 
typedef struct 
{
    int a[6];
    long sum;
} Node;
vector<Node> vec[N];

int nn;

int Compare(Node n1, Node n2) 
{
    int i, j;
    for (i = 0; i < 6; i++) 
	{
        if (n1.a[0] == n2.a[i]) 
		{
			//顺序
            for (j = 1; j < 6; j++)
			{
                if (n1.a[j] != n2.a[(i + j) % 6])
                    break;
            }
            if (j == 6) return 1;
			//逆序
            for (j = 1; j < 6; j++)
			{
                if (n1.a[6 - j] != n2.a[(i + j) % 6])
                    break;
            }
            if (j == 6) return 1;
        }
    }
    return 0;
}
 
int check() 
{
    int i, j, k;
    for (i = 0; i < N; i++)  // 哈希表遍历
	{
        for (j = 0; j < vec[i].size(); j++)  
		{                                          
            for (k = j + 1; k < vec[i].size(); k++)
			{
                if ( Compare(vec[i][j], vec[i][k])) 
                    return 1;
            }
        }
    }
    return 0;
}
 
int main() 
{
    int n, i;
    Node node;
    scanf("%d", &n);
	nn = n;
    while (n--) 
	{
        node.sum = 0;
        for (i = 0; i < 6; i++) 
		{
            scanf("%d", node.a + i);
            node.sum += node.a[i];
        }
        vec[node.sum % N].push_back(node);
    }
    puts(check() ? "Twin snowflakes found." : "No two snowflakes are alike.");
	printf("%f",(double)clock()/CLOCKS_PER_SEC);
    return 0;
}
//*/
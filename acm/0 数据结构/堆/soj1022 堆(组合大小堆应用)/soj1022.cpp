/*

2
Add Magicpig 100
Add Radium 600
Add Kingfkong 300
Add Dynamic 700 
Query
Add Axing 400
Query
Find Kingfkong
Add Inkfish 1000
Add Carp 800
End

Add Radium 100
Add Magicpig 200
End
Sample Output

No one!
Axing
Radium is so poor.

Happy BG meeting!!

*/



//*       Run Time: 0.25secs    Run Memory: 3436KB
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

struct node
{
	char name[10];
	int mark;
};

node heap[2][100010];
int hlen[2];  // 0 小堆  1 大堆

bool kctless(const node& s, const node& t)
{
	return s.mark>t.mark;
}

bool kctgreater(const node& s, const node& t)
{
	return s.mark<t.mark;
}

void insert(node t, int k)   // 先将元素查到末尾，再调整顺序
{
	heap[k][hlen[k]++] = t;
	if(k==0)  // 插入最小堆
		push_heap(heap[k], heap[k]+hlen[k], kctless);
	else      // 插入最大堆
		push_heap(heap[k], heap[k]+hlen[k], kctgreater);
}

void remove(int k)          // 先将元素下移到数组最后，再缩小数组大小
{
	if(k==0)  // 元素下移
		pop_heap(heap[k], heap[k]+hlen[k]--, kctless);
	else
		pop_heap(heap[k], heap[k]+hlen[k]--, kctgreater);
}

bool find(char *ch, int k)   // t从1开始 用不了二分法，因为不知大小关系！
{
		for(int i=0; i<hlen[k]; i++)
			if(strcmp(heap[k][i].name, ch)==0)
				return true;
		return false;
}

int main()
{
	int tc;
	char command[10];
	scanf("%d", &tc);

	while(tc--)
	{
		hlen[0] = 0;
		hlen[1] = 0;
		
		while(1)
		{
			scanf("%s", command);
			if(command[0]=='A')
			{
				node temp;
				scanf("%s%d", temp.name, &(temp.mark));
				if(hlen[0]>hlen[1])
				{
					// 加入最大堆
					insert(temp, 1);
				}
				else
				{
					// 加入最小堆
					insert(temp, 0);
				}
				if(hlen[0]>0 && hlen[1]>0 && heap[0][0].mark<heap[1][0].mark)
				{
					node tmp1, tmp2;
					tmp1 = heap[0][0];
					tmp2 = heap[1][0];
					remove(0);
					remove(1);
					insert(tmp2, 0);
					insert(tmp1, 1);
				}
			}
			else if(command[0]=='Q')
			{
				if(hlen[0]==hlen[1])
					printf("No one!\n");
				else
					printf("%s\n", heap[0][0].name);
			}
			else if(command[0]=='F')
			{
				node temp;
				scanf("%s", temp.name);
				if(find(temp.name, 0))
					cout << "zuixiaodui" << endl;
				else if(find(temp.name, 1))
					cout << "zuidadui" << endl;
				else
					cout << "no" << endl;
			}
			else
			{
				if(hlen[0]==hlen[1])
					printf("Happy BG meeting!!\n");
				else
					printf("%s is so poor.\n", heap[0][0].name);
				break;
			}
		}
		if(tc!=0)
		printf("\n");
	}

	return 0;
}


//*/




/*    Run Time: 0.25secs    Run Memory: 3436KB
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn=100010;

struct node
{
    char name[11];
    int mark;
};

bool myless(node s,node t)
{
    return s.mark<t.mark;
}

bool mygreater(node s,node t)
{
    return s.mark>t.mark;
}

node st[2][maxn];  
int cc[2];

node tmp;

void insert(node &t,int k)
{
    st[k][cc[k]++]=t;
    if (k==0)
        push_heap(st[k],st[k]+cc[k],mygreater);
    else
        push_heap(st[k],st[k]+cc[k],myless);
}

void remove(int k)
{
    tmp=st[k][0];
    if (k==0)
        pop_heap(st[k],st[k]+cc[k]--,mygreater);
    else
        pop_heap(st[k],st[k]+cc[k]--,myless);
}

char comm[10];
char name[12];
int mark;

int main()
{
    int num;
    scanf("%d",&num);
    for (int kk=0;kk<num;kk++)
    {
        cc[0]=0;
        cc[1]=0;

        while (true)
        {
            scanf("%s",comm);
            if (strcmp(comm,"Add")==0)
            {
                scanf("%s%d",name,&mark);

                node x;
                x.mark=mark;
                strcpy(x.name,name);

                if (cc[0]==cc[1]&&cc[0]==0)
                {
                    insert(x,0);
                    continue;
                }
               
                if (cc[0]==cc[1]&&cc[0]!=0)
                {
                    int tmpmark=st[0][0].mark;
                    if (mark>=tmpmark)
                        insert(x,0);
                    else
                        insert(x,1);
                    continue;
                }

                if (cc[0]<cc[1])   // should put into the minmal heap
                {
                    if (x.mark<st[1][0].mark)
                    {
                        tmp=st[1][0];
                        remove(1);
                        insert(tmp,0);
                        insert(x,1);                       
                    }
                    else
                    {
                        insert(x,0);
                    }
                    continue;
                }

                if (cc[0]>cc[1])
                {
                    if (x.mark>st[0][0].mark)
                    {
                        tmp=st[0][0];
                        remove(0);
                        insert(tmp,1);
                        insert(x,0);
                    }
                    else
                    {
                        insert(x,1);
                    }
                    continue;
                }
            }
            else if (strcmp(comm,"Query")==0)
            {
                if (cc[0]==cc[1])
                    printf("%s\n","No one!");
                else if (cc[0]>cc[1])
                {
                    printf("%s\n",st[0][0].name);
                }
                else
                    printf("%s\n",st[1][0].name);

            }
            else    // for end
            {
                if (cc[0]==cc[1])
                    printf("%s\n","Happy BG meeting!!");
                else if (cc[0]>cc[1])
                {
                    printf("%s is so poor.\n",st[0][0].name);
                }
                else
                    printf("%s is so poor.\n",st[1][0].name);
               
            }

            if (comm[0]=='E')
                break;
        }

        if (kk!=num-1)
            printf("\n");
    }
    return 0;
}

//*/






/*                                                                      Run Time: 0.27secs         Run Memory: 5000KB
#include "iostream"
#include "cstring"
#include "algorithm"
#include "cstdio"
using namespace std;

void insert_min_heap(int pos);//往最小堆中插入元素
void insert_max_heap(int pos);//往最大堆中插入元素
void is_min_heap(int pos, int parent);//对最小堆的调整
void is_max_heap(int pos, int parent);//对最大堆的调整

struct Info
{
	//string name;
	char name[20];
	int SolveNum;
}max_heap[100010], min_heap[100010];



int main()
{
	char command[10];
	Info temp;
	int TestCase;
	
	scanf("%d", &TestCase);
	int tag = 0;//用于输出格式的判断位

	while (TestCase--)
	{
		if (tag != 0)
			printf("\n");

		tag++;
		bool is_even = true;//用于判断是奇数还是偶数
		int min_length = 0, max_length = 0;

		while (scanf("%s", command) && strcmp(command, "End") != 0)
		{
			if (strcmp(command, "Add") == 0)
			{
				scanf("%s", temp.name);    scanf("%d", &temp.SolveNum);

				if (is_even)//如果是偶数就插入最小堆中
				{
					min_length++;
					min_heap[min_length] = temp;
					insert_min_heap(min_length);     //自下而上
					is_even = false;
				}
				else//如果是奇数就插入最大堆中
				{
					max_length++;
					max_heap[max_length] = temp;
					insert_max_heap(max_length);
					is_even = true;
				}

				if (max_length > 0 && min_length > 0 && max_heap[1].SolveNum > min_heap[1].SolveNum)
				{
					swap(max_heap[1], min_heap[1]);
					is_min_heap(min_length, 1);        //自上而下
					is_max_heap(max_length, 1);
				}
			}
			if (strcmp(command, "Query") == 0)
			{
				if (is_even)
					printf("No one!\n");
				else
					printf("%s\n", min_heap[1].name);
			}
		}
		if (is_even)
			printf("Happy BG meeting!!\n");
	    else
			printf("%s is so poor.\n", min_heap[1].name);
	}	
}

void insert_min_heap(int pos)
{
	if (pos == 1)
		return;
	int parent = pos / 2;
	if (min_heap[parent].SolveNum > min_heap[pos].SolveNum)
	{
		swap(min_heap[parent], min_heap[pos]);
		insert_min_heap(parent);
	}
}

void insert_max_heap(int pos)
{
	if (pos == 1)
		return;
	int parent = pos / 2;
	if (max_heap[parent].SolveNum < max_heap[pos].SolveNum)
	{
		swap(max_heap[parent], max_heap[pos]);
		insert_max_heap(parent);
	}
}

void is_min_heap(int pos, int parent)
{
	int left, right;
	int min;
	left = parent * 2;
	right = parent * 2 + 1;

	if (left <= pos && min_heap[parent].SolveNum > min_heap[left].SolveNum)
		min = left;
	else
		min = parent;

	if (right <= pos && min_heap[min].SolveNum > min_heap[right].SolveNum)
		min = right;

	if (min != parent)
	{
		swap(min_heap[min], min_heap[parent]);
		is_min_heap(pos, min);
	}
}

void is_max_heap(int pos, int parent)
{
	int left, right;
	int max;
	left = parent * 2;
	right = parent * 2 + 1;

	if (left <= pos && max_heap[left].SolveNum > max_heap[parent].SolveNum)
		max = left;
	else
		max = parent;

	if (right <= pos && max_heap[right].SolveNum > max_heap[max].SolveNum)
		max = right;

	if (max != parent)
	{
		swap(max_heap[max], max_heap[parent]);
		is_max_heap(pos, max);
	}
}

//*/






/*                                                             Run Time: 0.24secs          Run Memory: 3436KB                       系统堆               

#include<iostream>
#include<algorithm>

using namespace std;

const int maxn=100010;

struct node
{
    char name[11];
    int mark;
};

node st[2][maxn];   
int cc[2];

node tmp;

char comm[10];
char name[12];
int mark;

bool myless(node s,node t)
{
    return s.mark<t.mark;
}

bool mygreater(node s,node t)
{
    return s.mark>t.mark;
}



void insert(node &t,int k)
{
    st[k][cc[k]++]=t;

    if (k==0)
        push_heap(st[k],st[k]+cc[k],mygreater);
    else
        push_heap(st[k],st[k]+cc[k],myless);
}

void remove(int k)
{
    //tmp=st[k][0];
    if (k==0)
        pop_heap(st[k],st[k]+cc[k]--,mygreater);
    else
        pop_heap(st[k],st[k]+cc[k]--,myless);
}



int main()
{
    int num;
    scanf("%d",&num);
    for (int kk=0; kk<num; kk++)
    {
        cc[0]=0;
        cc[1]=0;

        while (true)
        {
            scanf("%s",comm);
            if (strcmp(comm,"Add")==0)
            {
                scanf("%s%d",name,&mark);

                node x;
                x.mark=mark;
                strcpy(x.name,name);


                if (cc[0]==cc[1]&&cc[0]==0)
                {
                    insert(x,0);
                    continue;
                }
                
                if (cc[0]==cc[1]&&cc[0]!=0)
                {
                    int tmpmark=st[0][0].mark;
                    if (mark>=tmpmark)
                        insert(x,0);
                    else
                        insert(x,1);
                    continue;
                }

                if (cc[0]<cc[1])   // should put into the minmal heap
                {
                    if (x.mark<st[1][0].mark)
                    {
                        tmp=st[1][0];
                        remove(1);
                        insert(tmp,0);
                        insert(x,1); 
                    }
                    else
                    {
                        insert(x,0);
                    }
                    continue;
                }

                if (cc[0]>cc[1])
                {
                    if (x.mark>st[0][0].mark)
                    {
                        tmp=st[0][0];
                        remove(0);
                        insert(tmp,1);
                        insert(x,0);
                    }
                    else
                    {
                        insert(x,1);
                    }
                    continue;
                }
            }
            else if (strcmp(comm,"Query")==0)
            {
                if (cc[0]==cc[1])
                    printf("%s\n","No one!");
                else if (cc[0]>cc[1])
                {
                    printf("%s\n",st[0][0].name);
                }
                else
                    printf("%s\n",st[1][0].name);

            }
            else    // for end
            {
                if (cc[0]==cc[1])
                    printf("%s\n","Happy BG meeting!!");
                else if (cc[0]>cc[1])
                {
                    printf("%s is so poor.\n",st[0][0].name);
                }
                else
                    printf("%s is so poor.\n",st[1][0].name);
            }
            if (comm[0]=='E')
                break;
        }

        if (kk!=num-1)
            printf("\n");
    }

    return 0;
}
//*/






























/*
#include <iostream> 
#include <queue> 

using namespace std; 

struct sta 
{ 
    int state; 
    int step; 
}p,temp,s; 

void pri(int num) 
{ 
    int i,j=0,l=0,n[16]={0}; 
    while(num) 
        n[l++]=num%2,num/=2; 
    for(i=15;i>=0;i--) 
    {    
        cout<<n[i]; 
        j++; 
        if(j==4) 
        { 
            cout<<endl; 
            j=0; 
        } 
    } 
    cout<<endl; 
} 

void move(sta *a,int id) 
{ 
    a->state<<=id; 
    a->state^=32768; 
    a->state>>=id; 
    if(id<=11)     // 有下的
    {
            a->state<<=(id+4); 
            a->state^=32768; 
            a->state>>=(id+4); 
    }
    if(id>=4)       //  有上的
    { 
        a->state<<=(id-4); 
        a->state^=32768; 
        a->state>>=(id-4); 
    } 
    if(id==0||id==4||id==8||id==12)   //第一列 的右边
        { 
            a->state<<=(1+id); 
            a->state^=32768; 
            a->state>>=(id+1); 
        } 
    else 
    if(id==3||id==7||id==11||id==15)  //第四列  的左边
        { 
            a->state<<=(id-1); 
            a->state^=32768; 
            a->state>>=(id-1); 
        } 
    else                              // 中间两列
        { 
            a->state<<=(id+1);   // 右边
            a->state^=32768; 
            a->state>>=2;        // 左边
            a->state^=32768; 
            a->state>>=(id-1); 
        } 
} 



queue<sta> q; 
bool hash[65537];


int main() 
{ 
    int w,i,j; 
    char map[4][5]; 
    bool flag; 
    while(cin>>map[0]) 
    { 
		memset(hash,false,sizeof(hash)); 
		flag=false; 
		getchar(); 
		for(i=1;i<4;i++) 
			cin>>map[i],getchar(); 
		s.step=0;s.state=0; 
		for(i=0;i<4;i++) 
			for(j=0;j<4;j++) 
				if(map[i][j]=='b') 
					s.state++,s.state<<=1; 
				else 
					s.state<<=1; 
		s.state>>=1; 

		if(s.state==0||s.state==65535) 
		{ 
			cout<<0<<endl; 
			continue; 
		} 

		q.push(s); 
		hash[s.state]=true; 
		w=0; 
		while(!q.empty()) 
		{ 
				while(q.front().step==w) 
				{ 
					p=q.front(); 
					p.step++; 
					for(i=0;i<=15;i++) 
					{ 
						temp=p; 
						move(&temp,i); 
					    if(temp.state==0||temp.state==65535) 
						{ 
                         
							flag=true; 
							break; 
						} 
					    if(!hash[temp.state]) 
						{ 
							hash[temp.state]=true; 
							q.push(temp);
						} 
					} 
					q.pop();
					if(flag) break;  
				} 
				w++; 
				if(flag) break; 
		} 
		if(flag) 
			cout<<temp.step<<endl; 
		else 
			cout<<"Impossible"<<endl; 
    } 
    return 0; 
}
//*/




//*  204K	79MS	C++	879B  
#include "iostream"
using namespace std;
unsigned short int flips[16]={0xc800,0xe400,0x7200,0x3100,0x8c80,0x4e40,0x2720,0x1310,
              0x08c8,0x04e4,0x0272,0x0131,0x008c,0x004e,0x0027,0x0013};
int min1=16;
unsigned short int poww2(int n)
{
    int i=1;
    i=i<<n;
    return i; 
}

void bsp(unsigned short int number,int step,int flip)   //  binary space partitioning 子集树
{
    if(number==0||number==0xffff)
    {
        min1=(min1<flip?min1:flip);
        return ;
    }
    if(step>=16)return;
    bsp(number,step+1,flip);
    bsp(number^flips[step],step+1,flip+1);
}

int main()
{
    int i=0;
    unsigned short int num=0;
    char x;
    while(i<16)
    {
        cin>>x;
        if(x=='b')
        num+=poww2(15-i);
        i++;
    }
    min1=16;
    bsp(num,0,0);
    if(min1==16)
        printf("Impossible\n");
    else printf("%d\n",min1);
    return 0;
}
//*/

/*
#include "iostream"
using namespace std;
unsigned short int flips[16]={0xc800,0xe400,0x7200,0x3100,0x8c80,0x4e40,0x2720,0x1310,
              0x08c8,0x04e4,0x0272,0x0131,0x008c,0x004e,0x0027,0x0013};
int min1=16;
bool vis[16];

unsigned short int poww2(int n)
{
    int i=1;
    i=i<<n;
    return i; 
}

void bsp(unsigned short int number,int step)
{
    if(step>=16)
		return ; 
	if(number==0||number==0xffff)
    {
        min1=(min1<step?min1:step);
        return ;
    }
	for(int i=0; i<16; i++)
	{
		unsigned short int tmp = number^flips[i];
		if(!vis[i])
		{
			vis[i] = true;
			bsp(tmp, step+1);
			vis[i] = false;
		}
	}
}

int main()
{
    int i=0;
    unsigned short int num=0;
    char x;
    while(i<16)
    {
        cin>>x;
        if(x=='b')
        num+=poww2(15-i);
        i++;
    }

	if(num==0||num==0xffff)
    {
        printf("0\n");
        return 0;
    }

	memset(vis, false, sizeof(vis));
    min1=16;
    bsp(num,0);

    if(min1==16)
        printf("Impossible\n");
    else printf("%d\n",min1);

    return 0;
}
//*/
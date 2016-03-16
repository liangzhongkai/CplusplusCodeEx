/*  怎样表示这个状态都不知道，怎么写得出hash函数，怎么剪枝
#include<iostream>

using namespace std;

int mp[5][9];
int ans;

int main()
{
	int tc;
	int i, j;
	int mo[4] = {11, 21, 31, 41};
	pair<int,int> ko[5];

	cin >> tc;

	while(tc--)
	{
		for(i=1; i<5; i++)
			for(j=2; j<9; j++)
			{
				cin >> mp[i][j];
				if(mp[i][j]==11)
				{
					mp[1][1] = mp[i][j];
					mp[i][j] = 0;
					ko[1].first = i;
					ko[1].second = j;
				}
				else if(mp[i][j]==21)
				{
					mp[2][1] = mp[i][j];
					mp[i][j] = 0;
					ko[2].first = i;
					ko[2].second = j;
				}
				else if(mp[i][j]==31)
				{
					mp[3][1] = mp[i][j];
					mp[i][j] = 0;
					ko[3].first = i;
					ko[3].second = j;
				}
				else if(mp[i][j]==41)
				{
					mp[4][1] = mp[i][j];
					mp[i][j] = 0;
					ko[4].first = i;
					ko[4].second = j;
				}
			}

		int key = 0;
		for(i=1; i<5; i++)
			for(j=1; j<8; j++)
			{
				if(mp[i][j]!=mo[i-1]+j-1)
				{
					key = 1;
					break;
				}
			}

		if(key==0)
		{
			cout << 0 << endl;
			continue;
		}

		ans = 99999999;
		queue<int> q;
		if()
			cout << ans << endl;
		else
			cout << -1 << endl;
	}

	return 0;
}
//*/




/*  bfs        9732K	375MS	C++	2379B


#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

const int M=1000007;    // 大质数

struct data
{
    char s[32],e[4],p[48];   //  s装矩阵的，e记录0的坐标，p记录某个数对应的下标
    int ans;                 //  ans记录路径长度
}w[500000];

int id[M],ans;

inline int BKDRHash(char *str)
{
	int hash = 0;
	int q=0;

    while (++q<33)
    {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;    
		//hash = hash * 31 + (*str++);                          
    }

    return (hash & 0x7FFFFFFF)%M;

	//int hash=0,q=0;
//	while(++q<33)
	//	hash=hash*7+(*str++);  // 如果str只是一个数，那么这个数必然变小了     //              9732K	422MS	C++	3365B
	
	//return((hash&0x7FFFFFFF)%M);  //
	
}

inline void insert(char *c,int i)
{
    int x=BKDRHash(c);
    while(id[x]>=0)  // 记录的时候，如果这个位置已经被占了，那么向后移7位，看看有没有位置，直到找到落脚点
    {
        x+=7;
        if(x>=M)x%=M;
    }
    id[x]=i;
}

inline void get(char &a)
{
    char ch=getchar();
    while (ch<'0'||ch>'9')
		ch=getchar();
    for(a=0; ch>='0'&&ch<='9'; ch=getchar())
		a=a*10+ch-48;
    if((a==11)||(a==21)||(a==31)||(a==41))
		a=0;
}

inline bool cmp(char *p,char *q)
{
    for(int i=0;i<32;++i,++p,++q)
        if(*p!=*q)return 1;
    return 0;
}

inline int find(char *c)
{
    int x=BKDRHash(c);
    while(id[x]>=0 && cmp(c,w[id[x]].s))   // 这个位置有人占了，而且这个人就是要找的那个，就返回它的id[]值（这个值是人为给的）
    {
        x+=7;
        if(x>=M)x%=M;
    }
    return id[x];
}

inline void cpy(char *p,char *q,int n)
{
    for(int i=0; i<n; ++i,++p,++q)
		*p=*q;
}

inline int bfs()
{
    int l=0, r=1, rr=2, i,k,s,p,e;                                           // r指向变化好的状态，rr指向变化前的状态
    do
    {
        cpy(w[rr].s, w[++l].s, 32);                                          // 4 * 8 = 32   将w[1] 传给 w[2]
        for(i=0;i<4;++i)
			if( w[l].s[(e=w[l].e[i])-1]%10<7 && w[l].s[e-1]>0 )              // 每个空的前一个数  和  这个数大于0
			{
				w[rr].s[e] = s = w[l].s[e-1]+1,    w[rr].s[p=w[l].p[s]]=0;   // 前一个状态的空位被放置successor，successor的位置放置0
				if((k=find(w[rr].s))<0)                                      
				{
					++r,   ++rr,   cpy(w[r].e, w[l].e, 4),   cpy(w[r].p, w[l].p, 48);
					w[r].e[i]=p;
					w[r].p[s]=e;
					w[r].ans=w[l].ans+1;
					insert(w[r].s,r);
					cpy(w[rr].s,w[l].s,32);
				}
				else
					w[rr].s[p]=s, w[rr].s[e]=0;
				if(!k)                                                        // k==0时，找到目标态
					return w[l].ans+1;
			}
    }while(l<r);
    return -1;
}

int main()
{
    int n,i,j,k;
    for(i=0;i<4;i++)
        for(j=0;j<7;++j)
			w[0].s[i*8+j]=(i+1)*10+j+1;

		
	//for(i=0;i<25;i+=8)
    //    for(j=0;j<7;++j)
	//		cout << (int)w[0].s[i+j] << " " ;

	//	__int64 d = 0x7FFFFFFF;
	//	printf("%I64d", d);

	//	cout << BKDRHash(w[0].s) << endl;

    scanf("%d",&n);
    while(n--)
    {
        memset(id,-1,sizeof(id));           //  记录状态
        insert(w[0].s,0);                   //  目标态被标记为0

        for(i=0;i<25;i+=8)
            for(w[1].s[i]=(i/8+1)*10+1,j=1; j<8; ++j)
			{
				get(w[1].s[i+j]);           // 这个居然就能把输入的11,21,31,41标为0，原来只是用了getchar();
				w[1].p[w[1].s[i+j]]=i+j;    //
			}

		//for(i=0;i<25;i+=8)
		//{
		//	for(j=0;j<7;++j)
		//		cout << (int)w[1].s[i+j] << " " ;
		//	cout << endl;
		//}

        if(!find(w[1].s))
			printf("0\n");
        else
        {
            for(k=i=0;i<25;i+=8)
                for(j=0;j<8;++j)
                    if(!w[1].s[i+j])
						w[1].e[k++]=i+j;    // 记录下那些 0 的位置。
            w[1].ans=0;
            insert(w[1].s,1);               // 初始态标记为1
            printf("%d\n",bfs());
        }
    }
    return 0;
}

//*/





//*  dfs    6212K	454MS	C++	2256B


#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

const int M=1000007;
char g[32],w[500000][32],t[500000],p[48],e[4],goat[32]={0};
int id[M],ans,tot;

inline int BKDRHash(char *str)
{
	int hash = 0;
	int q=0;

    while (++q<33)
    {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;    //          6212K	407MS	C++	2524B
		//hash = hash * 31 + (*str++);                          //          6212K	438MS	C++	2558B
    }

    return (hash & 0x7FFFFFFF)%M;
	
	//int hash=0,q=0;
	//while(++q<33)
	//	hash=hash*7+(*str++);                                    //         6212K	454MS	C++	2256B
	//return((hash&0x7FFFFFFF)%M);  
	
}

inline void insert(char *c,int i)
{
    int x=BKDRHash(c);
    while(id[x])
    {
        x+=7;
        if(x>=M)x%=M;
    }
    id[x]=i;
}

inline bool cmp(char *p,char *q)
{
    for(int i=0;i<32;++i,++p,++q)
        if(*p!=*q)
			return 1;
    return 0;
}

inline int find(char *c)
{
    int x=BKDRHash(c);
    while(id[x]&&cmp(c,w[id[x]]))
    {
        x+=7;
        if(x>=M)x%=M;
    }
    return id[x];
}

inline void get(char &a)
{
    char ch=getchar();
    while (ch<'0'||ch>'9')ch=getchar();
    for(a=0;ch>='0'&&ch<='9';ch=getchar())a=a*10+ch-48;
    if((a==11)||(a==21)||(a==31)||(a==41))a=0;
}

inline int count()
{
    int c=0;
    for(int i=0;i<32;++i)
    if(g[i]!=goat[i])++c;
    return c/2;
}

inline void cpy(char *p,char *q)
{
    for(int i=0;i<32;++i,++p,++q)
			*p=*q;
}

void dfs(int now)
{
    int cur;
    if(now+(cur=count())>=ans)
		return;
    if(!cur)
    {
        ans=now;
        return;
    }
    int i,j,k;
    for(i=0;i<4;++i)
    if(g[(j=e[i])-1]%10<7&&g[j-1]>0)
    {
        g[e[i]=p[g[j]=g[j-1]+1]]=0;
        p[g[j]]=j;
        if(!(k=find(g))||now+1<t[k])
        {
            if(!k)cpy(w[++tot],g),t[tot]=now+1;
            else t[k]=now+1;
            insert(g,tot);
            dfs(now+1);
        }
        p[g[e[i]]=g[j]]=e[i];
        g[e[i]=j]=0;
    }
}

int main(int argc, char* argv[])
{
    int n,i,j,k;
    for(i=0;i<25;i+=8)
        for(j=0;j<7;++j)
			goat[i+j]=(i/8+1)*10+j+1;

    scanf("%d",&n);
    while(n--)
    {
        for(i=0;i<25;i+=8)
            for(g[i]=(i/8+1)*10+1,j=1; j<8; ++j) 
				get(g[i+j]), p[g[i+j]]=i+j;

        for(k=i=0;i<25;i+=8)
            for(j=0;j<8;++j)
                if(!g[i+j])
					e[k++]=i+j;

        cpy(w[tot=1],g);
        memset(id,0,sizeof(id));
        insert(g,tot);
        ans=1000000;
        dfs(0);
        printf("%d\n",ans<1000000?ans:-1);
    }
    return 0;
}
//*/
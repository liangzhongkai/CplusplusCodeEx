//*                  632K	250MS
//有许多的集合，每个集合里都有相对根节点的关系，合并集合的关键一步是find的r[]转换

#include<iostream>
#include<cstdio>
using namespace std;

int find(int x);

void merge(int a,int b,int p,int q,int d);

struct p_r
{
	int parent;
	int relation;
};

p_r tree[50001];

int main()
{
	int N,K,i=1,n;
	scanf("%d%d", &N, &K);
	n=N;
	while(n--)
	{
		tree[i].parent = i;
		tree[i].relation = 0;
		i++;
	}
	int d,a,b,j=0,p,q;
	while(K--)
	{
		scanf("%d%d%d", &d, &a, &b);
		if(a>N||b>N) 
			j++;
		else
		{
			p=find(a);
			q=find(b);
			if(p!=q)
				merge(a,b,p,q,d);
			else if((tree[b].relation+d+2)%3!=tree[a].relation)j++;
		}	
	}
	cout<<j<<endl;
	return 0;
}

int find(int x)
{
	int temp;
	if(tree[x].parent!=x)
	{
		// 因为路径压缩，该结点的与根结点的关系要更新(因为前面合并时可能还没来得及更新).
		temp=tree[x].parent;
		tree[x].parent=find(tree[x].parent);
		// x与根结点的关系更新(因为根结点变了)，此时的temp为它原来子树的根结点.
		tree[x].relation=(tree[x].relation + tree[temp].relation) % 3;
	}
	return tree[x].parent;
}
void merge(int a,int b,int p,int q,int d)
{
	// 公式是找规律推出来的.
	tree[p].parent=q; // 这里的下标相同，都是tree[p].
	tree[p].relation=(tree[b].relation-tree[a].relation+2+d)%3;
}


// #include <iostream>
// 
// using namespace std;
// 
// int p[50001];
// int r[50001];
// 
// void make_set( int n )
// {
//      for ( int i = 0 ; i <= n ; i++ )
//      {
//           p[i] = i;
//           r[i] = 0;
//      }
// }
// 
// int find_set( int x )
// {
//       if ( p[x] == x ) return x;
// 
//       int temp_px = p[x];    
//       p[x] = find_set( p[x] );  //递归寻找元素x所在集合的代表元素 rx
//       r[x] = ( r[temp_px] + r[x] ) % 3;  //important. 更新r[]数组中x与代表元素的相对关系。更新原因:代表元素在
//                                          //union_set操作中被改变了。至于这个式子的推得.可以枚举rx与p[x], p[x]
//                                          //与x的关系，然后观察得到。更好的方法是向量运算。来自poj 1182 Discuss
//       return p[x];
// }
// 
// void union_set( int rx , int ry , int x , int y , int d )
// {
//       p[ry] = rx;                             // 多叉树
//       r[ry] = ( r[x] - r[y] + 2 + d ) % 3;    // 同上。这两个关系的推得实际上是这道题的关键所在。
// 	                                          // ## 改变两个不同的集合的根节点之间的关系 ##
// 		                                      // 实际上，从数学的角度去看：a与b有关系， b与c有关系，总关系只有3个，就能确认a与c的关系！
// }
// int main()
// {
//      
//      int n, k;
//      int d, x, y, rx, ry;
//      int fs;
//  
//      scanf( "%d%d" , &n , &k );
//      make_set( n );
//      fs = 0;
//      while ( k-- > 0 )
//      {
//            scanf( "%d%d%d" , &d , &x , &y );
//            if ( x > n || y > n || ( d == 2 && x == y ) )
//            {
//                 fs++;
//                 continue;
//            }
//            rx = find_set( x );
//            ry = find_set( y );
//            if ( rx == ry )    //可以确定X与Y的关系，也就可以判断此话的真伪。
//                 if ( d == 1 && r[x] != r[y] )
//                      fs++;
//                 else
//                 {
//                      if ( d== 2 && r[x] != ( r[y] + 2 ) % 3 )
//                           fs++;
//                 }
//            else
//                 union_set( rx , ry , x , y , d );
//    }
// 
//    cout << fs << endl;
//    return 0;
// }



/*
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;

const int MAX = 50005;

int N, K;

struct NODE
{
    int f, w;
    NODE() 
    {
        f = -1;
        w = 0;
    }
    NODE(int ff, int ww) : f(ff), w(ww) {}
}node[MAX];

void ready()
{
    for(int i = 1; i <= N; i++)
        node[i] = NODE();
}

int myFind(int x)
{
    if(node[x].f == -1)  return x;
    int f = myFind(node[x].f);
    node[x].w += node[node[x].f].w;
    node[x].w %= 3;
    node[x].f = f;
    return f;
}

void join(int x, int y, int z)
{
    int xx = myFind(x);
    int yy = myFind(y);
    node[yy].f = xx;
    node[yy].w = (-node[y].w - z + node[x].w + 9) % 3;
}

int main()
{
    while(scanf("%d%d", &N, &K) != 2)
    {
        scanf("%d%d", &N, &K);
        int ans = 0;
        ready();
        while(K--)
        {
            int a, b, c;
            scanf("%d%d%d", &c, &a, &b);
            if(a > N || b > N)
            {
                ans++;
                continue;
            }
            int aa = myFind(a);
            int bb = myFind(b);
            if(aa == bb)
            {
                if(c == 1 && node[a].w != node[b].w)  ans++;
                else if(c == 2)
                {
                    if((node[a].w - node[b].w + 6) % 3 != 1)  ans++;
                }
            }
            else  join(a, b, c - 1);
        }
        printf("%d\n", ans);
    }
}
//*/



/*
#include <iostream>

using namespace std;
struct ANI
{
    int relation;
    int parent;
}Animal[100000];
int N,V;

int Froot(int i)
{
    int t;
    if (Animal[i].parent!=-1)
    {
       t=Animal[i].parent;
       Animal[i].parent=Froot(t);
       Animal[i].relation=(Animal[i].relation+Animal[t].relation)%3;
       return Animal[i].parent;
    }
    else
    {
       Animal[i].relation=0;
       return i;
    }
   
}
void Init()
{
    for (int i=0;i<V;i++)
    {
        Animal[i].parent=-1;
        Animal[i].relation=0;
    }
}
int main()
{
    int x,y,d,a,b,cnt;
    cnt=0;
    int i=0;
    scanf("%d %d",&V,&N);
    Init();
    for (i=0;i<N;i++)
    {
      scanf("%d %d %d",&d,&x,&y);
   
      if(x>V||y>V)
      {
          cnt++;
          continue;
      }
      else if(d==1)
      {
       a=Froot(x);
       b=Froot(y);
       if(a==b)
       {
          if(Animal[x].relation!=Animal[y].relation)cnt++;
       }
       else
       {
           Animal[a].parent=b;
           Animal[a].relation=(Animal[y].relation-Animal[x].relation+3)%3;
       }
      }
      else
      {
          if(x==y)cnt++;
          else
          {
           a=Froot(x);
           b=Froot(y);
           if(a==b)
           {
               if(Animal[x].relation!=(Animal[y].relation+1)%3)cnt++;
           }
           else
              
           {
               Animal[a].parent=b;
               Animal[a].relation=(Animal[y].relation-Animal[x].relation+4)%3;
           }
          }
      }
    }
    printf("%d",cnt);
    return 0;
}
//*/








 

/*                                 1008K	266MS
#include<iostream>
#include<cstdio>
#include<string>
#define MAX 50001
using namespace std;
struct Node{
    long food, enemy, rank, parent;
}node[MAX];
long N,K;
long root(long x){
    if( node[x].parent == x )    return x;
    else                         return root(node[x].parent);
}
long Union(long x,long y){//有时候，还是返回一个值好点
    long a=root(x),b=root(y);
    if (a==b||a==0||b==0)
        return a!=0?a:b; 
    else {
        if ( node[a].rank==node[b].rank )
            node[b].rank++;
        if ( node[a].rank > node[b].rank )
            node[b].parent = a;
        else
            node[a].parent = b;
    }
    node[a].food = node[b].food = Union(node[a].food,node[b].food);
    node[a].enemy = node[b].enemy = Union(node[a].enemy,node[b].enemy);
    return node[a].parent;
}
void Enemy(long x,long y){//建立天敌关系
    long xr = root(x),yr = root(y);
    if(root(node[xr].food)==yr)    return;
    //the left side of the following equations are necessary!
    //the value of .food or .enemy may be 0
    node[xr].food = Union( node[xr].food,yr );
    node[yr].enemy = Union( node[yr].enemy,xr );
    node[xr].enemy = node[yr].food = Union( node[xr].enemy,node[yr].food );

    long z = node[xr].enemy;
    if (z){
        Union( node[z].food,xr );
        Union( node[z].enemy,yr );
    }
}

bool TorF(long moni,long x,long y){
    if ( x>N||y>N )
        return false;
    x = root(x);
    y = root(y);
    long xe,xf;
    xe = root( node[x].enemy );
    xf = root( node[x].food );
    switch (moni){
    case 1:return(x==0||y==0||x==y||xe!=y&&xf!=y);break;
    case 2:return(x!=y&&(xe==0||xe!=y));
    }
}

int main(){
    long sum = 0;//sum of lies
    scanf("%ld%ld",&N,&K);
    for ( long i = 0;i <= N;i++ )
        node[i].parent = i;
    for ( long i = 1,moni,x,y;i <= K;i++ ){
        scanf("%ld%ld%ld",&moni,&x,&y);
        if ( TorF(moni,x,y) )
            switch (moni){
            case 1:Union(x,y);break;
            case 2:Enemy(x,y);
            }
        else
            sum++;
    }
    cout << sum << endl;
    return 0;
}
//*/

/*
80 300
1 38 13
2 9 34
2 62 52
2 64 74
2 80 18
2 31 14
2 23 22
2 41 30
2 60 12
2 80 81
2 18 35
1 53 76
2 9 58
1 9 14
1 28 30
2 49 9
2 65 24
1 30 69
2 79 27
2 32 58
2 59 49
2 26 15
1 65 8
2 11 65
2 65 75
1 67 73
2 19 19
2 50 10
2 25 34
1 68 9
2 54 50
1 13 34
2 78 21
2 40 1
2 55 2
2 38 36
1 81 30
2 45 51
2 1 49
1 46 9
1 21 70
2 71 41
1 21 11
1 49 48
2 46 71
2 45 13
2 79 57
2 58 77
2 66 77
2 44 44
2 69 48
2 21 50
2 30 2
1 30 45
2 53 45
2 26 7
2 23 23
2 24 34
2 47 29
1 43 17
1 25 27
2 19 42
1 77 47
2 64 10
1 15 46
1 58 20
2 19 24
2 56 32
2 75 71
2 11 57
1 11 58
2 67 68
2 49 10
2 7 56
2 4 67
2 66 45
1 63 52
2 4 35
2 63 20
1 14 54
1 72 16
1 39 69
1 50 13
1 13 68
2 58 61
2 66 14
2 15 37
2 70 3
2 55 69
1 79 50
2 25 66
2 34 28
2 63 1
2 3 16
1 76 41
2 41 31
2 8 57
1 5 74
2 10 1
1 30 76
2 46 45
2 10 28
2 40 69
1 17 13
2 61 42
2 32 29
2 42 62
2 75 19
1 68 73
1 56 6
2 7 37
2 79 26
2 9 43
2 30 57
2 33 23
2 43 28
2 25 6
2 14 80
2 76 58
2 19 9
2 57 3
2 56 71
2 23 74
1 20 3
1 55 53
1 58 17
1 21 76
1 11 53
2 55 23
2 25 26
1 27 44
1 65 37
1 54 42
1 66 57
2 36 74
1 49 58
1 47 61
2 35 35
2 49 54
1 81 62
1 76 3
2 41 21
1 11 45
1 33 9
2 48 65
2 50 53
1 4 40
2 41 6
1 7 75
2 4 53
1 49 37
2 60 31
2 58 61
1 34 24
2 52 41
1 13 14
1 26 30
2 19 23
2 73 22
2 6 28
2 37 14
1 26 50
1 43 59
2 57 33
2 23 14
2 28 77
1 6 63
1 80 32
2 58 15
1 9 44
1 3 23
2 71 62
2 74 35
2 3 79
2 53 37
1 17 7
1 76 49
2 53 4
2 23 2
1 26 29
1 44 49
2 37 55
2 42 10
2 57 28
2 74 65
2 58 13
1 61 19
2 35 77
2 54 74
1 62 16
2 3 43
1 21 41
2 45 46
2 9 19
2 65 63
2 53 15
2 40 79
1 6 11
2 75 31
1 53 60
1 37 37
1 31 33
2 61 74
1 24 46
1 41 3
1 14 16
1 30 28
2 23 20
1 22 75
1 28 68
2 14 56
1 50 7
2 59 79
1 33 9
2 14 30
2 77 33
1 63 43
2 32 25
2 15 14
1 44 76
2 23 19
2 62 57
2 35 56
2 79 23
2 37 20
2 7 55
2 49 58
1 4 21
2 2 11
2 29 55
2 49 25
2 55 27
1 10 65
2 28 54
2 65 66
2 13 36
1 19 49
1 77 47
2 74 35
2 16 49
2 43 81
2 41 76
2 46 41
2 19 11
2 63 33
2 15 48
2 79 50
1 11 4
2 31 41
2 60 7
2 37 4
1 33 49
1 74 60
1 46 58
2 3 34
2 16 52
2 28 13
2 20 26
2 75 19
1 68 73
1 56 6
2 7 37
2 79 26
2 9 43
2 30 57
2 33 23
2 43 28
2 25 6
2 14 80
2 76 58
2 19 9
2 57 3
2 56 71
2 23 74
1 20 3
1 55 53
1 58 17
1 21 76
1 11 53
2 55 23
2 25 26
1 27 44
1 65 37
1 54 42
1 66 57
2 36 74
1 49 58
1 47 61
2 35 35
2 49 54
1 81 62
1 76 3
2 41 21
1 11 45
1 33 9
2 48 65
2 50 53
1 4 40
2 41 6
1 7 75

答案：154
*/

// 
// void Initset(){
// 	// memset(father, -1, sizeof(father));
// 	for(int i=0; i<N; i++)
// 		 father[i] = -1;
// }
// 
// int Findset(int x){
// 	int s, tmp;
// 	for(s=x; father[s]>=0; s=father[s]);
// 	while(s!=x){
// 		tmp = father[x];
// 		father[x] = s;
// 		x = tmp;
// 	}
// 	return s;
// }
// 
// void Unionset(int x, int y){
// 	int rx = Findset(x), ry = Findset(y);
// 	int tmp = father[rx] + father[ry];
// 	if(father[rx]>father[ry]){
// 		father[rx] = ry;
// 		father[ry] = tmp;
// 	}
// 	else{
// 		father[ry] = rx;
// 		father[rx] = tmp;
// 	}
// }
#include<iostream>

using namespace std;

int main()
{
	int 

	return 0;
}




/*
#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<queue>
#include<memory>

using namespace std;

struct edge
{
	int r;
	int w;
	edge( int a, int b )
	{
		r = a;
		w = b;
	}
};
typedef pair<int, int> pii;
int dist[101];
int nn; //点数
const int INF = 1000000;
vector<edge> Link[101];

void dijkstra( int s, int e )
{
	priority_queue<pii> q;
	int i;

	for( i=1; i<=nn; i++ )
		dist[i] = (i==s)?0:INF;

	q.push( make_pair( s, dist[s]) );

	while( !q.empty() )
	{
		pii temp = q.top();
		q.pop();
		int x = temp.first;

		//if( temp.second==dist[])
		//判断该点是否被计算过？   if( flag[i]==true )
		

		for( i=0; i<Link[x].size(); i++ )
		{
			if( dist[Link[x][i].r]>dist[x]+Link[x][i].w )
			{
				dist[Link[x][i].r] = dist[x]+Link[x][i].w;
		        q.push( make_pair(Link[x][i].r, dist[Link[x][i].r]) );
			}
		}

	}
}

int main()
{
	int tc;
	int en;  //边数
	int i;
	string temp1, temp2;
	int count = 0;
	int weight;
	int ans;

	cin >> tc;
	while( tc-- )
	{
		map<string,int> place;
		
		cin >> en;
		for( i=0; i<en; i++ )
		{
			cin >> temp1 >> temp2;
			if( place.find(temp1)==place.end() )
				place[temp1] = ++count;            
			if( place.find(temp2)==place.end() )
				place[temp2] = ++count;

			cin >> weight;
            Link[place[temp1]].push_back( edge(place[temp2], weight) );
			Link[place[temp2]].push_back( edge(place[temp1], weight) );
		}

		nn = place.size();
		ans = 0;
		cin >> temp1 >> temp2;
		if( temp1==temp2 )
			cout << "0" << endl;
		if( !place.count(temp1) || !place.count(temp2) )
			cout << "-1" << endl;
		else
		{
			dijkstra( place[temp1], place[temp2] );
			cout << dist[place[temp2]] << endl;
		}
	}
	

	return 0;
}

//*/



/*    Run Time: 0secs    Run Memory: 312KB
//Dijkstra邻接表做法  
//邻接表使得计算复杂度成为O(E*n),但图为稀疏图时效率比邻接矩阵高，但当图为稠密图时，E与n^2同阶,计算复杂度最坏可到O(n^3)  
//Dijkstra优先队列实现(相当于堆优化)  
//优先队列的实现的Dijstra可以使得算法在处理稠密图时速度也比使用邻接矩阵要快  
//原因在于插入队列的元素的前提是边关系必须满足可松弛条件，对于稠密图而言，可松弛条件是常常不满足的  
//因此插入队列的元素便比边数少很多  
//下面使用vector容器实现邻接表的，因为直观易懂  
//G[u]存放的是与结点u邻接的所有结点  
//遍历邻接边：for(int i = 0;i < G[u].size();++i)  
#include<iostream>  
#include<vector>  
#include<map>  
#include<queue>  
#include<string>  
#include<cstring>  
using namespace std;  
const int MAXN = 205;  
const int INF = 1000000;  
int dis[MAXN];  
int n;//结点数量  
typedef pair<int,int> pii;   
struct edge//建立边的结构体  
{  
    int u;  
    int v;  
    int w;  
    edge(int uu,int vv,int ww)  
    {  
        u = uu;  
        v = vv;  
        w = ww;  
    }  
};  
int dijkstra(int st,int ed,vector<edge> G[])  
{  
    priority_queue<pii> q;//优先队列是默认小元素先出队  
    for(int i = 0;i < n;++i)  
        dis[i] = (i == st ? 0 : INF);//初始化dis  
    q.push(make_pair(dis[st],st));//将起点插入队列，pair默认是优先处理first元素，故插入优先队列先弹出队列的优先级是依据dis[]大小  
    while(!q.empty())  
    {  
        pii u = q.top();  
        q.pop();  
        int x = u.second;  
        if(u.first != dis[x]) continue;//可避免结点的重复拓展，提高优先队列处理速度。因为Dijkstra算法对每个结点都会进行一次标号。  
                                        //这里每一个元素出队都相当于处理一次已标号结点，如果出队的这个元素，他带的dis,和当前的dis不相同，证明这个结点是被处理过的  
        for(int  i = 0;i < G[x].size();++i)  
        {  
            int y = G[x][i].v;  
            int w = G[x][i].w;  
            if(dis[y] > dis[x] + w)  
            {  
                dis[y] = dis[x] + w;  
                q.push(make_pair(dis[y],y));  
            }  
        }  
    }  
    if(dis[ed] == INF)  
        return -1;  
    else
		return dis[ed];  
}  
      
int main()  
{  
    //freopen("in.txt","r",stdin);  
    int t,w;  
    string u,v;  
    cin >> t;  
    while(t--)  
    {  
        n = 0;//初始化结点数目  
        int e;  
        cin >> e;  
        map<string,int> M;  
        vector<edge> G[MAXN];//邻接表  
        for(int i = 0;i < e;++i)  
        {  
            cin >> u >> v >> w;//输入点1，点2， 权值  
            if(!M.count(u))  
                M.insert(make_pair(u,n++));  
            if(!M.count(v))  
                M.insert(make_pair(v,n++));//利用map关联容器为字符串型的边进行标号  
            edge E1(M[u],M[v],w);//初始化边，必须调换结点才能插入vector邻接表  
            edge E2(M[v],M[u],w);  
            G[M[u]].push_back(E1);//建立邻接表  
            G[M[v]].push_back(E2);  
        }  
        string st,ed;  
        cin >> st >> ed;  
        if(st == ed)  
            cout << 0 << endl;  
        else if(!M.count(st) || !M.count(ed))  
            cout << -1 << endl;  
        else      
            cout << dijkstra(M[st],M[ed],G) << endl;  
    }  
    return 0;  
}  
//*/









/*    Run Time: 0secs    Run Memory: 484KB

#include <iostream>
#include <string>
#include <map>
#include <memory.h>
#define INF 1000000
#define MAX 210
using namespace std;
 
int cost[MAX][MAX];
int my_distance[MAX];
bool isvisit[MAX];
 
int n;
int edge_count;
 
void shortest_path(int);
int main()
{
    int cases;
    int  start, goal;
    string a, b;
    int distance;
 
    int count;
    map<string, int> name;
    map<string, int>::iterator iter1, iter2;
 
    cin >> cases;
    while (cases--)
    {
 
        cin >> n;
 
        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                if (i != j) cost[i][j] = INF;
                else cost[i][j] = 0;
 
        count = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> a >> b >> distance;
            iter1 = name.find(a);
            iter2 = name.find(b);
            if (iter1 != name.end() && iter2 != name.end())
            {
                cost[iter1->second][iter2->second] = distance;
                cost[iter2->second][iter1->second] = distance;
            }
            else if (iter1 == name.end() && iter2 == name.end())
            {
                if (a != b)
                {
                    cost[count][count+1] = distance;
                    cost[count+1][count] = distance;
                    name.insert(pair<string, int>(a, count++));
                    name.insert(pair<string, int>(b, count++));
                }
                else
                {
                    cost[count][count] = distance;
                    name.insert(pair<string, int>(a, count++));
                }
 
            }
            else if (iter1 == name.end() && iter2 != name.end())
            {
                cost[count][iter2->second] = distance;
                cost[iter2->second][count] = distance;
                name.insert(pair<string, int>(a, count++));
            }
            else
            {
                cost[count][iter1->second] = distance;
                cost[iter1->second][count] = distance;
                name.insert(pair<string, int>(b, count++));
            }
        }
 
        edge_count = count;
        cin >> a >> b;
        iter1 = name.find(a);
        iter2 = name.find(b);
 
        if (iter1 != name.end() && iter2 != name.end())
        {
            start =(name.find(a))->second;
            goal = (name.find(b))->second;
 
            shortest_path(start);
 
            if (my_distance[goal] < INF)
                cout << my_distance[goal] << endl;
            else
                cout << "-1" << endl;
 
        }
        else if (a == b)
            cout << "0" << endl;
        else
            cout << "-1" << endl;
 
        name.clear();
    }
    return 0;
}
 
void shortest_path(int start)
{
    memset(isvisit, false, sizeof(isvisit));
 
    for (int i = 0; i < edge_count; i++)
        my_distance[i] = cost[start][i];
 
    isvisit[start] = true;
    int _min = INF, min_point;
    int next;
 
    for (int i = 0; i < edge_count-1; i++)
    {
        _min = INF;
        for (int j = 0; j < edge_count; j++)
            if (!isvisit[j] && _min > my_distance[j])
            {
                _min = my_distance[j];
                min_point = j;
            }
 
        isvisit[min_point] = true;
 
        for (int j = 0; j < edge_count; j++)
            if (!isvisit[j] && my_distance[j] > cost[min_point][j] + my_distance[min_point])
                my_distance[j] =  cost[min_point][j] + my_distance[min_point];
 
    }
}


//*/







/*    Run Time: 0secs    Run Memory: 476KB


//邻接矩阵Dijkstra,得开始学用邻接表的方式来处理单源最短路问题 可以把复杂度提高到O(ElgE)
//学会了map关联容器，十分强大的类

#include<iostream>
#include<string>
#include<cstring>
#include<map>//关联容器
using namespace std;
const int INF = 1000000;//定义无穷，注意不能太大，否则在更新结点过程中可能产生溢出
int G[205][205];//100条边最多只有200个结点
int dis[205];
bool flag[205];
int t,road,d,n;
string start,end;
int dijkstra(int a,int b)//Dijkstra处理从起点a到b的最短路
{
	memset(flag,0,sizeof(flag));
	for(int i = 0;i < n;++i)
		dis[i] = (i == a ? 0 : INF);//初始化dis数组，起点应初始化为0
	for(int i = 0;i < n;++i)
	{
		int _min = INF,x = a;//对标号变量的初始化应该是起点a
		for(int y = 0;y < n;++y)
		{
			if(!flag[y] && dis[y] < _min)//从未标号结点中选出dis最小的结点x
			{
				_min = dis[y];
				x = y;
			}
		}
		flag[x] = 1;//标记x
		for(int y = 0;y < n;++y)
			dis[y] = min(dis[y],dis[x] + G[x][y]);//更新从x出发到其他点的距离
	}
	if(flag[b])//如果终点是有标号结点，则证明a点到b点是连通的
		return dis[b];//返回dis值
	else return -1;
}
int main()
{
	//freopen("in.txt","r",stdin);
	cin >> t;
	while(t--)
	{
		cin >> road;
		for(int i = 0;i < 205;++i)
			for(int j = 0;j < 205;++j)
				G[i][j] = (i == j ? 0 : INF);
		map<string, int> edge_map;//利用关联容器处理名字到图结点编号的转化
		n = 0;
		for(int i = 0;i < road;++i)
		{
			cin >> start >> end >> d;
			{
				if(!edge_map.count(start))//如果从来没出现过这个结点
				{
					edge_map[start] = n++;//为这个结点定义一个标号
				}
				if(!edge_map.count(end))
				{
					edge_map[end] = n++;
				}
				G[edge_map[start]][edge_map[end]] = G[edge_map[end]][edge_map[start]] = d;//无向图双向联通
			}
		}
		cin >> start >> end;
		if(start == end)//名字相同时返回0，即使不存在这个点……没见过这么扑街的条件，害我WA了N次
			cout << 0 << endl;
		else if(!edge_map.count(start) || !edge_map.count(end))//其中有一个点的边不存在，返回不可达
			cout << -1 << endl;
		else 
			cout << dijkstra(edge_map[start],edge_map[end]) << endl;
	}
	return 0;
}

//*/


















/*    Run Time: 0secs    Run Memory: 312KB


#include <iostream>
 #include <map>
 #include <vector>
 #include <string>
 #include <queue>
 using namespace std;
 const int MaxNum = 203;
 const int MAX = 999999; //定义一个较大的数 ， 用于松弛处理
 //定义距离数组
 int dis[MaxNum];
 int n ; //节点的数目 : n+ 1 
  typedef pair<int,int> element;   
  //定义的边 
  struct edge
 {
     int des_node ; //指向的节点 ， 
     int weight ; //权重
     edge( int d , int w)
     {
         des_node = d ;
         weight = w ;
     }
 };
 
 int  dijkstra ( int start , int end  , vector<edge> G[] )
 {
     priority_queue< element ,  vector<element >  ,   greater<element>  > q ; //定义一个优先队列 ， greater是最小堆
 //进行初始化 ， 起点为 0 ，其余的为无穷远
     for ( int i = 0 ; i < n ; i++)
         dis[i] = ( i == start ? 0 : MAX);
     //将起点压入队列
     q.push(make_pair(dis[start],start));
     
     while(!q.empty())  
     {  
         element u = q.top();        //每次都弹出最小值，再在这最小值基础上修改其它结点的最短距离,就是Dijkstra算法
         q.pop();  
         //x为哪个点解
         int x = u.second;   
        //x.first为dis[x]距离
         for(int  i = 0;i < G[x].size() ;++i)// G里存放着邻接表  
         {  
             int y = G[x][i].des_node;  
             int w = G[x][i].weight;  
             //松弛处理
             if(dis[y] > dis[x] + w)  
             {  
                 dis[y] = dis[x] + w;  
                 q.push(make_pair(dis[y],y));  
             }  
         }  
     }  
     if(dis[end] == MAX)  
         return -1;  
     else return dis[end];  
 }
 int main()
 {
     int t , NumE , wei ;
     cin >> t ;
     string temp1 , temp2 , origin ,destination;
     while ( t--)
     {
         n = 0 ; 
         map<string,int> M;                    //把每个地址转化成相对应的唯一的数字
         vector<edge> G[MaxNum];
         cin >> NumE ;
         for ( int i = 0 ; i < NumE ; i ++)
         {
             cin >> temp1 >> temp2 >> wei;
             if ( !M.count( temp1)) 
                 M[temp1] = n++ ;
             if ( !M.count( temp2 ))
                 M[temp2] = n ++ ;
             G[M[temp1]].push_back(  edge(M[temp2] , wei) );
             G[M[temp2]].push_back(  edge ( M[temp1] , wei ));
         }
         cin >> origin >> destination ;
         if ( origin == destination )
             cout <<"0"<<endl;
         else
             if (  !M.count( origin )  || !M.count( destination ) )
                 cout <<"-1" << endl;
             else
                 cout << dijkstra( M[ origin ] , M[ destination ] , G ) << endl;
 
     }
     return 0 ;
 }
//*/
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
int nn; //����
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
		//�жϸõ��Ƿ񱻼������   if( flag[i]==true )
		

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
	int en;  //����
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
//Dijkstra�ڽӱ�����  
//�ڽӱ�ʹ�ü��㸴�Ӷȳ�ΪO(E*n),��ͼΪϡ��ͼʱЧ�ʱ��ڽӾ���ߣ�����ͼΪ����ͼʱ��E��n^2ͬ��,���㸴�Ӷ���ɵ�O(n^3)  
//Dijkstra���ȶ���ʵ��(�൱�ڶ��Ż�)  
//���ȶ��е�ʵ�ֵ�Dijstra����ʹ���㷨�ڴ������ͼʱ�ٶ�Ҳ��ʹ���ڽӾ���Ҫ��  
//ԭ�����ڲ�����е�Ԫ�ص�ǰ���Ǳ߹�ϵ����������ɳ����������ڳ���ͼ���ԣ����ɳ������ǳ����������  
//��˲�����е�Ԫ�ر�ȱ����ٺܶ�  
//����ʹ��vector����ʵ���ڽӱ�ģ���Ϊֱ���׶�  
//G[u]��ŵ�������u�ڽӵ����н��  
//�����ڽӱߣ�for(int i = 0;i < G[u].size();++i)  
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
int n;//�������  
typedef pair<int,int> pii;   
struct edge//�����ߵĽṹ��  
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
    priority_queue<pii> q;//���ȶ�����Ĭ��СԪ���ȳ���  
    for(int i = 0;i < n;++i)  
        dis[i] = (i == st ? 0 : INF);//��ʼ��dis  
    q.push(make_pair(dis[st],st));//����������У�pairĬ�������ȴ���firstԪ�أ��ʲ������ȶ����ȵ������е����ȼ�������dis[]��С  
    while(!q.empty())  
    {  
        pii u = q.top();  
        q.pop();  
        int x = u.second;  
        if(u.first != dis[x]) continue;//�ɱ�������ظ���չ��������ȶ��д����ٶȡ���ΪDijkstra�㷨��ÿ����㶼�����һ�α�š�  
                                        //����ÿһ��Ԫ�س��Ӷ��൱�ڴ���һ���ѱ�Ž�㣬������ӵ����Ԫ�أ�������dis,�͵�ǰ��dis����ͬ��֤���������Ǳ��������  
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
        n = 0;//��ʼ�������Ŀ  
        int e;  
        cin >> e;  
        map<string,int> M;  
        vector<edge> G[MAXN];//�ڽӱ�  
        for(int i = 0;i < e;++i)  
        {  
            cin >> u >> v >> w;//�����1����2�� Ȩֵ  
            if(!M.count(u))  
                M.insert(make_pair(u,n++));  
            if(!M.count(v))  
                M.insert(make_pair(v,n++));//����map��������Ϊ�ַ����͵ı߽��б��  
            edge E1(M[u],M[v],w);//��ʼ���ߣ�������������ܲ���vector�ڽӱ�  
            edge E2(M[v],M[u],w);  
            G[M[u]].push_back(E1);//�����ڽӱ�  
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


//�ڽӾ���Dijkstra,�ÿ�ʼѧ���ڽӱ�ķ�ʽ������Դ���·���� ���԰Ѹ��Ӷ���ߵ�O(ElgE)
//ѧ����map����������ʮ��ǿ�����

#include<iostream>
#include<string>
#include<cstring>
#include<map>//��������
using namespace std;
const int INF = 1000000;//�������ע�ⲻ��̫�󣬷����ڸ��½������п��ܲ������
int G[205][205];//100�������ֻ��200�����
int dis[205];
bool flag[205];
int t,road,d,n;
string start,end;
int dijkstra(int a,int b)//Dijkstra��������a��b�����·
{
	memset(flag,0,sizeof(flag));
	for(int i = 0;i < n;++i)
		dis[i] = (i == a ? 0 : INF);//��ʼ��dis���飬���Ӧ��ʼ��Ϊ0
	for(int i = 0;i < n;++i)
	{
		int _min = INF,x = a;//�Ա�ű����ĳ�ʼ��Ӧ�������a
		for(int y = 0;y < n;++y)
		{
			if(!flag[y] && dis[y] < _min)//��δ��Ž����ѡ��dis��С�Ľ��x
			{
				_min = dis[y];
				x = y;
			}
		}
		flag[x] = 1;//���x
		for(int y = 0;y < n;++y)
			dis[y] = min(dis[y],dis[x] + G[x][y]);//���´�x������������ľ���
	}
	if(flag[b])//����յ����б�Ž�㣬��֤��a�㵽b������ͨ��
		return dis[b];//����disֵ
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
		map<string, int> edge_map;//���ù��������������ֵ�ͼ����ŵ�ת��
		n = 0;
		for(int i = 0;i < road;++i)
		{
			cin >> start >> end >> d;
			{
				if(!edge_map.count(start))//�������û���ֹ�������
				{
					edge_map[start] = n++;//Ϊ�����㶨��һ�����
				}
				if(!edge_map.count(end))
				{
					edge_map[end] = n++;
				}
				G[edge_map[start]][edge_map[end]] = G[edge_map[end]][edge_map[start]] = d;//����ͼ˫����ͨ
			}
		}
		cin >> start >> end;
		if(start == end)//������ͬʱ����0����ʹ����������㡭��û������ô�˽ֵ�����������WA��N��
			cout << 0 << endl;
		else if(!edge_map.count(start) || !edge_map.count(end))//������һ����ı߲����ڣ����ز��ɴ�
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
 const int MAX = 999999; //����һ���ϴ���� �� �����ɳڴ���
 //�����������
 int dis[MaxNum];
 int n ; //�ڵ����Ŀ : n+ 1 
  typedef pair<int,int> element;   
  //����ı� 
  struct edge
 {
     int des_node ; //ָ��Ľڵ� �� 
     int weight ; //Ȩ��
     edge( int d , int w)
     {
         des_node = d ;
         weight = w ;
     }
 };
 
 int  dijkstra ( int start , int end  , vector<edge> G[] )
 {
     priority_queue< element ,  vector<element >  ,   greater<element>  > q ; //����һ�����ȶ��� �� greater����С��
 //���г�ʼ�� �� ���Ϊ 0 �������Ϊ����Զ
     for ( int i = 0 ; i < n ; i++)
         dis[i] = ( i == start ? 0 : MAX);
     //�����ѹ�����
     q.push(make_pair(dis[start],start));
     
     while(!q.empty())  
     {  
         element u = q.top();        //ÿ�ζ�������Сֵ����������Сֵ�������޸�����������̾���,����Dijkstra�㷨
         q.pop();  
         //xΪ�ĸ����
         int x = u.second;   
        //x.firstΪdis[x]����
         for(int  i = 0;i < G[x].size() ;++i)// G�������ڽӱ�  
         {  
             int y = G[x][i].des_node;  
             int w = G[x][i].weight;  
             //�ɳڴ���
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
         map<string,int> M;                    //��ÿ����ַת�������Ӧ��Ψһ������
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
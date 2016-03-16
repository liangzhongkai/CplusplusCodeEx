
/*   671MS	  37320K	1779 B	C++
#include<iostream>
#include<queue>
#include<fstream>

using namespace std;

ifstream fin("data.txt");
#define cin fin 

const int N = 1005;
const int INF = 99999999;

struct point{
	int t, w;
	point(int a, int b):t(a),w(b){}
};
vector<point> mp[N];

struct node{
	int id, w, n;
	node(){}
	node(int a, int b):id(a),w(b),n(1){}
	bool operator<(const node &a)const{
		return w>a.w;
	}
};
priority_queue<node> q;

int dist[N];
int dd[2], cn[2];

int main()
{
	int tc;
	int m, n;
	int a, b, c;
	int s, e;
	int i;

	cin >> tc;
	while(tc--){
		cin >> n >> m;
		for(i=1; i<=m; i++){
			mp[i].clear();
		}
		
		for(i=1; i<=m; i++){
			cin >> a >> b >> c;
			mp[a].push_back(point(b, c));
		}
		cin >> s >> e;

		while(!q.empty()){
			q.pop();
		}
		for(i=1; i<=n; i++){
			dist[i] = INF;
		}
		dd[0] = dd[1] = INF;
		cn[0] = cn[1] = 0;
		node tmp, temp;
		q.push(node(s, 0));
		dist[s] = 0;
		while(!q.empty()){
			temp = q.top();
			q.pop();

			if(temp.w>dd[1])
					break;

			if(temp.id==e){
				if(temp.w < dd[0]){
					dd[1] = dd[0];
					dd[0] = temp.w;
					cn[1] = cn[0];
					cn[0] = temp.n;
				}
				else if(temp.w == dd[0]){
					cn[0]++;
				}
				else if(temp.w < dd[1]){
					dd[1] = temp.w;
					cn[1] = temp.n;
				}
				else if(temp.w == dd[1]){
					cn[1]++;
				}
			}

			for(i=0; i<mp[temp.id].size(); i++){
				int t = mp[temp.id][i].t;
				//if(dist[t] > dist[temp.id] + mp[temp.id][i].w){
					dist[t] = dist[temp.id] + mp[temp.id][i].w;
				//}
				int d = dist[t];
				//cout << d << " ";
				tmp = node(t, d);
				tmp.n = temp.n;
				q.push(tmp);
			}
		}
		//cout << dd[0] << " " << dd[1] << " " << cn[0] << " " << cn[1] << endl;

		if(dd[0]==dd[1]-1)
			cn[0] += cn[1];
		cout << cn[0] << endl;
	}

	return 0;
}
//*/




//*     46MS	520K	2251 B	C++

#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
const int N = 1001;

struct node
{
    int v,w;
    node(){}
    node(int v,int w):v(v),w(w){}
};

vector<node> g[N];
int n,dist[N][2],cnt[N][2];
bool vis[N][2];

void Dijkstra(int s)
{
	int i, j;
    for(i=1;i<=n;i++)
    {
        dist[i][0]=INT_MAX;
        dist[i][1]=INT_MAX;
    }
    memset(vis,false,sizeof(vis));
    dist[s][0]=0;
    cnt[s][0]=1;
    for(i=0;i<2*n;i++)  // 每一个节点会被更新俩次，最短和次短，所以是2*n
    {
        int temp=INT_MAX,u=-1,k;
        for(j=1;j<=n;j++)
            if(!vis[j][0] && dist[j][0]<temp){  // 对于每一个节点，肯定是先更新最短
                k=0;                            // 但是对于全部点来讲，最短和次短像在并行计算
                temp=dist[j][0];
                u=j;
            }
            else if(!vis[j][1] && dist[j][1]<temp){  // 然后更新次短
                k=1;
                temp=dist[j][1];
                u=j;
            }

        if(u==-1)
            break;

        vis[u][k]=true;
        vector<node>::iterator it=g[u].begin();
        for(; it!=g[u].end(); it++)
        {
            int newdis = dist[u][k] + it->w;
            int v = it->v;
            if(newdis<dist[v][0])         // dist[][0]表示最短路，dist[][1]表示次短路
            {                             // cnt[][]表示有多少条最短/次短路。
                dist[v][1]=dist[v][0];
                dist[v][0]=newdis;
				cnt[v][1]=cnt[v][0];
                cnt[v][0]=cnt[u][k];
            }
            else if(newdis==dist[v][0])
                cnt[v][0]+=cnt[u][k];
            else if(newdis<dist[v][1])
            {
                dist[v][1]=newdis;
                cnt[v][1]=cnt[u][k];
            }
            else if(newdis==dist[v][1])
                cnt[v][1]+=cnt[u][k];
        }
    }
}

int main()
{
    int T,m,a,b,c;
    int s,t;
	int i;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);

        for(i=1;i<=n;i++)
            g[i].clear();

        for(i=0;i<m;i++)
        {
            scanf("%d %d %d",&a,&b,&c);
            g[a].push_back(node(b,c));
        }
        scanf("%d %d",&s,&t);

        Dijkstra(s);

        int ans=cnt[t][0];
        if(dist[t][1]==dist[t][0]+1)
            ans+=cnt[t][1];
        printf("%d\n",ans);
    }
    return 0;
}
//*/
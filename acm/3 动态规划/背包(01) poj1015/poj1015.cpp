/*    400K	16MS	C++	2371B
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int f[30][1000],path[30][1000] ;
int p[300],d[300],ans[30] ;


int main()
{
      int n,m;
	  int i, j, k;
      int tcase = 0 ;
      scanf("%d%d",&n,&m) ;
      while(n)
	  {
            tcase++ ;
            memset(f,-1,sizeof(f)) ;
            memset(path,0,sizeof(path)) ;
            int p_d = m*20 ;
            f[0][p_d] = 0 ;
            for (i=1 ; i<=n ; i++)
			{
                  scanf("%d%d",p+i,d+i) ;
            }
            for (j=0 ; j<m ; j++)
			{
                  for (k=0 ; k<=p_d*2 ; k++)
				  {
                        if (f[j][k]>=0)
						{
                              for (i=1 ; i<=n ; i++)
							  {
                                    if (f[j][k]+p[i]+d[i]>f[j+1][k+p[i]-d[i]])
									{
                                          int t1=j,t2=k ;
                                          while (t1>0 && path[t1][t2]!=i)
										  {
                                                t2 -= p[path[t1][t2]]-d[path[t1][t2]] ;
                                                t1-- ;
                                          }
                                          if (t1==0)
										  {
                                                f[j+1][k+p[i]-d[i]] = f[j][k]+p[i]+d[i] ;
                                                path[j+1][k+p[i]-d[i]] = i ;
                                          }
                                    }
                              }
                        }
                  }
            }

            i=p_d ;
            j=0, k=0 ;

            while (f[m][i+j]<0 && f[m][i-j]<0)
			{
                  j++ ;
            }
            if (f[m][i+j]>f[m][i-j])
			{
                  k=i+j ;
            }
            else
			{
                  k=i-j ;
            }

            printf("Jury #%d\n",tcase) ;
            printf("Best jury has value %d for prosecution and value %d for defence:\n",
                   (k-p_d+f[m][k])/2,(f[m][k]-k+p_d)/2) ;
            for (i=1 ; i<=m ; i++)
			{
                  ans[i] = path[m-i+1][k] ;
                  k -= p[ans[i]] - d[ans[i]] ;
            }

            sort (ans+1,ans+m+1) ;

            for (i=1 ; i<=m ; i++){
                  printf(" %d",ans[i]) ;
            }
            printf("\n\n") ;
            scanf("%d%d",&n,&m) ;
      }

    return 0;
}
//*/


/*    336K	110MS	C++	2672B

#include <cstdio>
 #include <cstring>
 #include <vector>
 #include <algorithm>
  using namespace std;
 
 #define maxn 220
 #define offset 25*20
 pair <int , int> cdd[maxn];
 int dp[22][400+offset];
 int par[22][400+offset];
 vector <int> order;
 
 int cmp(int a,int b){return a>b;}

 //candidate[a] exists in i men
 int notused(int a , int i, int p){
     while(par[i][p] != -1)
     {
         if( par[i][p] == a)return 0;
         p  = p - cdd[par[i][p]].first + cdd[par[i][p]].second;
         i--;
     }
     return 1;
 }
 
 int main(){
     int i, j , k , p ,n , m ,ncase=0;
     while( scanf("%d %d",&n,&m) != EOF && m)
     {
         memset(dp , -1 , sizeof(dp));
         memset(par , 0 , sizeof(par));
         dp[0][offset] = 0;
         par[0][offset] = -1;
         for(i=0 ; i<n ; i++)
             scanf("%d %d",&cdd[i].first,&cdd[i].second);
 
         //        dp[j][p] = max( dp[j-1][p+first[i]-second[i]] + first[i] + second[i])  
         for(i=1 ; i<=m ; i++)
         {    // 01 
             for(p=0 ; p<400+offset ; p++)
             {
                 if( dp[i-1][p] != -1)
                 {
                     for(j=0 ; j<n ; j++)
                     {
                         if(notused(j,i-1,p) && dp[i-1][p]+cdd[j].first+cdd[j].second > dp[i][p+cdd[j].first-cdd[j].second])
                         {
                             dp[i][ p+cdd[j].first-cdd[j].second ] = dp[i-1][p]+cdd[j].first+cdd[j].second;
                             par[i][ p + cdd[j].first - cdd[j].second ] = j;
                         }
                     }
                 }//if
             }
         }// for(i)
 
         for( k=0 ; k<=20*m ; k++)
         {
             if(dp[m][offset+k]!=-1 || dp[m][offset-k]!=-1 )
                 break;
         }
         if( dp[m][offset-k] > dp[m][offset+k]) k = -k;
 
         p = offset+k; i=m;
         order.clear();
         while(par[i][p] != -1)
         {
             order.push_back(par[i][p]);
             p = p -  cdd[par[i][p]].first + cdd[par[i][p]].second;
             i--;
         }
         pair <int,int> count=make_pair(0,0);
         for(i=0 ; i<order.size() ; i++)
         {
             count.first += cdd[order[i]].first;
             count.second += cdd[order[i]].second;
         }
         printf("Jury #%d\nBest jury has value %d for prosecution and value %d for defence:\n",++ncase , count.first,count.second);
         sort(order.begin(),order.end(),cmp);
         for(i=order.size()-1 ; i>=0 ; i--)printf(" %d",order[i]+1);
         printf("\n\n");
         
     }
     return 0;
 }
//*/




 /*                         492K	79MS	C++	1706B	
 #include <iostream>
using namespace std;
int main()
{
    long i,j,k,l,n,m,t1,maxf,count;
    long p[210],d[210],f[210],s[210];
    long can[30];
    long res[30][1000],from[30][1000];
    
    count=0;
    cin>>n>>m;
    while(n!=0 || m!=0)
    {
        count++;
        
        for(i=0;i<n;i++)
        {
            cin>>p[i]>>d[i];
            f[i]=p[i]-d[i];
            s[i]=p[i]+d[i];
        }
        maxf=20*m;
        
        for(i=0;i<=m;i++)
			for(j=0;j<=maxf*2;j++)
				res[i][j]=-1;

			res[0][maxf]=0;
			from[0][maxf]=-1;
			
			for(i=0;i<m;i++)
				for(j=0;j<=maxf*2;j++)
					if(res[i][j]!=-1)
					{
						for(k=0;k<n;k++)
						{
							t1=j;
							for(l=i;l>0;l--)
							{
								if(from[l][t1]==k) break;
								t1-=f[from[l][t1]];
							}
							if(l!=0) continue;
							
							t1=res[i][j]+s[k];
							if(res[i+1][j+f[k]]<t1)
							{
								res[i+1][j+f[k]]=t1;
								from[i+1][j+f[k]]=k;
							}
						}
					}
					
					for(i=0;i<=maxf;i++)
					{
						if(res[m][maxf+i]>res[m][maxf-i]) { t1=maxf+i; break;}
						if(res[m][maxf-i]!=-1) { t1=maxf-i; break;}
					}
					
					cout<<"Jury #"<<count<<endl;
					cout<<"Best jury has value "<<(res[m][t1]+t1-maxf)/2<<" for prosecution";
					cout<<" and value "<<(res[m][t1]-t1+maxf)/2<<" for defence:"<<endl;
					
					for(i=m;i>0;i--)
					{
						can[i]=from[i][t1];
						t1-=f[can[i]];
					}
					
					for(i=1;i<m;i++)
						for(j=i+1;j<=m;j++)
							if(can[i]>can[j]) swap(can[i],can[j]);
							
							for(i=1;i<=m;i++)
								cout<<" "<<can[i]+1;
							cout<<endl<<endl;
							
							cin>>n>>m;
    }
    return 0;
}

 //*/


 /*
 ����:���ڷ���Ҫ�ӹ����������ѡn������Ϊ�����ŵĺ�ѡ��,Ȼ���ٴ���n������ѡm�������������,ѡȡm�˵Ĺ�����:

      �ط��ͱ緽������Լ��Ժ�ѡ�˵�ϲ���̶�,�����еĺ�ѡ�˴��,��ֵ��0����20.��ôѡ����m����,��������緽�ֺܷͿط��ֵܷĲ�ľ���ֵ��С,

      ����ж���ѡ�񷽰��ı緽���ֺܷͿط��ֵܷĲ�ľ���ֵ��ͬ,��ôѡȡ�緽�ֺܷͿط��ܷ�֮�����ķ�������.

      �����к�ѡ�˵ı緽�ֺܷͿط��ܷ�֮���Ϊ"��ز�",�ܷ�֮�ͳ�Ϊ"��غ�",��i����ѡ�˵ı�ز��Ϊv[i],��غͼ�Ϊs[i].

	  ��f[i][j]��ʾ��ȡ��i����ѡ��,ʹ���ز�Ϊj�����з�����,��غ������Ǹ�����,��Ϊ����f(i,j)�ı�غ�,

	  ���û��ѡȡ��i����,ʹ���ز�Ϊj,��ôf[i][j]��ֵ��Ϊ-1,������f(i,j)������,
	  
	  ����Ҫ��ѡȡm����,��ô,��������е�j�Ŀ���ȡֵ��������е�f[m][j] (-20*m<=j<=20*m),��ô�����ŷ�����Ȼ�������ҵ���.

      ����f(i,j)����ĳ�����з���f(i-1,x) (-20*m<=x<=20*m)���ƶ�����,�����з���f(i-1,x)���Ƴ�����f(i,j)�ı�Ҫ������:
	  
	  ����ĳ����ѡ��k,����k�ڷ���f(i-1,x)��û�б�ѡ��,��x+v[k]=j.����������ñ�Ҫ������f(i-1,x)��ѡ��f(i-1,x)+s[k]��ֵ�����Ǹ�,
	  
	  ��ô����f(i-1,x)�ټ��Ϻ�ѡ��k���Ƴ��˷���f(i,j),���������,������path[i][j]����¼����f(i,j)�����ѡ���Ǹ���ѡ�˵ı��,���ȷ���˽������֮��,
	  
	  ��f[m][j]����,����������к�ѡ�˵ı��.

      ��ʼʱ����ȷ��f[0][0]=0,�ɴ˳���,�𲽵���,����������еĿ��з���f(m,j) (-20*m<=j<=20*m),
	  
	  ���������ز����Ϊ����,��Ϊf[m][j]�е�j��ŵ���ѡȡ��m����ѡ��ʱ�ı�ز�,�������±겻��Ϊ����,
	  
	  ���Կ��Խ���ز��ֵ������20*m����������f[i][j]���±���ָ���,����Ŀʵ�ʵı�ز�Ϊ0ʱ,��ô��Ӧ�任֮��ı�ز�Ϊtemp=20*m,
	  
	  ����Ȼ��ز��ȡֵ��Χ��[0,2*temp].

      ��������������ķ���f(m,j),f[m][j]��jΪѡȡm����ѡ�˵ı�ز�Ϊj(ע����ʱ�ı�ز��Ǳ任֮��ı�ز�,ʵ�ʵı�ز�Ϊ:j-temp),
	 
	  f[m][j]��ŵ��Ǳ�ز�Ϊj�ķ��������ı�غ�,��ô��:

      V-S=j-temp;
      V+S=f[m][j]
    �����Ƴ�:V=(f[m][j]+j-temp)/2       V=(f[m][j]-j+temp)/2
    ���ѡȡ����������ѡʱ��Ҫ������˳�����,��ô���Ƚ�������������ٽ������.


	//    396K	16MS	C++	2836B
#include<iostream>
#include<string>
#include<cstdlib>
#include<algorithm>
using namespace std;

int f[25][1000];                                                      //f[i][j]��ʾȡ��i����ѡ��,ʹ���ز�Ϊj�����з����б�غ������Ǹ�����
int path[25][1000];                                                //path[i][j]��ʾ����f(i,j)�����ѡȡ���Ǹ���ѡ�˵ı��
int result[25];                                                         //���ѡȡ�������ų�Ա
int p[205];
int d[205];

int cmp(const void * a,const void * b)
{
	return *(int *)a-*(int *)b;
}

int main()
{
	int i,j,x,y,k,m,n,temp,ncase=0;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		   if(n==0&&m==0)
				break;
		   for(i=1;i<=n;i++)
				scanf("%d%d",&p[i],&d[i]);

		   memset(f,-1,sizeof(f));
		   memset(path,0,sizeof(path));
		   temp=20*m;                                                         //��ʵ���б�ز�Ϊ0ʱ��Ӧ�ı任��ı�ز�(������20*m)
		   f[0][temp]=0;                                                      //��ʼʱf[0][0]=0,���Ӧ�任��f[0][temp]=0

		   for(i=0;i<m;i++)                                                   //ÿ��ѭ��ѡ����i����,��Ҫѡ��m��
			  for(j=0;j<=2*temp;j++)                                          //���ܵı�زΧʱ[0,2*temp](�任֮���)
				 if(f[i][j]>=0)                                               //����f(i,j)����
				 {
					for(k=1;k<=n;k++)                                         //�ڷ���f(i,j)�Ļ�����,ѡȡ��һ����ѡ��
					   if(f[i][j]+p[k]+d[k]>f[i+1][j+p[k]-d[k]]) //���������������,��˵����ԭ���Ѿ����˳����ķ���f(i+1,j+p[k]-d[k]),�����ķ����������������
					   {
							x=i;
							y=j;
							while(x>0&&path[x][y]!=k)                         //�жϵ�k�����Ƿ��Ѿ��ڷ���f(i,j)�б�ѡ����
							{
								 y-=p[path[x][y]]-d[path[x][y]];
								 x--;
							}
							if(x==0)                                           //��k�����ڷ���f(i,j)��û�б�ѡ��
							{
								 f[i+1][j+p[k]-d[k]]=f[i][j]+p[k]+d[k];        //��ô�ڷ���f(i,j)�Ļ�����,ѡȡ��k����,�γɷ���f(i+1,j+p[k]-d[k])
								 path[i+1][j+p[k]-d[k]]=k;                     //��¼�·���ѡȡ�ĳ�Ա
							}
					   }
				 }

		   i=temp;
		   k=0;
		   while(f[m][i+k]<0&&f[m][i-k]<0)                                      //�ҵ����еķ���f(i,j)                                                    
				k++;
		   if(f[m][i+k]>f[m][i-k])                                              //���շ����ж�Ӧ�ı�ز�Ϊj
				j=i+k;
		   else
				j=i-k;

		   printf("Jury #%d\n",++ncase);
		   printf("Best jury has value %d for prosecution and value %d for defence:\n",(f[m][j]+j-temp)/2,(f[m][j]-j+temp)/2);

		   for(i=1;i<=m;i++)                                                
		   {
				result[i] = path[m-i+1][j];
				j -= p[result[i]]-d[result[i]];
		   }

		   qsort(result+1,m,sizeof(result[1]),cmp);

		   for(i=1;i<=m;i++)
				printf("%d ",result[i]);

		   printf("\n\n");
	}
	//system("pause");
	return 0;
}
 //*/
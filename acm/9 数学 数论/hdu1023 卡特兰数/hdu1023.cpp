#include<iostream>
using namespace std;

#define MAX 105
#define BASE 10000

typedef int myType[MAX+10];

void multiply ( int a[], int Max, int b )  //大数乘小数
{
    int i,array=0;
    for (i=Max-1; i>=0; i--)   
    {
        array+=b*a[i];
        a[i] = array%BASE;
        array /= BASE;   
    }
}
 
void divide ( int a[], int Max, int b )  //大数除小数
{
    int i,div=0;
    for (i=0;i<Max; i++)   
    {
        div = div*BASE + a[i];
        a[i] = div / b;
        div %= b;
    }
}
void outPut ( myType ctl[MAX] ,int N )
{
     int i = 0;
     while ( i < MAX && ctl[N][i] == 0 )
     {
             i ++ ; //去前导0 
     }
     cout << ctl[N][i++];             
     while ( i < MAX )   
     {
             printf ( "%04d", ctl[N][i++] );   
     } 
     cout << endl; 
}
void setNum ( myType ctl[MAX] )
{
     memset ( ctl[1], 0, MAX * sizeof ( int ) );
     ctl[1][MAX-1] = 1;
     for ( int i = 2; i < 101; i ++ )
     {
         memcpy ( ctl[i], ctl[i-1], MAX * sizeof ( int ) );      
         multiply ( ctl[i], MAX, 4 * i - 2 );               
         divide ( ctl[i], MAX, i + 1 );                  
     } 
}


myType ctl[MAX];  // 相当于int[][]

int main()
{
    setNum ( ctl );
    int N; 
    while ( cin >> N )     // 这里根据各题要求需要做相应变化
    {
           outPut ( ctl, N ); 
    }
    return 0;
}




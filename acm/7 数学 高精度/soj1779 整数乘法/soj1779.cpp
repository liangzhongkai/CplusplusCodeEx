

/*
#include <stdio.h>
#include <string.h>
void mul( char *a, char *b, char *sum ) {
    int temp[2500];
    int i,j,la,lb,l;
    la=strlen(a);
    lb=strlen(b);

    for ( i=0;i<la+lb;i++ )
        temp[i]=0;
    for ( i=la-1;i>=0;i-- ) {
        l=la-1-i;
        for ( j=lb-1;j>=0;j-- ) {
            temp[l]=(b[j]-'0')*(a[i]-'0')+temp[l];
            l++;
        }
    }

    while ( temp[l]==0 )
        l--;
    for ( i=0;i<=l;i++ ) {
        temp[i+1]+=temp[i]/10;
        temp[i]=temp[i]%10;
    }
    if ( temp[l+1]!=0 )
        l++;
    
    while ( temp[l]/10!=0 ) {   
        temp[l+1]+=temp[l]/10;
        temp[l]=temp[l]%10;
        l++;
    }
    if ( temp[l]==0 )
        l--;
    i=0;
    while ( l>=0 ) {
        sum[i]=temp[l]+'0';
        i++;
        l--;
    }
    sum[i]='\0';
}

int main()
{
    char a[2500],b[2500],sum[2500];
    int t,n,i;
    scanf( "%d",&t );
    while ( t-- ) {
        scanf( "%s%s%d",&a,&b,&n );
        strcpy(sum,a);
        if ( a[0]=='1'&&b[0]=='1'&&a[1]=='\0'&&b[1]=='\0' )
            printf( "1\n" );
        else {
			if ( n==1 )
				printf( "%s\n",a );
			else if ( n==2 )
				printf( "%s\n", b );
			else {
				for (i=3;i<=n;i++) {    
					mul(a,b,sum);
					strcpy(a,b);
					strcpy(b,sum);
					if ( strlen(sum)>500 ) {
						printf( "Ooops!\n" );
						break;
					}
				}
				if ( strlen(sum)<500 )
					printf( "%s\n",sum );
			}
        }
    }
    return 0;
}
//*/


/*
// Problem#: 1779
// Submission#: 1261993
// The source code is licensed under Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
// URI: http://creativecommons.org/licenses/by-nc-sa/3.0/
// All Copyright reserved by Informatic Lab of Sun Yat-sen University
#include<iostream>
#include<cstring>

using namespace std;

char* mul( char *a, char *b) {
	char sum[2500] ;
    int temp[2500];
    int i,j,la,lb,l;
    la=strlen(a);
    lb=strlen(b);

    for ( i=0;i<la+lb;i++ )
        temp[i]=0;
    for ( i=la-1;i>=0;i-- ) {
        l=la-1-i;
        for ( j=lb-1;j>=0;j-- ) {
            temp[l]=(b[j]-'0')*(a[i]-'0')+temp[l];
            l++;
        }
    }

    while ( temp[l]==0 )
        l--;
    for ( i=0;i<=l;i++ ) {
        temp[i+1]+=temp[i]/10;
        temp[i]=temp[i]%10;
    }
    if ( temp[l+1]!=0 )
        l++;
    
    while ( temp[l]/10!=0 ) {   
        temp[l+1]+=temp[l]/10;
        temp[l]=temp[l]%10;
        l++;
    }
    if ( temp[l]==0 )
        l--;
    i=0;
    while ( l>=0 ) {
        sum[i]=temp[l]+'0';
        i++;
        l--;
    }
    sum[i]='\0';

	return sum;
}
char sum1[500], sum2[700];
char tmp[2500];

int main()
{
    int tc;
    int n;
    
    cin >> tc;

    while(tc--){
        cin >> sum1 >> sum2;
        cin >> n;
        if(n==1)
        {
            cout << sum1 <<endl;
            continue;
        }
        if(n==2){
            cout << sum2 << endl;
            continue;
        }
        n = n - 2;
       
        int key = 0;
        while(n--){
            tmp = mul(sum1, sum2);
            if(strlen(tmp)>1000){
                key = 1;
                break;
            }
            //cout << sum1 << "    " << sum2 << endl;
            strcpy(sum1, sum2);
            strcpy(sum2, tmp);
            //*sum1 = *sum2;
            //*sum2 = *tmp;
        }
        if(key==1){
            cout << "Ooops!" << endl;
        }
        else{
            cout << sum2 << endl;
        }
        
    }

    return 0;
}                                 
//*/
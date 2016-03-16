//  750MS 	500K 	1289B 	KCT
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
    while ( scanf( "%s%s",&a,&b )!=EOF ) {
        strcpy(sum,a);
        if ( (a[0]=='0' && a[1]=='\0') || (b[0]=='0' && b[1]=='\0') )
            printf("0\n");
        else {
			if ( a[0]=='1' && a[1]=='\0')
				printf( "%s\n", b);
			if( b[0]=='1' && b[1]=='\0' )
				printf("%s\n", a);
			else{   
				mul(a,b,sum);
				printf("%s\n", sum);
			}
		}
    }
    return 0;
}

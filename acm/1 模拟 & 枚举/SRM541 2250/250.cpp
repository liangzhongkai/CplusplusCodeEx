#include <string>
using namespace std;

class AkariDaisukiDiv2{public:
int countTuples( string S )
{
    int n = (int)S.size();
    int c = 0;
    for ( int i=1;   i<n; i++ )
    for ( int j=i+1; j<n; j++ )
    for ( int k=j+1; k<n; k++ )
    for ( int l=k+1; l<n; l++ )
        if ( S.substr(i,j-i)==S.substr(k,l-k) )
            c++;
    return c;
}};

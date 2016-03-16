/*
1 2 52
1 2 53
2 3 55
3 6 124
3 6 258

5
4
1
5
1
*/
/*   0MS	216K	782 B	C++
#include<stdio.h>

int main()
{
    int A, B, n, z = 1;
    int f[54] = {0, 1, 1};
    //取54是因为第0位不使用，第1,2位固定为1，加49最大周期
	//    及最后判断周期所用2位，最大共需用54位。
    while(scanf("%d%d%d", &A, &B, &n) != EOF){
        if(A == 0 && B == 0 && n == 0)
            break;
        for(int i = 3; i < 54; ++i){
            f[i] = (A * f[i - 1] + B * f[i - 2]) % 7;
            //printf("%d ", f[i]);
            if(i > 5){
                if(f[i - 1] == f[3] && f[i] == f[4]){
                    z = i - 4;
                    break;
                }
            }
        }
        //printf("\n%d\n", z);
        if(n > 2)
            printf("%d\n", f[(n - 3) % z + 3]);
        else
            printf("1\n");
    }
    return 0;
}
//*/

//*
#include<stdio.h>
int main()
{
    int A, B, n, i, z = 1;
    int f[55] = {0,1,1};
    while(scanf("%d%d%d", &A, &B, &n) != EOF){
        if(A == 0 && B == 0 && n == 0)
            break;
        for(i = 3; i < 60; ++i){
            f[i] = (A * f[i - 1] + B * f[i - 2]) % 7;
			if(i>5){
				if(f[i] == f[4] && f[i-1] == f[3]){
					z = i - 4;
					break;
				}
			}
        }
        if(n > 2)
            printf("%d\n", f[(n - 3) % z + 3]);
        else
            printf("1\n");
    }
    return 0;
}
//*/
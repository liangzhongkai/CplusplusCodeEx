//    256K  	0MS  	C++ 	3072B

#include <iostream>
#include<string>

using namespace std;

int main()
{   
    int n,i,j,flag,g,k,b[6],pos,spos,sum[200],key,temp1[200];    //temp1[200]=累计结果、sum[200]装乘积结果后归零、key为进位、spos为乘积结果长度
    char a[7];
    memset(a,0x00,sizeof(a));

    while(cin>>a>>n)        //scanf("%s %d",a,&n)!=EOF
    {
		// 乘积数组、 累计数组
        for(i=0;i<200;i++)
		{
			sum[i]=0;
			temp1[i]=0;
		}
        j=0;
        flag=5;

        for(i=5;i>=0;i--)
        {
            if(a[i]=='.') flag=i;
            else 
            {
                b[j] = a[i] - '0';         //转变为数字b[0]为低位，b[5]为高位。
                temp1[j++] = b[j] ;       // temp1一样！
                //j++;
            }
        }
		
        pos=0;
        spos=5;

		//下面temp1在循环保持原结果的！
        for(k=1;k<n;k++)                         //计算 n 次方数
        {
			// 相乘
            for(i=0;i<5;i++)                     //它这里无视前面的0位，把它照乘下去，b[]代表5位数
            {
                for(j=0;j<spos;j++)
                {                                //用原先的5位数b[i]去乘以temp1[0~spos]
                    sum[i+j]+=(temp1[j]*b[i]);   //为什么要累加！因为它们本身就是0 （从sum[0]~sum[200]都是！）
                } //这个sum[i+j]的形式妙极了！！
            }

			// 处理进位
            key=sum[0]/10;            //key 是进位，因为sum[0]可能是两位数
            sum[0]%=10;               //sum[0] 变为个位数
            for(i=1;i<spos+4;i++)       //这个就是我之前想法的实现，，但是我自己写不出，容器运用得不熟练
            {                           //得到一个 9 位数。这里的有8位，加上上面的sum[0]
                sum[i]+=key;     
                key=sum[i]/10;          //其实这个也是刘汝佳的阶乘算法
                sum[i]%=10;
            }

            // 处理最高进位
            sum[i]=key%10;              //现在的key为第十位的进位
            if(sum[i]!=0)   pos++;     //pos是什么含义？  可能同相乘结果的位数有关！！！
            //i++;

			/*   可有可无
            while((key/10)>0)          //如果第十位的进位是十位数的话，就会操作下面的步骤
            {
                key/=10;
                sum[i]=key%10;
                pos++;
                i++;
            }
			*/

            spos=spos + 4 + pos;                 //  5 + 4 + 1/0
            for(i=0;i<spos;i++)              //sum[]传值给temp1[]
			{	 
				temp1[i]=sum[i];
				sum[i]=0;                    //赋值后随后变翻做 0 。
			}
        }
        

        // 提取从后面开始第j位不等于 0 ；从前面开始第g位不等于 0 ！
        for(j=199;j>=(5-flag)*n;j--)
        {
            if(temp1[j]==0)  continue;
            else
                break;
        }
        for(g=0;g<=(5-flag)*n-1;g++)
        {
            if(temp1[g]==0)  continue;
            else
                break;
        }       
		
         
		//打印分成 3 部分     （5-flag）*n是一个分界点！！
        for(i=j;i>=(5-flag)*n;i--) 
        {
            cout<<temp1[i];                             //printf("%d",temp1[i]);
        }
        if(g<(5-flag)*n)  cout<<".";                    //printf(".");
        for(i=(5-flag)*n-1;i>=g;i--)
			cout<<temp1[i];                             //printf("%d",temp1[i]);

		cout<<endl;                                     //printf("\n");                
    }
    return 0;
}
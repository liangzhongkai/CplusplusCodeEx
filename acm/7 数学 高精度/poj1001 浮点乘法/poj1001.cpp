//    256K  	0MS  	C++ 	3072B

#include <iostream>
#include<string>

using namespace std;

int main()
{   
    int n,i,j,flag,g,k,b[6],pos,spos,sum[200],key,temp1[200];    //temp1[200]=�ۼƽ����sum[200]װ�˻��������㡢keyΪ��λ��sposΪ�˻��������
    char a[7];
    memset(a,0x00,sizeof(a));

    while(cin>>a>>n)        //scanf("%s %d",a,&n)!=EOF
    {
		// �˻����顢 �ۼ�����
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
                b[j] = a[i] - '0';         //ת��Ϊ����b[0]Ϊ��λ��b[5]Ϊ��λ��
                temp1[j++] = b[j] ;       // temp1һ����
                //j++;
            }
        }
		
        pos=0;
        spos=5;

		//����temp1��ѭ������ԭ����ģ�
        for(k=1;k<n;k++)                         //���� n �η���
        {
			// ���
            for(i=0;i<5;i++)                     //����������ǰ���0λ�������ճ���ȥ��b[]����5λ��
            {
                for(j=0;j<spos;j++)
                {                                //��ԭ�ȵ�5λ��b[i]ȥ����temp1[0~spos]
                    sum[i+j]+=(temp1[j]*b[i]);   //ΪʲôҪ�ۼӣ���Ϊ���Ǳ������0 ����sum[0]~sum[200]���ǣ���
                } //���sum[i+j]����ʽ��ˣ���
            }

			// �����λ
            key=sum[0]/10;            //key �ǽ�λ����Ϊsum[0]��������λ��
            sum[0]%=10;               //sum[0] ��Ϊ��λ��
            for(i=1;i<spos+4;i++)       //���������֮ǰ�뷨��ʵ�֣����������Լ�д�������������õò�����
            {                           //�õ�һ�� 9 λ�����������8λ�����������sum[0]
                sum[i]+=key;     
                key=sum[i]/10;          //��ʵ���Ҳ������ѵĽ׳��㷨
                sum[i]%=10;
            }

            // ������߽�λ
            sum[i]=key%10;              //���ڵ�keyΪ��ʮλ�Ľ�λ
            if(sum[i]!=0)   pos++;     //pos��ʲô���壿  ����ͬ��˽����λ���йأ�����
            //i++;

			/*   ���п���
            while((key/10)>0)          //�����ʮλ�Ľ�λ��ʮλ���Ļ����ͻ��������Ĳ���
            {
                key/=10;
                sum[i]=key%10;
                pos++;
                i++;
            }
			*/

            spos=spos + 4 + pos;                 //  5 + 4 + 1/0
            for(i=0;i<spos;i++)              //sum[]��ֵ��temp1[]
			{	 
				temp1[i]=sum[i];
				sum[i]=0;                    //��ֵ�����䷭�� 0 ��
			}
        }
        

        // ��ȡ�Ӻ��濪ʼ��jλ������ 0 ����ǰ�濪ʼ��gλ������ 0 ��
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
		
         
		//��ӡ�ֳ� 3 ����     ��5-flag��*n��һ���ֽ�㣡��
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
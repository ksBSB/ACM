#include<iostream>
#include<string.h>
#include<math.h>
using namespace std;
#define N 10000

int sum;				//记录和像素。
char *move;				//遍历字符串求像素时的辅助指针。

void build(int n);		//通过递归求解。

int cut(char *t,int f)	//需要多个字符拷贝或抛弃时，计算个数，返回值为移动后的下标，与原先坐标相减即为个数。
{
    for(int i=0; i<4; i++)
    {
        f++;
        if(t[f]=='e'||t[f]=='f')
            continue;
        else if(t[f]=='p')
            f=cut(t,f);
    }
    return f;
}

int main()
{
	char str1[N],str2[N],tem[N];
	int n;
	cin>>n;
	while(n--)
	{
		//Init.
		memset(str1,0,sizeof(str1));
		memset(str2,0,sizeof(str2));
		memset(tem,0,sizeof(tem));

		cin>>str1>>str2;

		//Count.
		int num1=0,num2=0,num_t=0;
		while(1)
		{
			if(str1[num1]=='\0'&&str2[num2]=='\0')	break;		//两个字符串均遍历过后跳出循环。
			
			if(str1[num1]=='p'&&str2[num2]=='p')			
			{
				num1++;
				num2++;
				tem[num_t++]='p';
			}
			else if(str1[num1]=='p'&&str2[num2]=='f')
			{
				num1=cut(str1,num1)+1;
				num2++;
				tem[num_t++]='f';
			}
			else if(str1[num1]=='f'&&str2[num2]=='p')
			{
				num1++;
				num2=cut(str2,num2)+1;
				tem[num_t++]='f';
			}
			else if(str1[num1]=='p'&&str2[num2]=='e')
			{
				int k=cut(str1,num1)+1-num1;
				strncpy(tem+num_t,str1+num1,k);
				num1+=k;
				num2++;
				num_t+=k;
			}
			else if(str1[num1]=='e'&&str2[num2]=='p')
			{
				int k=cut(str2,num2)+1-num2;
				strncpy(tem+num_t,str2+num2,k);
				num1++;
				num2+=k;
				num_t+=k;
			}
			else if(str1[num1]=='e'&&str2[num2]=='f')
			{
				num1++;
				num2++;
				tem[num_t++]='f';
			}
			else if(str1[num1]=='f'&&str2[num2]=='e')
			{
				num1++;
				num2++;
				tem[num_t++]='f';
			}
			else if(str1[num1]=='f'&&str2[num2]=='f')
			{
				num1++;
				num2++;
				tem[num_t++]='f';
			}
			else if(str1[num1]=='e'&&str2[num2]=='e')
			{
				num1++;
				num2++;
				tem[num_t++]='e';
			}
			else if(str1[num1]=='\0')				//当有一个字符串先遍历完，另一串剩余字符可直接拷贝。
			{
				while(str2[num2]!='\0')
					tem[num_t++]=str2[num2++];
			
			}
			else if(str2[num2]=='\0')
			{
				while(str1[num1]!='\0')
					tem[num_t++]=str1[num1++];
			}
		
		}
	
		move=tem;						//move指针指向和字符串首部，定义成全局变量移动指针进行遍历。
		sum=0;
		build(0);
		cout<<"There are "<<sum<<" black pixels."<<endl;
	}
return 0;}

void build(int n)			//n为记录当前层数，用于计算像素值。
{
	int i;

	for(i = 0;i < 4; i++)
	{
		if(*move=='p')
		{	move++;
			build(n+1);
		}
		else if(*move=='f')
		{	sum+=pow(4,5-n);		//该点的像素值为4的5-n次方。
			move++;
		}
		else
			move++;
	}
}

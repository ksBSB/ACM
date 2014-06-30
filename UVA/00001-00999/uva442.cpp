#include<iostream>
#include<string.h>
using namespace std;

#define N 10000
#define M 30

struct sq{
	int l;
	int w;
}re[M];

//变量。
char name[M];				
int cnt;
int bo;
char *move;
int n;

//函数声明。
sq count();				
sq find(char c);		//根据矩阵名找到矩阵；

int main()
{
	char str[N];

	while(cin>>n)
	{	//Init.
		memset(name,0,sizeof(name));

		//Read sq.
		for(int i = 0;i < n; i++)
			cin>>name[i]>>re[i].l>>re[i].w;

		//Read and count.
		while(cin>>str)
		{
			str[strlen(str)+1]='\0';
			move=str;
			cnt=0;
			bo=1;

			count();

			if(bo)
				cout<<cnt<<endl;
			else
				cout<<"error"<<endl;
	
			memset(str,0,sizeof(str));
		}

		
	}
	return 0;}

sq count()
{
	sq dis[2];					//记录当前计算域中的矩阵。
	sq now;
	int t=0;					//记录总数。

	now.l=now.w=0;				

	while(1)
	{	
		if(*move=='\0')	
			break;
		else if('(' == *move)
		{
			move++;
			dis[t++]=count();
			if(!bo)	return now;
		}
		else if(')' == *move)
		{
			move++;
			break;
		}
		else
		{	
			dis[t++]=find(*move);
			move++;
			if(!bo)	return now;
		}
	}
	
	if(t==2)
	{	
		if(dis[0].w!=dis[1].l)	
		{
			bo=0;
			return now;
		}

		cnt=cnt+dis[0].l*dis[0].w*dis[1].w;
	}
	else if(t == 1)	return now;

	now.l=dis[0].l;
	now.w=dis[t-1].w;					//无论表达式如何计算，所得矩阵不变。
	return now;
}

sq find(char c)
{
	for(int i = 0;i < n; i++)
		if(c == name[i])	
			return re[i];

	bo=0;
	sq now;
	now.l=now.w=0;
	return now;
}

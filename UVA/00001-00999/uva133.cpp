#include<stdio.h>
#include<iostream>
using namespace std;
#define N 25

int num[N];

int main()
{
	int n,lift,right;
	int i;
	while(cin>>n>>lift>>right,n||lift||right)
	{
		//Init.
		int cnt=n;
		int now_lift=1,now_right=n;	
		for(i = 1;i <= n; i++)
			num[i]=1;

		while(1)
		{
			//move lift.
			for(i=0;;now_lift++)
			{	
				if(now_lift==n+1)	now_lift=1;
				if(num[now_lift])
				{	i++;
					if(i==lift)	
						break;
				}
			}

			//move right.
			for(i=0;;now_right--)
			{	
				if(now_right==0)	now_right=n;
				if(num[now_right])
				{	i++;
					if(i==right)
						break;
				}
			}

			if(now_lift!=now_right)
			{
				printf("%3d%3d",now_lift,now_right);
				num[now_lift]=0;
				num[now_right]=0;
				cnt-=2;
			}
			else if(now_lift==now_right)
			{	printf("%3d",now_right);
				num[now_lift]=0;
				cnt--;
			}

			if(cnt)
				cout<<",";
			else
				break;
		}
		cout<<endl;
	}
return 0;}

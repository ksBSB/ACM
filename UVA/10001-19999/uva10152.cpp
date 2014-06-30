#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
#define N 1000
#define M 500

char str[N][M];
char tem[N][M];
int bo[N];

int main()
{
	int i;
	int n;	cin>>n;
	while(n--)
	{
		//Init.
		memset(str,0,sizeof(str));
		memset(tem,0,sizeof(tem));
		memset(bo,0,sizeof(bo));

		int m;	cin>>m;
		getchar();
		for(i = 0;i < m; i++)
			gets(str[i]);

		for(i = 0;i < m; i++)
			gets(tem[i]);
		
		int s=m-1;
		int t=m-1;

		while(1)
		{
			if(strcmp(tem[t],str[s])==0)
			{
				bo[t]=1;
				t--;
				s--;
			}
			else
				s--;
			if(s==-1)	break;
		}

		for(;t>=0;t--)
			cout<<tem[t]<<endl;
		cout<<endl;
	}
	return 0;}

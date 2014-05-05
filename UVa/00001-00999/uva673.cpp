#include<string.h>
#include<stack>
#include<cstdio>
using namespace std;

#define N 200

int main()
{
	int n;

	char str[N];
	int bo;

	scanf("%d", &n);
	getchar();

	while(n--)
	{
		// Init.
		memset(str, 0, sizeof(str));
		bo = 1;
		stack<char> q;

		// Read.
		gets(str);
		int m = strlen(str);
		for(int i = 0; i < m ; i++)
		{
			if(str[i] == '(' || str[i] == '[')
				q.push(str[i]);
			else if(str[i] == ')')
			{
				if(q.empty() || q.top() != '(')
				{
					bo = 0;
					break;
				}
				else
					q.pop();
			}
			else if(str[i] == ']')
			{
				if(q.empty() || q.top() != '[')
				{
					bo = 0;
					break;
				}
				else
					q.pop();
			}
		}

		if(bo && q.empty())
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;}

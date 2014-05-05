#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;

#define N 105

int main(){

	int n;
	char str[N], tem[5][N];
	cin >> n;
	getchar();

	while (n--)
	{
		// Init.
		memset(str, 0, sizeof(str));
		memset(tem, 0, sizeof(tem));

		// Read.
		gets(str);

		// Change.
		int k = strlen(str);
		int cnt = 0, t = 0;
		for (int i = 0; i < k; i++)
		{
			if (str[i] == '<')
			{ 
				tem[cnt][t] = '\0';
				t = 0;
				cnt++;
			}
			else if (str[i] =='>')
			{
				tem[cnt][t] = '\0';
				t = 0;
				cnt++;
			}
			else
				tem[cnt][t++] = str[i];
		}

		gets(str);

		cout << tem[0] << tem[1] << tem[2] << tem[3] << tem[4] << endl;

		for (int i = 0; str[i] != '\0'; i++)
			if (str[i] =='.')
				break;
			else
				putchar(str[i]);

		cout << tem[3] << tem[2] << tem[1] << tem[4] << endl;

	}
	return 0;}

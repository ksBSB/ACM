#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
#define N 15
#define M 85
#define K 260

int main()
{
	char before[N][M], after[N][M];
	char str[K], tem[K];
	int n;

	while (cin >> n, n)
	{
		getchar();
		// Init.
		memset(before, 0, sizeof(before));
		memset(after, 0, sizeof(after));
		memset(str, 0, sizeof(str));

		// Read.
		for (int i = 0; i < n; i++)
		{
			gets(before[i]);
			gets(after[i]);
		}
		gets(str);

		// Judge.
		for (int i = 0; i < n; i++)
		{
			int t = strlen(before[i]);
			int k = strlen(after[i]);
			do{
				char *move = NULL;
				move = strstr(str, before[i]);

				if (move == NULL)
					break;
			
				strcpy(tem, move + t);	
				strcpy(move, after[i]);
				strcpy(move + k, tem);
			}while (1);
		}

		puts(str);
	}
	return 0;
}

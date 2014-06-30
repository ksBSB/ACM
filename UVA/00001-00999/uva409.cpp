#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

#define N 111

char str[N][N];
char tem[N][N];
char pop[N][N];
int num[N];

void strdx(char f[])
{
	int k = strlen(f);
	for (int i = 0; i < k; i++)
		if (f[i] >= 'A' && f[i] <= 'Z')
			f[i] +=32;
}

int main()
{
	int n, m;
	int t = 1;

	while (cin >> n >> m)
	{
		getchar();
		// Init.
		memset(str, 0, sizeof(str));
		memset(tem, 0, sizeof(tem));
		memset(num, 0, sizeof(num));
		memset(pop, 0, sizeof(pop));

		// Read.
		for (int i = 0; i < n; i++)
		{
			gets(str[i]);
			strdx(str[i]);
		}
		for (int i = 0; i < m; i++)
		{
			gets(tem[i]);
			strcpy(pop[i], tem[i]);
			strdx(pop[i]);
		}

		// Count.
		for (int i = 0; i < m; i++)
		{
			char *move = NULL;
			for (int j = 0; j < n; j++)
			{
				move = strstr(pop[i], str[j]);
				if (move == NULL)
					continue;
				int k = strlen(str[j]);

				if (*(move + k) >= 'a' && *(move + k) <= 'z')
					continue;
			
				num[i]++;
			}
		}

		int max = 0;
		for (int i = 0; i < m; i++)
			if (num[i] > max)
				max = num[i];

		cout << "Excuse Set #" << t++ << endl;

		for (int i = 0; i < m; i++)
			if (max == num[i])
				puts(tem[i]);
		cout << endl;
	}
	return 0;
}

#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<iostream>
using namespace std;

#define N 110
#define M 70

struct name{
	char str[M];
};
int len;

int cmp(const name &a, const name &b)
{
	if(strcmp(a.str, b.str) > 0)
		return 0;
	else 
		return 1;
}

int main()
{
	int n;
	int t;

	while (cin >> n)
	{
		// Init.
		len = 0;
		name s[N];
		
		// Read.
		for (int i = 0; i < n; ++i)
		{
			scanf("%s", s[i].str);		
			t = strlen(s[i].str);
			if (len < t)
				len = t;
		}
		len += 2;
		// Count.
		t = 62 / len;
		int f = n / t;
		if ( n % t)
			f++;
		sort(s,s + n,cmp);

		printf("------------------------------------------------------------\n");
		for (int i = 0; i < f; ++i)
		{
			for (int j = 0; j < t; ++j)
			{
				if (i + j * f < n)
					printf("%-*s", len, s[i + j * f].str);
			}
			printf("\n");
		}
	}
	return 0;
}

#include<stdio.h>
#define N 12
int find(int k)
{
	switch(k)
	{
		case 1:
			return 128;
		case 2:
			return 64;
		case 3:
			return 32;
		case 4:
			return 16;
		case 5:
			return 8;
		case 7:
			return 4;
		case 8:
			return 2;
		case 9:
			return 1;
		default:
			return 0;
	}
}

int main()
{
	char str[N];

	while (gets(str) != NULL)
	{
		if (str[0] != '|')
			continue;

		int sum = 0;
		for (int i = 1; i < N; i++)
			if (str[i] == 'o')
				sum +=find(i);

		putchar(sum);
	}
	return 0;
}

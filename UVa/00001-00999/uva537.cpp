#include<stdio.h>
#include<string.h>

#define N 305

char str[N];
int m;

double find(int k)
{
	double sum = 0;
	int i;
	int cnt = -1;
	for (i = k + 1; str[i] >='0' && str[i] <= '9' || str[i] == '.'; i++)
	{
		if (str[i] == '.')
			cnt = 0;
		else
		{
			sum = sum * 10 + str[i] - '0';
			if (cnt >= 0)
				cnt++;
		}
	}

	for (int j = 0; j < cnt; j++)
		sum *= 0.1;

	if (str[i] == 'm')
		sum *= 0.001;
	else if (str[i] == 'k')
		sum *= 1000;
	else if (str[i] == 'M')
		sum *= 1000000;

	return sum;
}

int main()
{
	int n;
	double P, U, I;

	scanf("%d", &n);
	getchar();

	for (int t = 1; t <= n; t++)
	{
		// Init.
		memset(str, 0, sizeof(str));
		P = 0;
		U = 0;
		I = 0;

		// Read.
		gets(str);

		// Find.
		m = strlen(str);
		char *move = str;
		for (int i =0; i < m; i++)
		{
			if (str[i] == '=')
				if (str[i - 1] == 'U')
					U = find(i);
				else if (str[i - 1] == 'I')
					I = find(i);
				else if (str[i - 1] == 'P')
					P = find(i);
		}

		// Print.
		if (P == 0)
			printf("Problem #%d\nP=%.2fW\n\n", t, I * U);
		else if (I == 0)
			printf("Problem #%d\nI=%.2fA\n\n", t, P / U);
		else 
			printf("Problem #%d\nU=%.2fV\n\n", t, P / I);
	}
	return 0;
}

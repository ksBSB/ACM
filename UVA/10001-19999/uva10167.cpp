#include<stdio.h>
#include<string.h>
#define N 105

int x[N], y[N];
int n;

void find()
{
	int p, q;

	for(int a = -500; a <= 500 ; a++)
	{
		for(int b = -500; b <= 500; b++)
		{	p = 0;
			q = 0;

			for(int i = 0; i < 2 * n; i++)
			{
				int k = x[i] * a + y[i] * b;

				if(k > 0)		p++;
				else if(k < 0)	q++;
				else		break;

				if(p > n) break;
				if(q > n) break;
			
				if(i == 2 * n - 1 && p == q)	
				{
					printf("%d %d\n", a, b);
					return;
				}
			}
		}
	}
}

int main( )
{
	while(scanf("%d", &n), n)
	{
		// Init.
		memset(x, 0, sizeof(x));
		memset(y, 0, sizeof(y));

		// Read.	
		for(int i = 0; i < 2 * n; i++)
			scanf("%d%d", &x[i], &y[i]);

		find();
	}
	return 0;}

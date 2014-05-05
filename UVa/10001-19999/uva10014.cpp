#include<stdio.h>
#include<string.h>
#define N 3005
double a0, an, c[N], a1;
int n;

int main(){
	int t;
	scanf("%d", &t);
	while (t--){
		// Init.
		memset(c, 0, sizeof(c));

		// Read.
		scanf("%d", &n);
		scanf("%lf%lf", &a0, &an);
		for (int i = 1; i <= n; i++)
			scanf("%lf", &c[i]);

		double sum = 0;
		for (int i = 1; i <= n; i++)
			sum = sum + (n + 1 - i) * c[i];
		a1 = (an + n * a0 - 2 * sum) / (n + 1);
		printf("%.2lf\n", a1);
		if (t)
			printf("\n");
	}
	return 0;}

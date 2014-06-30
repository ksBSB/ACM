#include <stdio.h>
#include <string.h>
#include <math.h>
const double INF = ((1<<31)-1);
const double eps = 1e-6;
const int N = 205;

int n, m;
double p, q;

void init () {
	int sum, cnt, a, v[N];
	sum = cnt = 0;
	memset(v, 0, sizeof(v));

	for (int i = 0; i < n; i++) {
		scanf("%d", &a);
		sum += a;
	}

	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d", &a);
		if (v[a]) continue;
		v[a] = 1;
		cnt++;
	}

	p = sum * 1.0 / n;
	q = cnt * 1.0 / n;
}

int main () {
	while (scanf("%d", &n) == 1) {
		init ();
		if (fabs(q - 1) < eps) {
			if (fabs(p) > eps)
				printf("inf\n");	
			else
				printf("0.00\n");
		} else
			printf("%.2lf\n", p/(1-q));
	}
	return 0;
}

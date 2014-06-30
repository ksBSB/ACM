#include <stdio.h>
#include <stdlib.h>
#include <math.h>
const int N = 1000005;

double q[N];
int cnt[N];

void init() {
	double p = 1, ans = 1;
	q[0] = 1;
	cnt[0] = 0;

	for (long long i = 1; i < N; i++) {
		p = 1./(i * i + i);
		q[i] = (1 - p) * q[i - 1];
		ans *= p;
		cnt[i] = cnt[i - 1];
		while (floor(ans) < 1e-10) {
			cnt[i]++;
			ans *= 10;
		}
	}
}

int main () {
	int n;
	init();
	while (scanf("%d", &n) == 1) {
		printf("%.6lf %d\n", 1 - q[n], cnt[n] - 1);
	}
	return 0;
}

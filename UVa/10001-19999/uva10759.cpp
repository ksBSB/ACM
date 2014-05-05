#include <stdio.h>
#include <string.h>

int n, x;
long long num[30][160], sum[30];

void init() {
	memset(num, 0, sizeof(num));
	for (int i = 1; i <= 6; i++) num[1][i] = 1;

	sum[0] = 1;
	for (int i = 1; i <= 24; i++) {
		sum[i] = sum[i - 1] * 6;
		for (int j = 1; j <= 150; j++) {
			for (int k = 1; k <= 6; k++)
				num[i + 1][j + k] += num[i][j];
			num[i][j] += num[i][j - 1];
		}
	}
}

long long  gcd(long long a, long long b) {
	return b == 0 ? a : gcd (b, a % b);
}

int main () {
	init();
	long long a, b, d;
	while (scanf("%d%d", &n, &x), n || x) {
		x--;
		if (sum[n] == num[n][x]) printf("0\n");
		else {
			d = gcd(sum[n] - num[n][x], sum[n]);
			a = (sum[n] - num[n][x]) / d;
			b = sum[n] / d;

			if (b == 1) printf("1\n");
			else 
				printf("%lld/%lld\n", a, b);
		}
	}
	return 0;
}

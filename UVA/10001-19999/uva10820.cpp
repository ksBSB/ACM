#include <stdio.h>
#include <string.h>
const int N = 50001;

int n, phi[N + 10], sum[N + 10];

void init() {
	memset(phi, 0, sizeof(phi));
	sum[1] = phi[1] = 1;

	for (int i = 2; i <= N; i++) {
		if (!phi[i])
			for (int j = i; j <= N; j += i) {
				if (!phi[j]) phi[j] = j;
				phi[j] = phi[j] / i * (i - 1);
			}
	}
	for (int i = 2; i <= N; i++)
		sum[i] = sum[i - 1] + (phi[i] << 1);
}

int main() {
	init();
	while (scanf("%d", &n) && n) {
		printf("%d\n", sum[n]);
	}
	return 0;
}

#include <stdio.h>
const int N = 80;
long long num[N];

void init() {
	num[0] = num[1] = 1, num[2] = 2;
	for (int i = 3; i < N; i++)
		num[i] = num[i - 2] + num[i - 3];
}

int main () {
	init();
	int n;
	while (scanf("%d", &n) == 1) {
		printf("%lld\n", num[n]);
	}
	return 0;
}

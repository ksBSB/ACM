#include <stdio.h>
#include <string.h>
const int N = 15;
int f[N];

void init() {
	memset(f, 0, sizeof(f));
	f[2] = 1;
	for (int i = 2; i < 14; i++)
		f[i + 1] = (4 * i - 6) * f[i] / i;
}

int main () {
	init();
	int n, flag = 0;
	while (scanf("%d", &n) == 1) {
		if (flag) printf("\n");
		else flag = 1;
		printf("%d\n", f[n + 2]);
	}
	return 0;
}

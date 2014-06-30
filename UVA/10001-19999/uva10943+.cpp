#include <stdio.h>
#include <string.h>
const int N = 105;
const int tmp = 1000000;
int num[N][N];

void init() {
	memset(num, 0, sizeof(num));
	for (int i = 0; i <= 100; i++) num[0][i] = 1;

	for (int i = 1; i <= 100; i++)
		for (int j = 1; j <= 100; j++)
			for (int k = 0; k <= i; k++)
				num[i][j] = (num[i][j] + num[k][j - 1]) % tmp;
}

int main () {
	init();
	int n, k;
	while(scanf("%d%d", &n, &k), n || k) {
		printf("%d\n", num[n][k]);
	}
	return 0;
}

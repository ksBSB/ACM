#include <stdio.h>
#include <string.h>
#include <math.h>
const int MAX = pow(10, 9);
const int N = 250005;

int prime[N], cnt;;
double f[N];

void makePrime(int n) {
	int vis[N];
	cnt = 1;
	memset(vis, 0, sizeof(vis));
	for (int i = 2; i * i < n; i++) {
		if (!vis[i]) {
			for (int j = 2 * i; j < n; j += i)
				vis[j] = 1;
		}
	}

	for (int i = 2; i < n; i++)
		if (!vis[i]) prime[cnt++] = i;
}

void init(int n) {
	int flag = 0;
	f[1] = f[2] = 1;
	for (int i = 3; i < n; i++) {
		f[i] = f[i - 1];
		if (flag) f[i] += f[i - 2] / 10;
		else f[i] += f[i - 2];
		flag = 0;
		while (f[i] >= MAX) {
			flag = 1;
			f[i] /= 10;
		}
	}
}

int main () {
	makePrime(N);
	init(N);
	int n;
	while (scanf("%d", &n) == 1) {
		if (n == 1) printf("2\n");
		else if (n == 2) printf("3\n");
		else 
			printf("%d\n", (int)f[prime[n]]);
	}
	return 0;
}

#include <stdio.h>
#include <string.h>
#define max(a,b) (a)>(b)?(a):(b)

const int N = 10005;
const int M = 400;

int n, f[N][M], d[M];

void put(int c[]) {
	for (int i = c[0]; i; i--)
		printf("%d", c[i]);
	printf("\n");
}

void mul(int c[]) {
	int sum = 0;
	for (int i = 1; i <= c[0]; i++) {
		sum += c[i] * 2;
		c[i] = sum %  10;
		sum /= 10;
	}

	while (sum) {
		c[++c[0]] = sum % 10;
		sum /= 10;
	}
}

void add(int ans[], int a[], int b[]) {
	int sum = 0;
	ans[0] = max(a[0],  b[0]);
	for (int i = 1; i <= ans[0]; i++) {
		if (i <= a[0]) sum += a[i];
		if (i <= b[0]) sum += b[i];
		ans[i] = sum % 10;
		sum /= 10;
	}

	while (sum) {
		ans[++ans[0]] = sum % 10;
		sum /= 10;
	}
}

void init() {
	f[1][0] = f[1][1] = d[0] = 1;
	d[1] = 2;
	int c = 0, top = 2;
	for (int i = 2; i <= 10000; i++) {
		add(f[i], f[i - 1], d);
		c++;
		if (c == top) {
			top++, c = 0;
			mul(d);
		}
	}
}

int main () {
	init();
	while (scanf("%d", &n)  == 1) {
		if (n)
			put(f[n]);
		else 
			printf("0\n");
	}
	return 0;
}

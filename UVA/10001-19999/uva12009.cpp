#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 500;

int a[maxn+5], b[maxn+5];

int mul (int* p, int n) {
	int q[maxn+5];
	memset(q, 0, sizeof(q));

	for (int i = 1; i < n; i++) {
		int t = 0, flag = true;
		for (int j = 1; j < n; j++) {
			if (i + j - 1 > n) {
				flag = false;
				break;
			}

			t += p[i] * p[j] + q[i+j-1];
			q[i+j-1] = t % 10;
			t /= 10;
		}

		if (flag) {
			int mv = i+n-1;
			while (t) {
				q[mv++] = t % 10;
				t /= 10;
			}
		}
	}

	/*
	   for (int i = 1; q[i]; i++)
	   printf("%d", q[i]);
	   printf("\n");
	   */
	return q[n];
}

void init () {
	a[1] = 5;
	b[1] = 6;

	mul(a, 2);
	for (int i = 2; i <= maxn; i++) {
		int ra = 0, rb = 0;
		int p = mul(a, i);
		int q = mul(b, i);

		for (int k = 0; k <= 9; k++) {

			if ((2 * k * a[1] + p) % 10 == k)
				ra = k;
			if ((2 * k * b[1] + q) % 10 == k)
				rb = k;
		}
		a[i] = ra;
		b[i] = rb;
	}
}

void put (int* num, int n) {
	printf(" ");
	for (int i = n; i; i--)
		printf("%d", num[i]);
}

int main () {
	init();
	int cas, n;
	scanf("%d", &cas);
	for (int k = 1; k <= cas; k++) {
		scanf("%d", &n);
		printf("Case #%d:", k);
		if (n == 1)
			printf(" 0 1");

		if (a[n] && b[n]) {
			if (a[n] > b[n]) {
				put(b, n);
				put(a, n);
			} else {
				put(a, n);
				put(b, n);
			}
		} else if (a[n]) {
			put(a, n);
		} else if (b[n])
			put(b, n);

		printf("\n");
	}
	return 0;
}

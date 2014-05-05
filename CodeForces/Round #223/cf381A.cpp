#include <stdio.h>
#include <string.h>

const int N = 1005;

int n, num[N];

void init () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &num[i]);
}

void solve () {
	int x = 0, y = 0, p = 0, q = n-1;
	int cnt = 0;
	while (p <= q) {
		if (cnt & 1) {
			if (num[p] > num[q]) {
				y += num[p++];
			} else {
				y += num[q--];
			}
		} else {
			if (num[p] > num[q]) {
				x += num[p++];
			} else {
				x += num[q--];
			}
		}
		cnt++;
	}
	printf("%d %d\n", x, y);
}

int main () {
	init();
	solve();
	return 0;
}

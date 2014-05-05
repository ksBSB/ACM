#include <stdio.h>

int n;

void solve() {
	int t = 2 * (n - 1);
	for (int i = 0; i < t; i++) {
		printf("%d", 2 * (n + i) + 1);
		for (int x = 0; x <= i; x++) {
			int y = i - x;
			if (x >= n || y >= n) continue;
			printf(" %d", x * n + y + 1);
		}
		printf("\n");
	}
}

int main() {
	int cas; scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		solve();
		if (cas) printf("\n");
	}
	return 0;
}

#include <stdio.h>
#include <string.h>

const int N = 8;
const int MAXN = 4500;

int n, a[N], bc, bn;
int rec[N][N][N][N][MAXN];

int dp(int x, int y, int s) {

	int t = 0;
	for (int i = 0; i < 4; i++)
		t = t * 8 + a[i];

	if (!s) {
		if (x != bc && y != bn) return 1;
		else return 0;
	}

	int& ans = rec[bc][bn][x][y][t];
	if (ans != -1)	return ans;
	ans = 0;

	for (int i = 0; i < n; i++) {
		if (i == x) continue;
		for (int j = 1; j <= 3 && j <= a[i]; j++) {
			if (j == y) continue;
			a[i] -= j;
			ans += dp(i, j, s - j);
			a[i] += j;
		}
	}
	return ans;
}

int solve() {
	int s = 0, ans = 0;
	scanf("%d", &n);
	memset(a, 0, sizeof(a));
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		s += a[i];
	}

	if (!s) return 1;

	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= 3 && j <= a[i]; j++) {
			bc = i, bn = j;
			a[i] -= j;
			ans += dp(i, j, s - j);
			a[i] += j;
		}
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	memset(rec, -1, sizeof(rec));
	while (cas--) {
		printf("%d\n", solve());
	}
	return 0;
}

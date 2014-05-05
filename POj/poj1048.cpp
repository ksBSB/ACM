#include <stdio.h>
#include <string.h>
#include <math.h>

const int N = 805;

int n, s, dp[N][N];

void add (int l) {
	for (int i = 800; i >= 0; i--) {
		for (int j = 800; j >= 0; j--) {
			if (dp[i][j]) {
				if (i + l < N)
					dp[i+l][j] = 1;
				if (j + l < N)
					dp[i][j+l] = 1;
			}
		}
	}
}

void init () {
	s = 0;
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	int l;
	for (int i = 0; i < n; i++) {
		scanf("%d", &l);
		s += l;
		add(l);
	}
}

int area (double x, double y, double z) {
	double p = (x*x - y*y + z*z)/(2*z);
	double h = sqrt(x*x - p*p);
	return h*z/2 * 100;
}

void solve () {
	int ans = -1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (dp[i][j] == 0) continue;
			int x = s - i - j;
			if (i + j <= x || i + x <= j || j + x <= i) continue;
			int tmp = area(i, j, x);
			if (tmp > ans)
				ans = tmp;
		}
	}
	printf("%d\n", ans);
}

int main () {
	while (scanf("%d", &n) == 1 && n) {
		init ();
		solve ();
	}
	return 0;
}

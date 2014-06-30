
#include <stdio.h>
#include <string.h>
#include <math.h>

const int MAXN = 15;
const int N = 5;

int n, cnt[MAXN];
double r[MAXN], p[MAXN][MAXN];

void init() {
	scanf("%d", &n);
	memset(r, 0, sizeof(r));
	for (int i = 0; i < N; i++)
		scanf("%d", &cnt[i]);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < N; j++)
			scanf("%lf", &p[i][j]);
}

double dfs(int d, double c) {
	if (n == d) {
		return c;
	}

	double ans = 0;
	for (int i = 0; i < N; i++) {
		if (cnt[i] && fabs(p[d][i]) > 1e-9) {
			cnt[i]--;

			double t = dfs(d + 1, c * p[d][i]);
			ans += t;

			if (d == 0) r[i] += t;

			cnt[i]++;
		}
	}
	return ans;
}

void solve(double s) {
	int id = 0;
	double ans = 0;
	for (int i = 0; i < N; i++) {
		double c = r[i] / cnt[i];
		if (c - ans > 1e-9) {
			id = i;
			ans = c;
		}
	}
	printf("%d %.3lf\n", id + 1, ans / s);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		double s = dfs(0, 1);
		solve(s);
	}
	return 0;
}

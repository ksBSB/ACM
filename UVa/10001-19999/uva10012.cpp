#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>

using namespace std;

const int N = 105;
const double INF = 0x7fffffff;

int n;
double r[N], x[N], y[N], ans;

void init() {
	ans = INF;
	memset(r, 0, sizeof(r));

	scanf("%d", &n);
	for (int i = 0; i < n; i++)	scanf("%lf", &r[i]);
	sort(r, r + n);
}

double dis(int a, int b) {
	return sqrt(r[a] * r[b]) * 2;
}

double lenth(int a, int b) {
	return sqrt( pow(x[a] - x[b], 2) + pow(y[a] - y[b], 2));
}

bool cmp(double a, double b) {
	return a - b < 1e-9;
}

void solve() {
	memset(x, 0, sizeof(x));
	memset(y, 0, sizeof(y));

	x[0] = y[0] = r[0];

	double Max = 2 * r[0];
	for (int i = 1; i < n; i++) {
		x[i] = x[i - 1] + dis(i - 1, i);
		y[i] = r[i];

		if (cmp(x[i], y[i])) x[i] = y[i];

		for (int j = 0; j < i; j++) {
			if (cmp( lenth(i, j), r[i] + r[j]) )
				x[i] = x[j] + dis(i, j);
		}

		if (cmp(Max, x[i] + r[i]) ) Max = x[i] + r[i];
	}

	if (cmp(Max, ans) ) ans = Max; 
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();

		do {
			solve();
		} while (next_permutation(r, r + n));
		printf("%.3lf\n", ans);
	}
	return 0;
}

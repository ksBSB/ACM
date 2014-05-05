#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>

using namespace std;
const int N = 205;
const int INF = 0x3f3f3f3f;
const double pi = acos(-1.0);
const double eps = 1e-9;

struct state {
	double l, r;
}s[N*2];

int n, m;
double d;

bool cmp(const state& a, const state& b) {
	return a.r - b.r < eps;
}

void init () {
	double x, y, c, k;

	m = 0;
	scanf("%d%lf", &n, &d);
	for (int i = 0; i < n; i++) {
		scanf("%lf%lf", &x, &y);
		c = atan2(y, x);
		double dis = sqrt(x*x + y*y);
		if (d >= dis) continue;
		k = asin(d/dis);
		s[m].l = c-k; s[m].r = c+k;
		if (s[m].r > pi) {
			s[m].l -= 2*pi;
			s[m].r -= 2*pi;
		}
		m++;
	}
	sort(s, s + m, cmp);
	for (int i = 0; i < m; i++) {
		s[i+m].l = s[i].l + 2*pi;
		s[i+m].r = s[i].r + 2*pi;
	}
}

int del (state* f) {
	int ans = 1;
	double tmp = f[0].r;
	for (int i = 1; i < m; i++) {
		if (tmp - f[i].l > -eps) continue;
		else {
			tmp = f[i].r;
			ans++;
		}
	}
	return ans;
}

int solve () {
	if (m == 0) return 0;

	int ans = m;
	for (int i = 0; i < m; i++) {
		ans = min(del(s+i), ans);
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}

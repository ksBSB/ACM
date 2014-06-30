#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#define INF 0x3f3f3f3f

using namespace std;
const int N = 1005;

struct Point {
	double x, y, z;
	int sign, same, diff;
}p[N];

struct Dist {
	int l, r;
	double len;
}d[N*N];
int n, c;

double handle(double xi, double yi, double zi) {
	return sqrt(xi*xi + yi*yi + zi*zi);
}

bool cmp(const Dist& a, const Dist& b) {
	return a.len < b.len;
}

void init () {
	c = 0;
	for (int i = 0; i < n; i++) {
		scanf("%lf%lf%lf%d", &p[i].x, &p[i].y, &p[i].z, &p[i].sign);
		p[i].same = 1; p[i].diff = 0;
		for (int j = 0; j < i; j++) {
			d[c].l = i; d[c].r = j;

			d[c++].len = handle(p[i].x - p[j].x, p[i].y - p[j].y, p[i].z - p[j].z);
		}
	}
	sort(d, d + c, cmp);
}

void solve () {
	int ans = 0, tmp = 0;
	double R = 0;
	for (int i = 0; i < c; i++) {
		int t = d[i].l, k = d[i].r;
		if (p[t].sign == p[k].sign) {
			if (p[t].diff - p[t].same == 1) tmp--;
			if (p[k].diff - p[k].same == 1) tmp--;
			p[t].same++; p[k].same++;
		} else {
			if (p[t].same == p[t].diff) tmp++;
			if (p[k].same == p[k].diff) tmp++;
			p[t].diff++; p[k].diff++;
		}

		if (i != c - 1 && fabs(d[i].len - d[i+1].len) < 1e-9) continue;
		if (tmp > ans) {
			ans = tmp; R = d[i].len;
		}
	}
	printf("%d\n%.4lf\n", ans, R);
}

int main () {
	while (scanf("%d", &n) == 1) {
		init();
		solve();
	}
	return 0;
}

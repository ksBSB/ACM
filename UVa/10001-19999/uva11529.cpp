#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int N = 1205;
const double pi = 4 * atan(1.0);
const double eps = 1e-9;

int n;
double s, r[2*N];
struct point {
	double x, y;
}p[N];

double Count (int d) {
	int c = 0, mv = 0;
	for (int i = 0; i < n; i++) {
		if (i == d)
			continue;

		double a = atan2(p[i].y-p[d].y, p[i].x-p[d].x);
		r[c] = a;
		r[c+n-1] = a + 2*pi;
		c++;
	}

	c = 2 * n - 2;
	sort(r, r + c);

	double ans = 0;

	for (int i = 0; i < n-1; i++) {
		double tmp = r[i] + pi;

		while (tmp > r[mv])
			mv++;
		double cnt = mv - i - 1;
		ans = ans + cnt * (cnt-1) / 2;
	}
	return s - ans;
}

double solve () {
	s = (n-1) * (n-2) * (n-3) / 6.0;
	double c = n * (n-1) * (n-2) / 6.0;
	double ans = 0;

	for (int i = 0; i < n; i++)
		ans += Count(i);

	return ans / c;
}

int main () {
	int cas = 1;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			scanf("%lf%lf", &p[i].x, &p[i].y);
		printf("City %d: %.2lf\n", cas++, solve());
	}
	return 0;
}

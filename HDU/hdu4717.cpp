#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int N = 305;
const double eps = 1e-6;
struct point {
	double x;
	double y;
}s[N], p[N];

int n;

void init () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lf%lf%lf%lf", &s[i].x, &s[i].y, &p[i].x, &p[i].y);
}

inline double dis (double x, double y) {
	return sqrt(x*x+y*y);
}

double cat (double k) {
	double ans = 0;
	for (int i = 0; i < n; i++) {
		double xi = s[i].x + p[i].x * k;
		double yi = s[i].y + p[i].y * k;

		for (int j = i + 1; j < n; j++) {
			double pi = s[j].x + p[j].x * k;
			double qi = s[j].y + p[j].y * k;
			ans = max(ans, dis(xi-pi, yi-qi));
		}
	}
	return ans;
}

void solve () {
	double l = 0;
	double r = 0xffffff;

	while (fabs(r-l) > eps) {
		double tmp = (r-l)/3;
		double midl = l + tmp;
		double midr = r - tmp;
		if (cat(midl) < cat(midr))
			r = midr;
		else
			l = midl;
	}
	printf("%.2lf %.2lf\n", l, cat(l));
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init ();
		printf("Case #%d: ", i);
		solve();
	}
	return 0;
}

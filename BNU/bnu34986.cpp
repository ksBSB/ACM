#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double eps = 1e-8;
const int N = 205;

double L, W;
double sx, sy, dx, dy;
double d[N];

double solve () {

	int n, c;
	double w, ans = 1;

	scanf("%d", &n);

	while (n--) {
		scanf("%lf%d", &w, &c);
		double r = sy + w * dy / dx;
		double s = 0;
		c = 2 * c - 1;

		for (int i = 0; i < c; i += 2)
			scanf("%lf", &d[i]);
		for (int i = 1; i < c; i += 2)
			scanf("%lf", &d[i]);	
		for (int i = 0; i < c; i++)
			s += d[i];

		double l = W - r;
		double rec = 0;

		if (l > s) {
			rec += (l - s);
			l = 0;
		} else {
			l = s - l;
		}

		if (r > s) {
			rec += (r - s);
			r = s;
		}


		s = 0;
		for (int i = 0; i < c; i++) {
			double tmp = s + d[i];
			if (i&1) {
				double add = min(r, tmp) - max(s, l);
				rec += max(add, (double)0);
			}
			s = tmp;
		}

		ans *= rec / (W-s);
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		scanf("%lf%lf", &L, &W);
		scanf("%lf%lf%lf%lf", &sx, &sy, &dx, &dy);
		printf("Case #%d: %.5lf\n", i, solve());
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double pi = 4 * atan(1);

double get(double x) {
	return x * pi / 180;
}

int main () {
	int a, b, c, d, e;
	while (scanf("%d%d%d%d%d", &a, &b, &c, &d, &e) == 5) {
		int s = a + b + c + d + e;
		if (s == 0)
			break;

		if (s == 180) {
			double BC = sin(get(b + c)) / sin(get(a));
			double BE = sin(get(c)) / sin(get(180 - c - d - e));
			double CE = BC - BE;

			double AC = sin(get(d + e)) / sin(get(a));
			double AD = sin(get(e)) / sin(get(180 - b - c - e));
			double CD = AC - AD;

			double DE = sqrt(CE * CE + CD * CD - 2 * CE * CD * cos(get(a)));
			double ans = asin( sin(get(b)) * AD / DE );
			printf("%.2lf\n", ans / pi * 180);
		} else
			printf("Impossible\n");
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double eps = 1e-9;
const double pi = 4 * atan(1);

inline int dcmp(double x) { if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }
double toRad(double x) { return x / 180.0 * pi; }

int main () {
	double d, h, a, b, c;
	scanf("%lf%lf", &d, &h);
	while (scanf("%lf%lf%lf", &a, &b, &c) == 3) {
		if (dcmp(a) == 0 && dcmp(b) == 0 && dcmp(c) == 0) break;
		a = tan(toRad(a)), b = tan(toRad(b)), c = tan(toRad(c));
		double ans = d * sqrt(2/(1/a/a+1/c/c-2/b/b)) + h;
		printf("%d\n", (int)(ans + 0.5));
	}
	return 0;
}

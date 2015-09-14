#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double pi = 4 * atan(1);

double dis(double x, double y) {
	return sqrt(x * x + y * y);
}

int main () {
	int n;
	double x1, y1, x2, y2;
	while (scanf("%lf%lf%lf%lf%d", &x1, &y1, &x2, &y2, &n) == 5) {
		if (fabs(n + x1 + y1 + x2 + y2) < 1e-9)
			break;
		double d = dis(x2 - x1, y2 - y1), ans;
		double corner = 2 * pi / n;
		double r = d / 2;

		if (n&1) {
			int k = n / 2;
			double t = k * corner / 2;;
			r = r / sin(t);
		}
		double c = 2 * r * sin(corner/2);
		double h = r * sin((pi - corner)/2);
		ans = h * c / 2 * n;
		printf("%lf\n", ans);
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const double pi = 4 * atan(1.0);

struct point {
	double x, y;
	point (double x = 0, double y = 0) {
		this->x = x;
		this->y = y;
	}
	point rotate (double rx, double ry, double r) {
		double x0 = (x - rx) * cos(r) - (y - ry) * sin(r) + rx;
		double y0 = (x - rx) * sin(r) + (y - ry) * cos(r) + ry;
		return point(x0, y0);
	}
};

int main () {
	int cas, n;
	scanf("%d", &cas);
	while (cas--) {
		double R = 0, x, y, r;
		scanf("%d", &n);

		point S;
		while (n--) {
			scanf("%lf%lf%lf", &x, &y, &r);
			R += r;
			
			if (R >= 2 * pi)
				R -= 2 * pi;
			S = S.rotate(x, y, r);
		}

		double a = 1 - cos(R), b = sin(R);

		double xx = (a * S.x - b * S.y) / (a * a + b * b);
		double yy = (a * S.y + b * S.x) / (a * a + b * b);
		printf("%.10lf %.10lf %.10lf\n", xx, yy, R);
	}
	return 0;
}

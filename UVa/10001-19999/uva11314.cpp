#include <cstdio>
#include <cstring>
#include <cmath>

double xa, ya, xb, yb;

double distant(double x, double y) {
	return sqrt(x*x + y*y);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%lf%lf%lf%lf", &xa, &ya, &xb, &yb);
		printf("%.3lf\n", distant(-xa - xb, ya + yb) + distant(xa-xb, ya-yb));
	}
	return 0;
}

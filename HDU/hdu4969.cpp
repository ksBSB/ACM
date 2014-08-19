#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int main () {
	int cas;
	double v1, v2, r, d;

	scanf("%d", &cas);
	while (cas--) {
		scanf("%lf%lf%lf%lf", &v1, &v2, &r, &d);
		double t = r / v1 * asin(v1 / v2);
		double l = t * v2;
		printf("%s\n", l > d ? "Why give up treatment" : "Wake up to code");
	}
	return 0;
}

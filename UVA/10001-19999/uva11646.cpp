#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double pi = 4.0 * atan(1.0);

int main () {
	int a, b, cas = 1;
	char c[10];
	while (scanf("%d%s%d", &a, c, &b) == 3) {
		double k = sqrt(a * a + b * b);
		double t = asin(b / k);
		double x = 200 / (k * t + a);
		printf("Case %d: %.9lf %.9lf\n", cas++, a * x, b * x);
	}
	return 0;
}

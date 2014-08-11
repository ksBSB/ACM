#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int main  () {
	int cas;
	double a, b, s;
	scanf("%d", &cas);

	while (cas--) {
		scanf("%lf%lf%lf", &a, &b, &s);
		double r = min(s / b, a);
		double ans = r * b + log(a) * s;

		if (fabs(s) > 1e-9)
			ans = ans - log(r) * s;

		double p = 1 - ans / (a * b);
		printf("%.6lf%c\n",  fabs(p * 100), '%');
	}
	return 0;
}

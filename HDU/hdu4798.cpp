#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double pi = 4 * atan(1.0);

int F;
double R, L, H, S;

double solve (double r, double h) {
	int n = pi / atan(S/2/h/r);
	double rad = pi / n;
	return 2 * r * n * tan(pi / n);
}

int main () {
	while (scanf("%lf%lf%lf%d%lf", &R, &L, &H, &F, &S) == 5) {
		double ans = 0, r = (R - L) / F, h = H / F;
		for (int i = 0; i < F; i++)
			ans += solve(L + r * i, h) * h;
		printf("%.3lf\n", ans);
	}
	return 0;
}

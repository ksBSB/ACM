#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double pi = 4 * atan(1.0);

double f (double R, double x) {
	return R * R * x - x * x * x / 3;
}

double solve (double R, double H) {
	if (2 * R <= H)
		return (f(R, R) - f(R, 0)) * 8;

	double h = sqrt(R * R - H * H / 4);
	return (H * H * h / 4 + f(R, R) - f(R, h)) * 8;
}

int main () {
	double R, H;
	while (scanf("%lf%lf", &R, &H) == 2) {
		printf("%.4lf\n", R * R * pi * H * 2 - solve(R, H));
	}
	return 0;
}

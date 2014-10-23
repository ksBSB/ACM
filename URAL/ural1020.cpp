#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 105;
const double pi = 4 * atan(1.0);

int N;
double R, x[maxn], y[maxn];

double dis (double x, double y) {
	return sqrt(x * x + y * y);
}

int main () {
	while (scanf("%d%lf", &N, &R) == 2) {
		for (int i = 0; i < N; i++)
			scanf("%lf%lf", &x[i], &y[i]);
		x[N] = x[0], y[N] = y[0];
		double ans = 2 * pi * R;
		for (int i = 0; i < N; i++)
			ans += dis(x[i]-x[i+1], y[i]-y[i+1]);
		printf("%.2lf\n", ans);
	}
	return 0;
}

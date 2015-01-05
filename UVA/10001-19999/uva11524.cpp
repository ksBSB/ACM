#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 3;

double cal (double a, double b, double c) {
	return a + b - c;
}

int main () {
	int cas;
	double r, m[maxn], n[maxn], k[maxn];
	scanf("%d", &cas);
	while (cas--) {
		scanf("%lf", &r);
		for (int i = 0; i < maxn; i++)
			scanf("%lf%lf", &m[i], &n[i]);

		k[0] = 1;
		k[1] = n[0] * (m[1] + n[1]) / (m[1] * (m[0] + n[0]));
		k[2] = m[0] * (m[2] + n[2]) / (n[2] * (m[0] + n[0]));

		double a = sqrt(4 * (k[0] + k[1] + k[2]) * r * r / (cal(k[0], k[1], k[2]) * cal(k[1], k[2], k[0]) * cal(k[2], k[0], k[1])));
		double b = a * k[1];
		double c = a * k[2];
		double ans = (a + b + c) * r / 2;
		printf("%.4lf\n", ans);
	}
	return 0;
}

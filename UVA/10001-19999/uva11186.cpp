#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 505;
const double pi = 4 * atan(1);

double A[maxn];

double area (double d, double r) {
	if (d > 180)
		d = 360 - d;
	d = d * pi / 180;
	double L = 2 * r * sin(d / 2);
	double H = r * sin((pi - d) / 2);
	return L * H / 2;
}

int main () {
	int N, R;
	while (scanf("%d%d", &N, &R) == 2 && N + R) {
		for (int i = 0; i < N; i++)
			scanf("%lf", &A[i]);
		sort(A, A + N);

		double ans = 0;
		for (int i = 0; i < N; i++) {
			for (int j = i + 1; j < N; j++) {
				int bo = (A[j] - A[i] > 180 ? -1 : 1);
				int n = j - i - 1;
				double s = area(A[j] - A[i], R);
	//			printf("%d %d %lf\n", i, j, s);
				ans += bo * s * (N - 2 * n - 2);
	//			printf("%lf!\n", ans);
			}
		}
		printf("%.0lf\n", ans);
	}
	return 0;
}

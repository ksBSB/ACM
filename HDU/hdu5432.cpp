#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 10005;
const double eps = 1e-4;

int N;
double A[maxn], B[maxn];

double judge(double h) {
	double ret = 0;
	for (int i = 0; i < N; i++) {
		if (A[i] < h) continue;
		double a = A[i] - h;
		double b = a * B[i] / A[i];
		ret += a * b * b;
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		double l = 0, r = 0;
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%lf", &A[i]);
			r = max(r, A[i]);
		}
		for (int i = 0; i < N; i++) scanf("%lf", &B[i]);

		double ans = judge(0) / 2;
		while (fabs(r - l) > eps) {
			double mid = (l + r) / 2;
			if (judge(mid) > ans) l = mid;
			else r = mid;
		}
		printf("%d\n", (int)l);
	}
	return 0;
}

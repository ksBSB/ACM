#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 30;

int N;
double L, vr[maxn], vk[maxn];

void init () {
	for (int i = 1; i <= N; i++) {
		vr[i] = 1/vr[i] - 1/vk[i];
		vk[i] = L/vk[i];
	}

	for (int i = 1; i < N; i++) {
		vr[i] -= vr[N];
		vk[i] -= vk[N];
	}
}

double f (double x) {
	double ret = vr[1] * x + vk[1];
	for (int i = 2; i < N; i++)
		ret = min(ret, vr[i] * x + vk[i]);
	return ret;
}

double tsearch (double l, double r) {
	for (int i = 0; i < 100; i++) {
		double p = l + (r - l) / 3;
		double q = r - (r - l) / 3;
		if (f(p) > f(q))
			r = q;
		else
			l = p;
	}
	return l;
}

int main () {
	while (scanf("%lf%d", &L, &N) == 2) {
		for (int i = 1; i <= N; i++)
			scanf("%lf%lf", &vr[i], &vk[i]);
		init();
		double x = tsearch(0, L);
		if (f(x) < 0)
			printf("The cheater cannot win.\n");
		else
			printf("The cheater can win by %.0lf seconds with r = %.2lfkm and k = %.2lfkm.\n", f(x) * 3600, x, L-x);
	}
	return 0;
}

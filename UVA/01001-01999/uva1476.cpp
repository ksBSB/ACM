#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 10005;

int n, a[maxn], b[maxn], c[maxn];

double f (double x) {
	double ret = a[0] * x * x + b[0] * x + c[0];
	for (int i = 0; i < n; i++)
		ret = max(ret, a[i] * x * x + b[i] * x + c[i]);
	return ret;
}

double search (double l, double r) {
	for (int i = 0; i < 100; i++) {
		double p = l + (r-l) / 3;
		double q = r - (r-l) / 3;
		if (f(p) > f(q))
			l = p;
		else
			r = q;
	}
	return l;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d%d%d", &a[i], &b[i], &c[i]);
		double x = search(0, 1000);
		printf("%.4lf\n", f(x));
	}
	return 0;
}

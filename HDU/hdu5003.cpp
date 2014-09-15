#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxn = 55;

int n;
double p[maxn];

bool cmp (const double &a, const double& b) {
	return a > b;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%lf", &p[i]);
		sort(p, p + n, cmp);

		double ans = 0;
		for (int i = 0; i < n; i++)
			ans += pow(0.95, i) * p[i];
		printf("%.10lf\n", ans);
	}
	return 0;
}

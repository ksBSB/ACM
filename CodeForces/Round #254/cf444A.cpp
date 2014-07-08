#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 500;

int n, m;
double val[maxn+5];

int main () {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%lf", &val[i]);

	double ans = 0, k;
	int a, b;

	for (int i = 0; i < m; i++) {
		scanf("%d%d%lf", &a, &b, &k);
		double tmp = (val[a] + val[b]) / k;
		if (tmp > ans)
			ans = tmp;
	}
	printf("%.15lf\n", ans);
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 50005;
const double INF = 1e20;

int N, K;
double p[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &N, &K);
		for (int i = 1; i <= N; i++)
			scanf("%lf", &p[i]);
		if (N == K) {
			printf("%.10lf\n", 0.0);
			continue;
		}
		sort(p + 1, p + 1 + N);
		int n = N - K;
		double s = 0, t = 0;
		for (int i = 1; i <= n; i++) {
			t += p[i] * p[i];
			s += p[i];
		}
		double ans = t - s * s / n;
		for (int i = n + 1; i <= N; i++) {
			t += p[i] * p[i] - p[i-n] * p[i-n];
			s += p[i] - p[i-n];
			ans = min(ans, t - s * s / n);
		}
		printf("%.10lf\n", ans);
	}
	return 0;
}

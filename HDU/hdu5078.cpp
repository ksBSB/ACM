#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int N;
struct state {
	double ti, x, y;
}s[maxn];

inline bool cmp (const state& a, const state& b) {
	return a.ti < b.ti;
}

inline double dis(double x, double y) {
	return sqrt(x * x + y * y);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%lf%lf%lf", &s[i].ti, &s[i].x, &s[i].y);
		sort(s, s + N, cmp);
		double ans = 0;
		for (int i = 1; i < N; i++)
			ans = max(ans, dis(s[i].x - s[i-1].x, s[i].y - s[i-1].y) / (s[i].ti - s[i-1].ti));
		printf("%.10lf\n", ans);
	}
	return 0;
}

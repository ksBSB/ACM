#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;

struct point {
	int x, id;
}p[maxn];

int N, M, K, g[maxn][11];
double v[maxn];

bool cmp (const point& a, const point& b) {
	return a.x < b.x;
}

bool judge (int i, int l, int r) {
	if (r > N)
		return true;
	if (l <= 0)
		return false;
	if (p[i].x - p[l].x != p[r].x - p[i].x)
		return p[i].x - p[l].x < p[r].x - p[i].x;
	return p[l].id < p[r].id;
}

void get_KNN(int x) {

	int id = p[x].id;
	int l = x - 1, r = x + 1;
	for (int i = 0; i < K; i++) {
		if (judge(x, l, r))
			g[id][i] = p[l--].id;
		else
			g[id][i] = p[r++].id;
	}
}

void init () {
	scanf("%d%d%d", &N, &M, &K);

	for (int i = 1; i <= N; i++) {
		scanf("%d%lf", &p[i].x, &v[i]);
		p[i].id = i;
	}

	sort(p + 1, p + N + 1, cmp);

	for (int i = 1; i <= N; i++)
		get_KNN(i);
}

int main () {
	int cas, x;
	scanf("%d", &cas);
	while (cas--) {
		init();
		double ans = 0;
		for (int i = 0; i < M; i++) {
			scanf("%d", &x);
			double tmp = 0;

			for (int j = 0; j < K; j++)
				tmp += v[g[x][j]];

			v[x] = tmp / K;
			ans += v[x];
		}
		printf("%.6lf\n", ans);
	}
	return 0;
}

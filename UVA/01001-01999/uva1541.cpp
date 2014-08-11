#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 100;

bool lose[maxn], vis[maxn][maxn];
double p[maxn][maxn];
int N, T, inst[maxn];

void init () {
	char str[maxn];
	memset(inst, 0, sizeof(inst));
	memset(vis, false, sizeof(vis));
	memset(lose, false, sizeof(lose));

	scanf("%d%d", &N, &T);
	for (int i = 1; i <= N; i++) {
		scanf("%s", str);
		if (str[0] == 'L')
			lose[i] = true;
		else
			sscanf(str, "%d", &inst[i]);
	}
}

double dfs (int d, int k) {

	if (vis[d][k])
		return p[d][k];

	vis[d][k] = true;

	if (d == N + 1)
		return p[d][k] = 1;

	if (k <= 0)
		return p[d][k] = 0;

	double& ret = p[d][k];
	ret = 0;

	int next = d + 1;
	if (lose[next])
		ret += 0.5 * dfs(next, k-2);
	else
		ret += 0.5 * dfs(next + inst[next], k - 1);

	next = min(d + 2, N + 1);
	if (lose[next])
		ret += 0.5 * dfs(next, k-2);
	else
		ret += 0.5 * dfs(next + inst[next], k - 1);

	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		double ans = dfs(0, T);
		if (fabs(ans - 0.5) < 1e-9)
			printf("Push. 0.5000\n");
		else if (ans > 0.5)
			printf("Bet for. %.4lf\n", ans);
		else
			printf("Bet against. %.4lf\n", ans);
	}
	return 0;
}

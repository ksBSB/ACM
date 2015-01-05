#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <set>
#include <bitset>
#include <algorithm>

using namespace std;
const int maxn = 55;
const int maxm = 15;
const int inf = 0x3f3f3f3f;

bitset<maxn * maxn> s, p[maxm];

int N, K, R[maxm], C[maxm], D[maxm];
int g[maxn][maxn];

void init () {
	memset(g, 0, sizeof(g));

	scanf("%d", &K);
	for (int i = 0; i < K; i++) {
		scanf("%d%d", &R[i], &C[i]);
		g[R[i]][C[i]] = 1;
	}
	for (int i = 0; i < K; i++)
		scanf("%d", &D[i]);

	for (int i = 0; i < K; i++) {
		p[i].reset();
		for (int x = 1; x <= N; x++) {
			for (int y = 1; y <= N; y++) {
				if (g[x][y])
					continue;
				if (abs(x - R[i]) + abs(y - C[i]) <= D[i])
					p[i].set( (x-1) * N + y-1);
			}
		}
	}
}

int solve() {
	int ans = inf;

	for (int i = 0; i < (1<<K); i++) {
		int cnt = 0;
		s.reset();

		for (int j = 0; j < K; j++) {
			if (i&(1<<j)) {
				cnt++;
				s |= p[j];
			}
		}

		if (s.count() == N * N - K)
			ans = min(ans, cnt);
	}
	return ans == inf ? -1 : ans;
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}

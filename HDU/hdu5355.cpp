#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 50;
typedef long long ll;

int s[maxn], t[maxn];
vector<int> G[maxn];

bool dfs (int d, int k, int n, int m) {
	if (d <= 0)
		return true;
	
	for (int i = 1; i <= m; i++) {
		if (s[i] + d > k)
			continue;
		t[d] = i;
		s[i] += d;
		if (dfs(d-1, k, n, m))
			return true;
		t[d] = 0;
		s[i] -= d;
	}
	return false;
}

void solve (int n, int m) {
	for (int i = 1; i <= m; i++) {
		s[i] = t[i] = 0;
		G[i].clear();
	}

	while (n > 40) {
		for (int i = 1; i <= m; i++)
			G[i].push_back(n--);
		for (int i = m; i; i--)
			G[i].push_back(n--);
	}

	dfs(n, n * (n+1) / 2 / m, n, m);
	for (int i = 1; i <= n; i++)
		G[t[i]].push_back(i);
}

int main () {
	int cas, n, m;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &n, &m);
		ll k = 1LL * n * (n + 1) / 2;
		if (k % m == 0 && n >= 2 * m - 1) {
			printf("YES\n");
			solve(n, m);
			for (int i = 1; i <= m; i++) {
				sort(G[i].begin(), G[i].end());
				int t = G[i].size();
				printf("%d", t);
				for (int j = 0; j < t; j++)
					printf(" %d", G[i][j]);
				printf("\n");
			}
		} else {
			printf("NO\n");
		}
	}
	return 0;
}

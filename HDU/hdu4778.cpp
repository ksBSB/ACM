#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxb = 21;
const int maxn = 1<<21;
const int maxg = 10;
const int INF = 0x3f3f3f3f;

int G, B, S;
int c[maxb+5][maxg], s[maxn+5][maxg];
int v[maxn+5], dp[maxn+5];

void init () {
	int t, a;
	memset(c, 0, sizeof(c));
	memset(v, 0, sizeof(v));

	for (int i = 0; i < B; i++) {
		scanf("%d", &t);
		for (int j = 0; j < t; j++) {
			scanf("%d", &a);
			c[i][a]++;
		}
	}

	for (int i = 0; i < (1<<B); i++) {
		for (int j = 0; j < B; j++) {

			if (i&(1<<j))
				continue;

			int e = i|(1<<j);
			
			if (v[e])
				continue;

			for (int k = 1; k <= G; k++)
				s[e][k] = (s[i][k] + c[j][k]) % S;
		}
	}
}

int add (int k, int x) {
	int ans = 0;
	for (int i = 1; i <= G; i++)
		ans += (s[k][i] + c[x][i]) / S;
	return ans;
}

int dfs (int u) {

	if (u + 1 == (1<<B))
		return 0;

	if (v[u])
		return dp[u];

	int up = -INF;
	int lower = INF;

	for (int i = 0; i < B; i++) {
		if (u&(1<<i))
			continue;

		int g = add (u, i);

		if (g)
			up = max(up, dfs(u|(1<<i))+g);
		else
			lower = min(lower, dfs(u|1<<i));
	}
	v[u] = 1;
	return dp[u] = max(up, -lower);
}

int main () {
	while (scanf("%d%d%d", &G, &B, &S) == 3 && G + B + S) {
		init();
		memset(v, 0, sizeof(v));
		printf("%d\n", dfs(0));
	}
	return 0;
}

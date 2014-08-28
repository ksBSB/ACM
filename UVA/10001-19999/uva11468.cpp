#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int sigma_size = 62;
const int maxn = 405;;

double pi[sigma_size], dp[maxn][105];
int vis[maxn][105];

int sz;
int ac[maxn][sigma_size];
int fail[maxn], last[maxn];

inline int idx (char ch) {
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	if (ch >= 'a' && ch <= 'z')
		return ch - 'a' + 10;
	if (ch >= 'A' && ch <= 'Z')
		return ch - 'A' + 36;
	return 0;
}

void ahoc_insert (char *s) {
	int u = 0, n = strlen(s);
	for (int i = 0; i < n; i++) {
		int v = idx(s[i]);

		if (ac[u][v] == 0) {
			last[sz] = 0;
			memset(ac[sz], 0, sizeof(ac[sz]));
			ac[u][v] = sz++;
		}
		u = ac[u][v];
	}
	last[u] = 1;
}

void ahoc_fail () {
	queue<int> que;
	
	for (int i = 0; i < sigma_size; i++) {
		int u = ac[0][i];
		if (u) {
			fail[u] = 0;
			que.push(u);
		}
	}

	while (!que.empty()) {
		int r = que.front();
		que.pop();

		for (int i = 0; i < sigma_size; i++) {
			int u = ac[r][i];

			if (u == 0) {
				ac[r][i] = ac[fail[r]][i];
				continue;
			}

			que.push(u);
			int v = fail[r];

			while (v && !ac[v][i])
				v = fail[v];
			fail[u] = ac[v][i];
			last[u] |= last[fail[u]];
		}
	}
}

void init () {
	int n, x;
	char str[sigma_size];
	memset(pi, 0, sizeof(pi));
	memset(vis, 0, sizeof(vis));

	sz = 1;
	fail[0] = last[0] = 0;
	memset(ac[0], 0, sizeof(ac[0]));

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", str);
		ahoc_insert(str);
	}
	ahoc_fail();

	scanf("%d", &n);
	for (int i = 0; i < n; i++)  {
		scanf("%s", str);
		scanf("%lf", &pi[idx(str[0])]);
	}
}

double getProb (int u, int dep) {
	if (dep == 0)
		return 1.0;

	if (vis[u][dep])
		return dp[u][dep];

	vis[u][dep] = 1;

	double& ans = dp[u][dep];
	ans = 0;

	for (int i = 0; i < sigma_size; i++) {
		if (last[ac[u][i]] == 0)
			ans += pi[i] * getProb(ac[u][i], dep - 1);
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();

		int n;
		scanf("%d", &n);
		printf("Case #%d: %.6lf\n", kcas, getProb(0, n));
	}
	return 0;
}

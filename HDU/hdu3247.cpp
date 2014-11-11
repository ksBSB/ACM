#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


typedef pair<int,int> pii;
const int maxn = 100005;
const int maxm = 1005;
const int sigma_size = 2;
const int inf = 0x3f3f3f3f;

struct Aho_Corasick {
    int sz, g[maxn][sigma_size];
    int tag[maxn], fail[maxn], vis[maxn];

	void init();
	int idx(char ch);
	void insert(char* str, int k);
	void getFail();
	void match(char* str);
	void put(int x, int y);

	queue<int> que;
	int K, pos[maxm], dis[maxn];
	int dp[maxm][1030], d[maxm][maxm];

	int solve();
	void BFS(int s);
	int DP();
}AC;

int N, M;
char w[1005];

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		AC.init();
		for (int i = 1; i <= N; i++) {
			scanf("%s", w);
			AC.insert(w, i);
		}
		for (int i = 1; i <= M; i++) {
			scanf("%s", w);
			AC.insert(w, 0);
		}
		printf("%d\n", AC.solve());
	}
	return 0;
}

int Aho_Corasick::DP() {
	int E = (1<<N)-1;
	memset(dp, inf, sizeof(dp));
	dp[0][0] = 0;

	for (int i = 0; i < E; i++) {
		for (int u = 0; u < K; u++) {
			if (dp[u][i] == inf)
				continue;

			for (int v = 0; v < K; v++) {
				if (d[u][v] == inf)
					continue;

				int s = i | (tag[pos[v]]>>1);
				dp[v][s] = min(dp[v][s], dp[u][i] + d[u][v]);
			}
		}
	}
	int ans = inf;
	for (int i = 0; i < K; i++)
		ans = min(ans, dp[i][E]);
	return ans;
}

void Aho_Corasick::BFS(int s) {
	memset(dis, inf, sizeof(dis));
	dis[pos[s]] = 0;
	que.push(pos[s]);

	while (!que.empty()) {
		int u = que.front();
		que.pop();

		for (int i = 0; i < sigma_size; i++) {
			int t = u;
			while (t && g[t][i] == 0)
				t = fail[t];
			t = g[t][i];

			if (tag[t]&1)
				continue;
			if (dis[t] > dis[u] + 1) {
				dis[t] = dis[u] + 1;
				que.push(t);
			}
		}
	}
	for (int i = 0; i < K; i++)
		d[s][i] = dis[pos[i]];
}

int Aho_Corasick::solve() {
	getFail();
	K = 0;
	pos[K++] = 0;
	for (int i = 1; i <sz; i++) {
		if (tag[i]>>1)
			pos[K++] = i;
	}
	for (int i = 0; i < K; i++)
		BFS(i);
	return DP();
}

void Aho_Corasick::init() {
	sz = 1;
	tag[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Aho_Corasick::idx(char ch) {
	return ch - '0';
}

void Aho_Corasick::put(int x, int y) {
}

void Aho_Corasick::insert(char* str, int k) {
	int u = 0, n = strlen(str);

	for (int i = 0; i < n; i++) {
		int v = idx(str[i]);
		if (g[u][v] == 0) {
			vis[sz] = tag[sz] = 0;
			memset(g[sz], 0, sizeof(g[sz]));
			g[u][v] = sz++;
		}
		u = g[u][v];
	}
	tag[u] = (1<<k);
}

void Aho_Corasick::match(char* str) {
	int n = strlen(str), u = 0;
	for (int i = 0; i < n; i++) {
		int v = idx(str[i]);
		while (u && g[u][v] == 0)
			u = fail[u];

		u = g[u][v];

	}
}

void Aho_Corasick::getFail() {

	for (int i  = 0; i < sigma_size; i++) {
		int u = g[0][i];
		if (u) {
			fail[u] = 0;
			que.push(u);
		}
	}

	while (!que.empty()) {
		int r = que.front();
		que.pop();

		for (int i = 0; i < sigma_size; i++) {
			int u = g[r][i];

			if (u == 0) {
				g[r][i] = g[fail[r]][i];
				continue;
			}

			que.push(u);
			int v = fail[r];
			while (v && g[v][i] == 0)
				v = fail[v];

			fail[u] = g[v][i];
			tag[u] |= tag[fail[u]];
			//last[u] = tag[fail[u]] ? fail[u] : last[fail[u]];
		}
	}
}

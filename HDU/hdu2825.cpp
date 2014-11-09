#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int maxn = 255;
const int sigma_size = 26;
const int mod = 20090717;

inline int bitcount (int x) {
	return x == 0 ? 0 : bitcount(x>>1) + (x&1);
}

struct Aho_Corasick {
    int sz, g[maxn][sigma_size];
    int tag[maxn], fail[maxn], last[maxn];
	int dp[2][maxn][1030];

    void init();
    int idx(char ch);
    void insert(char* str, int k);
	void getFail();
	void match(char* str);
	int put(int u);
	int solve();
}AC;

int N, M, K;

int main () {
	while (scanf("%d%d%d", &N, &M, &K) == 3 && N + M + K) {
		char w[30];
		AC.init();
		for (int i = 1; i <= M; i++) {
			scanf("%s", w);
			AC.insert(w, i);
		}
		if (K > M)
			printf("0\n");
		else
			printf("%d\n", AC.solve());
	}
	return 0;
}

int Aho_Corasick::solve() {
	getFail();
	memset(dp[0], 0, sizeof(dp[0]));
	dp[0][0][0] = 1;

	for (int x = 0; x < N; x++) {
		int now = x&1;
		int nxt = now^1;
		memset(dp[nxt], 0, sizeof(dp[nxt]));

		for (int i = 0; i < sz; i++) {
			for (int k = 0; k < (1<<M); k++) {
				if (dp[now][i][k] == 0)
					continue;

				for (int j = 0; j < sigma_size; j++) {
					int u = i;
					while (u && g[u][j] == 0)
						u = fail[u];

					u = g[u][j];

					int d = tag[u];
					dp[nxt][u][k|d] = (dp[nxt][u][k|d] + dp[now][i][k]) % mod;
				}
			}
		}
	}

	int n = 0, v[1030];
	memset(v, 0, sizeof(v));
	for (int i = 0; i < (1<<M); i++)
		if (bitcount(i) >= K)
			v[n++] = i;

	int ans = 0, d = N&1;
	for (int u = 0; u < sz; u++) {
		for (int i = 0; i < n; i++)
			ans = (ans + dp[d][u][v[i]]) % mod;
	}
	return ans;
}

void Aho_Corasick::init() {
	sz = 1;
	tag[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Aho_Corasick::idx(char ch) {
	return ch - 'a';
}

int Aho_Corasick::put(int u) {
	return 0;
}

void Aho_Corasick::insert(char* str, int k) {
	int u = 0, n = strlen(str);

	for (int i = 0; i < n; i++) {
		int v = idx(str[i]);
		if (g[u][v] == 0) {
			tag[sz] = 0;
			memset(g[sz], 0, sizeof(g[sz]));
			g[u][v] = sz++;
		}
		u = g[u][v];
	}
	tag[u] = (1<<(k-1));
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
	queue<int> que;

	for (int i  = 0; i < sigma_size; i++) {
		int u = g[0][i];
		if (u) {
			fail[u] = last[u] = 0;
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

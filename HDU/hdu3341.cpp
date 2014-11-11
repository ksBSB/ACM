#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


typedef pair<int,int> pii;
const int maxn = 505;
const int maxs = 11 * 11 * 11 * 11;
const int sigma_size = 4;

struct Aho_Corasick {
    int sz, g[maxn][sigma_size];
    int tag[maxn], fail[maxn], last[maxn];

	int c[4], bit[4], dp[maxs][maxn];

    void init();
    int idx(char ch);
    void insert(char* str, int k);
	void getFail();
	void match(char* str);
	void put(int x, int y);
	int solve(char* w);
	int hash(int a, int b, int c, int d);
}AC;

int N;
char w[50];

int main () {
	int cas = 1;
	while (scanf("%d", &N) == 1 && N) {
		AC.init();
		for (int i = 1; i <= N; i++) {
			scanf("%s", w);
			AC.insert(w, i);
		}
		scanf("%s", w);
		printf("Case %d: %d\n", cas++, AC.solve(w));
	}
	return 0;
}

int Aho_Corasick::hash(int a, int b, int c, int d) {
	return a * bit[0] + b * bit[1] + c * bit[2] + d;
}

int Aho_Corasick::solve(char* w) {
	getFail();

	int n = strlen(w);
	memset(c, 0, sizeof(c));
	for (int i = 0; i < n; i++)
		c[idx(w[i])]++;
	for (int i = 0; i < 4; i++) {
		bit[i] = 1;
		for (int j = i + 1; j < 4; j++)
			bit[i] *= (c[j]+1);
	}

	int ans = 0, t[4];
	memset(dp, -1, sizeof(dp));
	dp[hash(c[0], c[1], c[2], c[3])][0] = 0;

	for (t[0] = c[0]; t[0] >= 0; t[0]--)
		for (t[1] = c[1]; t[1] >= 0; t[1]--)
			for (t[2] = c[2]; t[2] >= 0; t[2]--)
				for (t[3] = c[3]; t[3] >= 0; t[3]--) {
					int s = hash(t[0], t[1], t[2], t[3]);
					for (int i = 0; i < 4; i++) {
						if (t[i] == 0)
							continue;
						int ss = s - bit[i];

						for (int k = 0; k < sz; k++) {

							if (dp[s][k] < 0)
								continue;

							int u = k;
							while (u && g[u][i] == 0)
								u = fail[u];
							u = g[u][i];

							if (dp[ss][u] < dp[s][k] + tag[u]) {
								dp[ss][u] = dp[s][k] + tag[u];
								ans = max(ans, dp[ss][u]);
							}
						}
					}
				}

	return ans;
}

void Aho_Corasick::init() {
	sz = 1;
	tag[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Aho_Corasick::idx(char ch) {
	if (ch == 'A')
		return 0;
	if (ch == 'C')
		return 1;
	if (ch == 'G')
		return 2;
	return 3;
}

void Aho_Corasick::put(int x, int y) {
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
	tag[u]++;
}

void Aho_Corasick::match(char* str) {
	int n = strlen(str), u = 0;
	for (int i = 0; i < n; i++) {
		int v = idx(str[i]);
		while (u && g[u][v] == 0)
			u = fail[u];

		u = g[u][v];

		if (tag[u])
			put(i, u);
		else if (last[u])
			put(i, last[u]);
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
			tag[u] += tag[fail[u]];
			//last[u] = tag[fail[u]] ? fail[u] : last[fail[u]];
		}
	}
}

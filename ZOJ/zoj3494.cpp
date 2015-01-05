#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 2005;
const int mod = 1e9 + 9;
const int sigma_size = 2;
const char sign[12][5] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001"};

struct Aho_Corasick {
    int sz, g[maxn][sigma_size];
    int tag[maxn], fail[maxn], last[maxn];

	int dp[205][maxn];

    void init();
    int idx(char ch);
    void insert(char* str, int k);
	void getFail();
	void match(char* str);
	void put(int x, int y);
	int solve(int* a, int n);
	int move(int u, int v);
}AC;

int N, num[205];

int getNum(int* a) {
	char s[205];
	scanf("%s", s);
	int n = strlen(s), mv = 0;
	while (mv < n && s[mv] == '0') mv++;

	n -= mv;
	if (n == 0)
		num[n++] = 0;
	else {
		for (int i = 0; i < n; i++)
			num[i] = s[i+mv] - '0';
	}
	return n;
}

void del(int* a, int& n) {
	if (n == 0)
		return;

	a[n-1]--;
	for (int i = n-1; i >= 0; i--) {
		if (a[i] < 0) {
			a[i] += 10;
			a[i-1]--;
		} else
			break;
	}

	if (a[0] == 0) {
		for (int i = 0; i < n; i++)
			a[i] = a[i+1];
		n--;
	}
}

int main () {
	int cas, n;
	char w[50];
	scanf("%d", &cas);

	while (cas--) {
		AC.init();
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%s", w);
			AC.insert(w, i);
		}
		AC.getFail();

		N = getNum(num);
		del(num, N);
		int l = AC.solve(num, N);

		N = getNum(num);
		int r = AC.solve(num, N);

		printf("%d\n", (r - l + mod) % mod);
	}
	return 0;
}

int Aho_Corasick::move(int u, int id) {
	for (int i = 0; i < 4; i++) {
		int v = idx(sign[id][i]);
		while (u && g[u][v] == 0)
			u = fail[u];
		u = g[u][v];

		if (tag[u] || last[u])
			return -1;
	}
	return u;
}

int Aho_Corasick::solve(int* a, int n) {
	if (n == 0)
		return 0;
	memset(dp, 0, sizeof(dp));

	int eq = 1, mv = 0;
	for (int i = 0; i < n; i++) {
		for (int x = 0; x < sz; x++) {
			if (tag[x] || last[x])
				continue;

			for (int j = 0; j < 10; j++) {
				int u = move(x, j);
				if (u == -1)
					continue;
				dp[i+1][u] = (dp[i+1][u] + dp[i][x]) % mod;
			}
		}

		if (i) {
			for (int j = 1; j < 10; j++) {
				int u = move(0, j);
				if (u == -1)
					continue;
				dp[i+1][u] = (dp[i+1][u] + 1) % mod;
			}
		}

		if (eq) {
			for (int j = (i == 0 ? 1 : 0); j < a[i]; j++) {
				int u = move(mv, j);
				if (u == -1)
					continue;
				dp[i+1][u] = (dp[i+1][u] + 1) % mod;
			}

			int u = move(mv, a[i]);
			if (u == -1) eq = 0;
			mv = u;
		}
	}

	int ans = eq;
	for (int i = 0; i < sz; i++) {
		if (tag[i] || last[i])
			continue;
		ans = (ans + dp[n][i]) % mod;
	}
	return ans;
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
			tag[sz] = 0;
			memset(g[sz], 0, sizeof(g[sz]));
			g[u][v] = sz++;
		}
		u = g[u][v];
	}
	tag[u] = k;
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
			last[u] = tag[fail[u]] ? fail[u] : last[fail[u]];
		}
	}
}

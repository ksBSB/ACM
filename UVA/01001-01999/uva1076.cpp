#include <cstdio>
#include <cstring>
#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int maxn = 105;
const int maxs = (1<<10)+5;
const int sigma_size = 26;

struct Aho_Corasick {
	int sz, g[maxn][sigma_size];
	int val[maxn], fail[maxn];

	void init();
	int idx(char ch);
	void insert(char* str, int k);
	void get_fail();
}AC;

int N, M;
vector<string> vec;
ll dp[30][maxn][maxs];

void init () {
	AC.init();
	char str[20];

	for (int i = 0; i < M; i++) {
		cin >> str;
		AC.insert(str, i);
	}
	AC.get_fail();
	memset(dp, -1, sizeof(dp));
}

ll solve (int d, int u, int s) {

	if (d >= N)
		return s == (1<<M)-1 ? 1 : 0;

	if (dp[d][u][s] != -1)
		return dp[d][u][s];

	ll& ret = dp[d][u][s];
	ret = 0;

	for (int i = 0; i < sigma_size; i++) {
		int v = AC.g[u][i];
		ret += solve(d + 1, v, s | AC.val[v]);
	}
	return ret;
}

void search (int d, int u, int s, string str) {

	if (d >= N) {
		if (s == (1<<M) - 1)
			vec.push_back(str);
		return;
	}

	if (dp[d][u][s] <= 0)
		return ;

	for (int i = 0; i < sigma_size; i++) {
		int v = AC.g[u][i];
		char ch = 'a' + i;
		search(d + 1, v, s | AC.val[v], str + ch);
	}
}

int main () {
	int cas = 0;
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init();
		ll ans = solve(0, 0, 0);
		//printf("Case %d: %lld suspects\n", ++cas, ans);
		cout << "Case " << ++cas << ": " << ans << " suspects" << endl;

		if (ans <= 42) {
			vec.clear();
			search(0, 0, 0, "");
			sort(vec.begin(), vec.end());
			for (int i = 0; i < vec.size(); i++)
				cout << vec[i] << endl;
		}
	}
	return 0;
}

void Aho_Corasick::init() {
	sz = 1;
	memset(g[0], 0, sizeof(g[0]));
}

int Aho_Corasick::idx(char ch) {
	return ch - 'a';
}

void Aho_Corasick::insert(char* str, int k) {
	int u = 0, n = strlen(str);

	for (int i = 0; i < n; i++) {
		int v = idx(str[i]);
		if (g[u][v] == 0) {
			val[sz] = 0;
			memset(g[sz], 0, sizeof(g[sz]));
			g[u][v] = sz++;
		}
		u = g[u][v];
	}
	val[u] |= (1<<k);
}

void Aho_Corasick::get_fail() {
	queue<int> que;

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
			val[u] |= val[fail[u]];
		}
	}
}

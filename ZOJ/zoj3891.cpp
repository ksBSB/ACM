#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 50005;
const int maxm = 35;
const int SIGMA_SIZE = 10;

struct SAM {
	int sz, last;
	int g[maxn<<1][SIGMA_SIZE], pre[maxn<<1], step[maxn<<1];
	int pos[maxn<<1], right[maxn<<1], cnt[maxn<<1];

	void newNode(int s) {
		step[++sz] = s;
		pre[sz] = 0;
		memset(g[sz], 0, sizeof(g[sz]));
	}

	int idx(char ch) { return ch -'0'; }

	void init() {
		sz = 0, last = 1;
		newNode(0);
	}

	void insert(char ch);
	void get_tuopu();
	void get_right(char* str);

	int dp[maxn<<1][maxm];
	void solve (int k) {
		memset(dp, 0, sizeof(dp));
		dp[1][0] = 1;

		for (int i = 1; i <= sz; i++) {
			int u = pos[i];

			for (int j = 0; j < SIGMA_SIZE; j++) {
				if (u == 1 && j == 0) continue;
				int v = g[u][j];
				if (v == 0) continue;
				for (int x = 0; x < k; x++) {
					int y = (x * 10 + j) % k;
					dp[v][y] += dp[u][x];
				}
			}
		}

		int ans[maxm];
		memset(ans, 0, sizeof(ans));
		for (int i = 2; i <= sz; i++) {
			for (int j = 0; j < k; j++)
				ans[j] += dp[i][j];
		}
		if (g[1][0]) ans[0]++;
		for (int i = 0; i < k; i++)
			printf("%d%c", ans[i], i == k-1 ? '\n' : ' ');
	}
}SA;

int K;
char str[maxn];

int main () {
	while (scanf("%s%d", str, &K) == 2) {
		int n = strlen(str);
		SA.init();
		for (int i = 0; i < n; i++) SA.insert(str[i]);
		SA.get_tuopu();
		SA.solve(K);
	}
	return 0;
}

void SAM::insert(char ch) {
	newNode(step[last] + 1);
	int v = idx(ch), p = last, np = sz;

	while (p && !g[p][v]) {
		g[p][v] = np;
		p = pre[p];
	}

	if (p) {
		int q = g[p][v];
		if (step[q] == step[p] + 1)
			pre[np] = q;
		else {
			newNode(step[p] + 1);
			int nq = sz;
			for (int j = 0; j < SIGMA_SIZE; j++) g[nq][j] = g[q][j];

			pre[nq] = pre[q];
			pre[np] = pre[q] = nq;

			while (p && g[p][v] == q) {
				g[p][v] = nq;
				p = pre[p];
			}
		}
	} else
		pre[np] = 1;
	last = np;
}

void SAM::get_tuopu() {
	for (int i = 0; i <= sz; i++) cnt[i] = 0;
	for (int i = 1; i <= sz; i++) cnt[step[i]]++;
	for (int i = 1; i <= sz; i++) cnt[i] += cnt[i-1];
	for (int i = 1; i <= sz; i++) pos[cnt[step[i]]--] = i; 
}

void SAM::get_right(char* str) {
	int p = 1, n = strlen(str);
	for (int i = 0; i <= sz; i++) right[i] = 0;

	for (int i = 0; i < n; i++) {
		int v = idx(str[i]);
		p = g[p][v];
		right[p]++;
	}

	for (int i = sz; i; i--) {
		int u = pos[i];
		right[pre[u]] += right[u];
	}
}

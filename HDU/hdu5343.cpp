#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef unsigned long long ll;
const int maxn = 90005;
const int SIGMA_SIZE = 26;

struct SAM {
	int sz, last;
	int g[maxn<<1][SIGMA_SIZE], pre[maxn<<1], step[maxn<<1];
	int pos[maxn<<1];
	ll tot, right[maxn<<1], cnt[maxn<<1], dp[maxn<<1];

	void newNode(int s) {
		step[++sz] = s;
		pre[sz] = 0;
		memset(g[sz], 0, sizeof(g[sz]));
	}

	int idx(char ch) { return ch -'a'; }

	void init() {
		tot = 0;
		sz = 0, last = 1;
		newNode(0);
	}

	void insert(char ch);
	void get_tuopu();
	void get_right(char* str);

	ll solve(ll* c);
	void presolve(ll* c);
}SA, SB;

char a[maxn], b[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s%s", a, b);
		int na = strlen(a); SA.init();
		for (int i = 0; i < na; i++) SA.insert(a[i]);
		int nb = strlen(b); SB.init();
		for (int i = nb-1; i >= 0; i--) SB.insert(b[i]);

		ll c[30];
		memset(c, 0, sizeof(c));
		SB.presolve(c);
		printf("%llu\n", SA.solve(c));
	}
	return 0;
}

void SAM::presolve(ll* c) {
	get_tuopu();
	memset(dp, 0, sizeof(dp));
	dp[1] = 1;

	for (int i = 1; i <= sz; i++) {
		int u = pos[i];
		for (int j = 0; j < SIGMA_SIZE; j++) {
			int v = g[u][j];
			if (v == 0) continue;
			c[j] += dp[u];
			dp[v] += dp[u];
		}
	}
}

ll SAM::solve(ll* c) {
	get_tuopu();

	memset(dp, 0, sizeof(dp));
	dp[1] = 1;

	ll ret = 0;
	for (int i = 1; i <= sz; i++) {
		int u = pos[i];
		for (int j = 0; j < SIGMA_SIZE; j++) {
			int v = g[u][j];
			if (v == 0) ret += dp[u] * c[j];
			else dp[v] += dp[u];
		}
		ret += dp[u];
	}
	return ret;
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

	tot += step[np] - step[pre[np]];
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

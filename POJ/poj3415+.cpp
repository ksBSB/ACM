#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
const int SIGMA_SIZE = 52;

struct SAM {
	int sz, last;
	int g[maxn<<1][SIGMA_SIZE], pre[maxn<<1], step[maxn<<1];
	int pos[maxn<<1], right[maxn<<1], cnt[maxn<<1];

	void newNode(int s) {
		step[++sz] = s;
		pre[sz] = 0;
		memset(g[sz], 0, sizeof(g[sz]));
	}

	int idx(char ch) { 
		if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 26;
		return ch -'a';
	}

	void init() {
		sz = 0, last = 1;
		newNode(0);
	}

	void insert(char ch);
	void get_tuopu();
	void get_right(char* str);
	ll solve (int k, char* str) {
		ll ret = 0;
		memset(cnt, 0, sizeof(cnt));
		int n = strlen(str), p = 1, lcs = 0;

		for (int i = 0; i < n; i++) {
			int v = idx(str[i]);

			if (g[p][v]) lcs++, p = g[p][v];
			else {
				while (p && !g[p][v]) p = pre[p];
				if (p) lcs = step[p] + 1, p = g[p][v];
				else lcs = 0, p = 1;
			}

			if (lcs >= k) {
				ret += 1LL * (lcs - max(k, step[pre[p]] + 1) + 1) * right[p];
				if (k <= step[pre[p]]) cnt[pre[p]]++;
			}
		}

		for (int i = sz; i; i--) {
			p = pos[i];
			ret += 1LL * cnt[p] * (step[p] - max(k, step[pre[p]] + 1) + 1) * right[p];
			if (k <= step[pre[p]]) cnt[pre[p]] += cnt[p];
		}
		return ret;
	}
}SA;

int K;
char a[maxn], b[maxn];

int main () {
	while (scanf("%d", &K) == 1 && K) {
		SA.init();
		scanf("%s%s", a, b);
		int n = strlen(a);
		for (int i = 0; i < n; i++)
			SA.insert(a[i]);
		SA.get_tuopu();
		SA.get_right(a);

		printf("%lld\n", SA.solve(K, b));
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

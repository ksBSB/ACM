#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 300005;
const int SIGMA_SIZE = 26;

struct SAM {
	int sz, last;
	int g[maxn<<1][SIGMA_SIZE], pre[maxn<<1], step[maxn<<1];
	int pos[maxn<<1], right[maxn<<1], cnt[maxn<<1];
	int ridx[maxn<<1];

	void newNode(int s) {
		step[++sz] = s;
		pre[sz] = 0;
		memset(g[sz], 0, sizeof(g[sz]));
	}

	int idx(char ch) { return ch -'a'; }

	void init() {
		sz = 0, last = 1;
		newNode(0);
	}

	void insert(char ch);
	void get_tuopu();
	void get_right(char* str);


	int f[maxn<<1], sub[maxn<<1];
	int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

	ll ans[maxn];
	void solve(int m, int* op, int k);
}SA;

int N, M, K, op[maxn];
char str[maxn];

void init () {
	SA.init();

	scanf("%s", str);
	for (int i = 0; i < N; i++)
		SA.insert(str[i]);

	char tmp[5];
	for (int i = 1; i <= M; i++) {
		scanf("%d", &op[i]);
		if (op[i] == 1) {
			scanf("%s", tmp);
			str[N++] = tmp[0];
			SA.insert(tmp[0]);
		}
	}
	str[N] = '\0';
	SA.get_tuopu();
	SA.get_right(str);
}

int main () {
	while (scanf("%d%d%d", &N, &M, &K) == 3) {
		init();
		SA.solve(M, op, K);
	}
	return 0;
}

void SAM::solve(int m, int* op, int k) {
	ll ret = 0;
	for (int i = 0; i < sz; i++) {
		int u = pos[i];
		if (right[u] >= k) ret += step[u] - step[pre[u]];
	}
	for (int i = 0; i <= sz; i++) f[i] = i, sub[i] = 0;

	for (int i = m; i; i--) {
		if (op[i] == 2) ans[i] = ret;
		else {
			int p = ridx[N--];
			int fp = find(p);
			while (fp && right[fp] < k) {
				p = f[fp] = pre[fp];
				fp = find(p);
			}

			if (fp == 0) continue;
			sub[fp]++;
			while (fp && right[fp] - sub[fp] < k) {
				ret -= step[fp] - step[pre[fp]];
				p = f[fp] = pre[fp];
				sub[pre[fp]] += sub[fp];
				fp = find(p);
			}
		}
	}
	for (int i = 1; i <= m; i++)
		if (op[i] == 2) printf("%lld\n", ans[i]);
}

void SAM::insert(char ch) {
	newNode(step[last] + 1);
	int v = idx(ch), p = last, np = sz;
	ridx[N] = np; //

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

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e6 + 5;
const int SIGMA_SIZE = 26;

struct SAM {
	int sz, last;
	int g[maxn<<1][SIGMA_SIZE], pre[maxn<<1], step[maxn<<1];
	int pos[maxn<<1], right[maxn<<1], cnt[maxn<<1], mark[maxn<<1];

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

	void presolve() {
		for (int i = 1; i <= sz; i++) {
			int u = pos[i];
			printf("%d ", right[u]);
		}
		printf("\n");
	}

	int solve(char* str, int k, int mk) {
		int ret = 0;
		int p = 1, n = strlen(str), lcs = 0;


		for (int i = 0; i < n; i++) {
			int v = idx(str[i]);
			if (g[p][v]) { lcs++, p = g[p][v]; }
			else {
				while (p && g[p][v] == 0) p = pre[p];

				if (p) lcs = step[p] + 1, p = g[p][v];
				else p = 1, lcs = 0;
			}

			if (lcs >= k) {
				while (pre[p] && step[pre[p]] >= k) p = pre[p], lcs = step[p];
				if (mark[p] != mk) {
					mark[p] = mk;
					ret += right[p];
				}
			}
		}
		return ret;
	}
}SA;

char str[maxn], a[maxn];

int main () {
	scanf("%s", str);
	SA.init();

	int n = strlen(str);
	for (int i = 0; i < n; i++) SA.insert(str[i]);
	SA.get_tuopu();
	SA.get_right(str);

	scanf("%d", &n);
	for (int k = 1; k <= n; k++) {
		scanf("%s", a);
		int n = strlen(a), p = 0;
		for (int i = 0; i < n; i++) str[p++] = a[i];
		for (int i = 0; i < n-1; i++) str[p++] = a[i];
		str[p++] = '\0';

		printf("%d\n", SA.solve(str, n, k));
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

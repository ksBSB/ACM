#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 100005;
const int SIGMA_SIZE = 26;
const int inf = 0x3f3f3f3f;

struct SAM {
	int sz, last;
	int g[maxn<<1][SIGMA_SIZE], pre[maxn<<1], step[maxn<<1];
	int lcs[maxn<<1], tlcs[maxn<<1];

	void newNode(int s) {
		step[++sz] = s;
		pre[sz] = 0;
		lcs[sz] = s;
		memset(g[sz], 0, sizeof(g[sz]));
	}

	int idx(char ch) { return ch -'a'; }

	void init() {
		sz = 0, last = 1;
		newNode(0);
		memset(tlcs, 0, sizeof(tlcs));
	}

	void insert(char ch) {
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

	void match(char* str) {
		memset(tlcs, 0 , sizeof(tlcs));
		int n = strlen(str), p = 1, ans = 0;
		for (int i = 0; i < n; i++) {
			int v = idx(str[i]);
			if (g[p][v]) p = g[p][v], ans++;
			else {
				while (p && g[p][v] == 0) p = pre[p];
				if (p) ans = step[p] + 1, p = g[p][v];
				else ans = 0, p = 1;
			}

			tlcs[p] = max(tlcs[p], ans);
		}
		for (int i = 0; i < sz; i++) {
			int u = id[i];
			lcs[u] = min(lcs[u], tlcs[u]);
			int v = pre[u];
			//printf("%d %d %d!", u, v, tlcs[u]);
			tlcs[v] = max(tlcs[v], tlcs[u]);
		}
		//printf("\n");
	}

	int solve() {
		int ans = 0;
		for (int i = 1; i <= sz; i++) {
			//printf("%d ", lcs[i]);
			ans = max(ans, lcs[i]);
		}
		//printf("\n");
		return ans;
	}

	int du[maxn<<1], id[maxn<<1];
	void topu() {
		memset(du, 0, sizeof(du));
		for (int i = 1; i <= sz; i++)
			du[pre[i]]++;

		int head = 0, rear = 0;
		for (int i = 1; i <= sz; i++)
			if (du[i] == 0) id[rear++] = i;

		while (head < rear) {
			int u = id[head++];
			du[pre[u]]--;
			if (du[pre[u]] == 0 && pre[u])
				id[rear++] = pre[u];
		}
	}
}SA;

char str[20][maxn];

int main () {
	int N = 0;
	while (gets(str[N]) != NULL) N++;

	SA.init();
	int len = strlen(str[0]);
	for (int i = 0; i < len; i++) SA.insert(str[0][i]);

	SA.topu();
	for (int i = 1; i < N; i++) SA.match(str[i]);
	printf("%d\n", SA.solve());
	return 0;
}

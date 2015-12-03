#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 20005;
const int SIGMA_SIZE = 26;

struct SAM {
	int sz, last;
	int g[maxn<<1][SIGMA_SIZE], pre[maxn<<1], step[maxn<<1];

	void newNode(int s) {
		step[++sz] = s;
		pre[sz] = 0;
		memset(g[sz], 0, sizeof(g[sz]));
	}

	int idx(char ch) { return ch - 'a'; }

	void init () {
		sz = 0, last = 1;
		newNode(0);
	}

	void insert(char ch) {
		newNode(step[last]+1);
		int c = idx(ch);
		int p = last, np = sz;

		while (p && !g[p][c]) {
			g[p][c] = np;
			p = pre[p];
		}

		if (p) {
			int q = g[p][c];
			if (step[q] == step[p] + 1) {
				pre[np] = q;
			} else {
				newNode(step[p] + 1);
				int nq = sz;
				for (int j = 0; j < SIGMA_SIZE; j++)
					g[nq][j] = g[q][j];
				pre[nq] = pre[q];
				pre[np] = pre[q] = nq;

				while (p && g[p][c] == q) {
					g[p][c] = nq;
					p = pre[p];
				}
			}
		} else
			pre[np] = 1;

		last = np;
	}

	int solve(int n) {
		int u = 1;
		while (n--) {
			for (int i = 0; i < SIGMA_SIZE; i++) if (g[u][i]) {
				u = g[u][i];
				break;
			}
		}
		return step[u];
	}
}sam;

char str[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s", str);
		int n = strlen(str);
		sam.init();
		for (int k = 0; k < 2; k++) {
			for (int i = 0; i < n; i++)
				sam.insert(str[i]);
		}
		int k = sam.solve(n);
		printf("%d\n", k - n + 1);
	}
	return 0;
}

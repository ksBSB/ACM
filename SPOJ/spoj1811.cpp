#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 250005;
const int SIGMA_SIZE = 26;

struct SAM {
	int sz, last;
	int g[maxn<<1][SIGMA_SIZE], pre[maxn<<1], step[maxn<<1];
	int tot;

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

	int insert(char ch) {
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
		return tot;
	}

	int solve(char* str) {
		int n = strlen(str), p = 1, ans = 0, lcs = 0;

		for (int i = 0; i < n; i++) {
			int v = idx(str[i]);
			if (g[p][v]) p = g[p][v], lcs++;
			else {
				while (p && g[p][v] == 0) p = pre[p];
				if (p) lcs = step[p] + 1, p = g[p][v];
				else lcs = 0, p = 1;
			}
			ans = max(ans, lcs);
		}
		return ans;
	}
}SA;

char a[maxn], b[maxn];

int main () {
	while (scanf("%s%s", a, b) == 2) {
		int n = strlen(a);
		SA.init();
		for (int i = 0; i < n; i++) SA.insert(a[i]);
		printf("%d\n", SA.solve(b));
	}
	return 0;
}

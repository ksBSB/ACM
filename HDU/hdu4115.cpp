#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 10005;

struct TwoSAT {
	int n, s[maxn<<1], c;
	bool mark[maxn<<1];
	vector<int> g[maxn<<1];

	void init (int n) {
		this->n = n;
		memset(mark, false, sizeof(mark));
		for (int i = 0; i < n*2; i++) g[i].clear();
	}

	void addClause(int x, int xval, int y, int yval) { // (sx || sy)
		x = x * 2 + xval;
		y = y * 2 + yval;
		g[x^1].push_back(y);
		g[y^1].push_back(x);
	}

	bool dfs (int x) {
		if (mark[x^1]) return false;
		if (mark[x]) return true;
		mark[x] = true;
		s[c++] = x;

		for (int i = 0; i < g[x].size(); i++)
			if (!dfs(g[x][i])) return false;
		return true;
	}

	bool solve () {
		for (int i = 0; i < n*2; i += 2) {
			if (!mark[i] && !mark[i+1]) {
				c = 0;
				if (!dfs(i)) {
					while (c) mark[s[--c]] = false;
					if (!dfs(i+1)) return false;
				}
			}
		}
		return true;
	}
}solver;

int N, M, A[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= N; i++) { scanf("%d", &A[i]); A[i]--; }
		solver.init(N);

		int a, b, k;
		while (M--) {
			scanf("%d%d%d", &a, &b, &k);
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					int u = (A[a] + i) % 3, v = (A[b] + j) % 3;

					if (u != v && k == 0) solver.addClause(a-1, i^1, b-1, j^1);
					if (u == v && k) solver.addClause(a-1, i^1, b-1, j^1);
				}
			}
		}
		printf("Case #%d: %s\n", kcas, solver.solve() ? "yes" : "no");
	}
	return 0;
}

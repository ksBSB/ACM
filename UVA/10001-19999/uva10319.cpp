#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1005;

struct TwoSAT {
	int n, c, S[maxn * 2];
	vector<int> G[maxn * 2];
	bool mark[maxn * 2];

	void init (int n) {
		this->n = n;
		memset(mark, 0, sizeof(mark));
		for (int i = 0; i < 2 * n; i++) G[i].clear();
	}

	void addClause(int x, int xflag, int y, int yflag) {
		x = x * 2 + xflag;
		y = y * 2 + yflag;
		G[x^1].push_back(y);
		G[y^1].push_back(x);
	}
	
	bool dfs(int u) {
		if (mark[u^1]) return false;
		if (mark[u]) return true;
		mark[u] = true;
		S[c++] = u;

		for (int i = 0; i < G[u].size(); i++)
			if (!dfs(G[u][i])) return false;
		return true;
	}

	bool solve () {
		for (int i = 0; i < 2*n; i += 2) {
			if (!mark[i] && !mark[i+1]) {
				c = 0;
				if (!dfs(i)) {
					while (c) mark[S[--c]] = false;
					if (!dfs(i+1)) return false;
				}
			}
		}
		return true;
	}
}solver;

void init () {
	int R, C, N, r1, c1, r2, c2;
	scanf("%d%d%d", &R, &C, &N);
	solver.init(R + C);

	while (N--) {
		scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
		r1--, r2--, c1--, c2--;
		c1 += R;
		c2 += R;
		int rflag = c1 < c2, cflag = r1 < r2;
		if (r1 == r2) {
			solver.addClause(r1, rflag, r2, rflag);
		} else if (c1 == c2) {
			solver.addClause(c1, cflag, c2, cflag);
		} else {
			solver.addClause(r1, rflag, r2, rflag);
			solver.addClause(r1, rflag, c1, cflag);
			solver.addClause(c2, cflag, r2, rflag);
			solver.addClause(c2, cflag, c1, cflag);
		}
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%s\n", solver.solve() ? "Yes" : "No");
		/*
		for (int i = 0; i < solver.n; i++) {
			if (solver.mark[i*2]) printf("<-");
			else printf("->");
			printf("\n");
		}
		*/
	}
	return 0;
}

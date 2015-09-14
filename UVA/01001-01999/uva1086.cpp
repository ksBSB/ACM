#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 105;

struct TwoSAT {
	int n, S[maxn * 2], C;
	bool mark[maxn * 2], must[maxn * 2];
	vector<int> G[maxn * 2];

	void init (int n) {
		this->n = n;
		memset(must, 0, sizeof(must));
		for (int i = 0; i < n*2; i++) G[i].clear();
	}

	void clear() { memcpy(mark, must, sizeof(must)); }

	void addClause(int x, int xflag, int y, int yflag) {
		x = x * 2 + xflag;
		y = y * 2 + yflag;
		G[x^1].push_back(y);
		G[y^1].push_back(x);
	}

	void draw(int u) {
		must[u] = true;
		for (int i = 0; i < G[u].size(); i++)
			if (!must[G[u][i]]) draw(G[u][i]);
	}

	bool dfs (int u) {
		if (mark[u^1]) return false;
		if (mark[u]) return true;
		mark[u] = true;
		S[C++] = u;

		for (int i = 0; i < G[u].size(); i++)
			if (!dfs(G[u][i])) return false;
		return true;
	}

	bool solve () {
		for (int i = 0; i < 2*n; i += 2) {
			if (mark[i] && mark[i+1]) return false;
			if (!mark[i] && !mark[i+1]) {
				C = 0;
				if (!dfs(i)) {
					while (C) mark[S[--C]] = false;
					if (!dfs(i+1)) return false;
				}
			}
		}
		return true;
	}
}solver;

int N, M, T[maxn];

void init () {
	int k, x[10], y[10];
	char s[10];

	solver.init(N);
	memset(T, 0, sizeof(T));

	while (M--) {
		scanf("%d", &k);
		for (int i = 0; i < k; i++) {
			scanf("%d%s", &x[i], s);
			x[i]--; y[i] = s[0] == 'y' ? 0 : 1;
		}

		if (k >= 3) {
			for (int i = 0; i < k; i++)
				for (int j = i + 1; j < k; j++)
					solver.addClause(x[i], y[i], x[j], y[j]);
		} else {
			for (int i = 0; i < k; i++)
				solver.must[x[i]*2+y[i]] = true;
		}
	}
}

int main () {
	int cas = 1;
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init();

		for (int i = 0; i < 2*N; i++)
			if (solver.must[i]) solver.draw(i);

		for (int i = 0; i < 2*N; i += 2) {
			if (solver.must[i] || solver.must[i+1]) continue;
			solver.clear();
			solver.mark[i] = true;
			bool flag1 = solver.solve();

			solver.clear();
			solver.mark[i+1] = true;
			bool flag2 = solver.solve();
			if (flag1 && flag2) T[i/2] = 1;
		}

		solver.clear();
		printf("Case %d: ", cas++);
		if (!solver.solve()) printf("impossible\n");
		else {
			for (int i = 0; i < N; i++) {
				if (T[i]) printf("?");
				else if (solver.mark[i*2]) printf("y");
				else printf("n");
			}
			printf("\n");
		}
	}
	return 0;
}

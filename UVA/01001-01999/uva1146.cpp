#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 2005;

int N, T[maxn][2];

struct TwoSAT {
	int n;
	vector<int> G[maxn * 2];
	bool mark[maxn * 2];
	int S[maxn * 2], c;

	bool dfs (int u) {
		if (mark[u^1]) return false;
		if (mark[u]) return true;
		mark[u] = true;
		S[c++] = u;
		for (int i = 0; i < G[u].size(); i++)
			if (!dfs(G[u][i])) return false;
		return true;
	}

	void init (int n) {
		this->n = n;
		for (int i = 0; i < n*2; i++) G[i].clear();
		memset(mark, 0, sizeof(mark));
	}

	void addClause(int u, int uflag, int v, int vflag) {
		u = u * 2 + uflag;
		v = v * 2 + vflag;
		G[u^1].push_back(v);
		G[v^1].push_back(u);
	}

	bool solve () {
		for (int i = 0; i < n*2; i += 2) {
			if (!mark[i] && !mark[i+1]) {
				c = 0;
				if (!dfs(i)) {
					while (c > 0) mark[S[--c]] = false;
					if (!dfs(i+1)) return false;
				}
			}
		}
		return true;
	}
}solver;

bool judge (int d) {
	solver.init(N);
	for (int i = 0; i < N; i++) for (int a = 0; a < 2; a++) {
		for (int j = i+1; j < N; j++) for (int b = 0; b < 2; b++) {
			if (abs(T[i][a] - T[j][b]) < d) solver.addClause(i, a^1, j, b^1);
		}
	}
	return solver.solve();
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		int L = 0, R = 0;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < 2; j++) {
				scanf("%d", &T[i][j]);
				R = max(R, T[i][j]);
			}

		while (L < R) {
			int mid = L + ((R - L + 1) >> 1);
			if (judge(mid)) L = mid;
			else R = mid - 1;;
		}
		printf("%d\n", L);
	}
	return 0;
}

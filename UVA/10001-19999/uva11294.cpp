#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 205;

struct TwoSAT {
	int n;
	bool mark[maxn * 2];
	int S[maxn * 2], c;
	vector<int> G[maxn * 2];

	void init (int n) {
		this->n = n;
		for (int i = 0; i < n*2;i++) G[i].clear();
		memset(mark, 0, sizeof(mark));
	}

	void addClause (int x, int xval, int y, int yval) {
		x = x * 2 + xval;
		y = y * 2 + yval;
		G[x^1].push_back(y);
		G[y^1].push_back(x);
	}

	bool dfs (int x) {
		if (mark[x^1]) return false;
		if (mark[x]) return true;
		mark[x] = true;
		S[c++] = x;
		for (int i = 0; i < G[x].size(); i++)
			if (!dfs(G[x][i])) return false;
		return true;
	}

	bool solve () {
		if (!dfs(0)) return false;
		for (int i = 2; i < n*2; i += 2) {
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

int N, M;

inline int idx(char ch) { return ch == 'w' ? 0 : 1; }

void init () {
	solver.init(N);
	int u, v;
	char cu[5], cv[5];
	while (M--) {
		scanf("%d%s%d%s", &u, cu, &v, cv);
		solver.addClause(u, idx(cu[0]), v, idx(cv[0]));
	}
}

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init ();
		if (solver.solve()) {
			for (int i = 1; i < N; i++) {
				printf("%d", i);
				if (solver.mark[i*2]) printf("w");
				else printf("h");
				printf("%c", i == N-1 ? '\n' : ' ');
			}
		} else
			printf("bad luck\n");
	}
	return 0;
}

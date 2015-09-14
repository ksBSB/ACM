#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 100005;

struct TwoSAT {
	int n;
	bool mark[maxn * 2];
	vector<int> G[maxn * 2];
	int S[maxn * 2], c;

	void init (int n) {
		this->n = n;
		for (int i = 0; i < n * 2; i++) G[i].clear();
		memset(mark, 0, sizeof(mark));
	}

	void addClause (int u, int uflag, int v, int vflag) {
		u = u * 2 + uflag;
		v = v * 2 + vflag;
		G[u^1].push_back(v);
		G[v^1].push_back(u);
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
		for (int i = 0; i < n * 2; i += 2) {
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

int N, M, S, W[maxn];

int IDX(int u) { return W[u] * N < S ? 1 : 0; }
int BW(int u) { if (solver.mark[u*2+1]) return 2; else return IDX(u); }

void init () {
	S = 0;
	for (int i = 0; i < N; i++) {
		scanf("%d", &W[i]);
		S += W[i];
	}
	solver.init(N);

	int u, v;
	while (M--) {
		scanf("%d%d", &u, &v);
		u--, v--;
		solver.addClause(u, 0, v, 0);
		if (IDX(u) == IDX(v))
			solver.addClause(u, 1, v, 1);
	}
}

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init ();
		if (solver.solve()) {
			for (int i = 0; i < N; i++)
				printf("%c\n", 'A' + BW(i));
		} else
			printf("No solutio.\n");
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1e4 + 5;

struct TwoSAT {
	int n, s[maxn * 4], c;
	bool mark[maxn * 4], must[maxn * 4];
	vector<int> g[maxn * 4];

	void init (int n) {
		this->n = n;
		memset(mark, 0, sizeof(mark));
		memset(must, 0, sizeof(must));
		for (int i = 0; i < 4 * n; i++) g[i].clear();
	}

	void addLink(int x, int y) { g[x].push_back(y); }

	bool dfs (int u) {
		for (int i = 1; i <= 3; i++)
			if (mark[u^i]) return false;
		if (must[u]) return false;
		if (mark[u]) return true;
		mark[u] = true;
		s[c++] = u;
		for (int i = 0; i < g[u].size(); i++)
			if (!dfs(g[u][i])) return false;
		return true;
	}

	void draw(int u) {
		if (must[u]) return;
		must[u] = true;
		for (int i = 0; i < g[u].size(); i++)
			draw(g[u][i]);
	}

	bool solve () {
		for (int i = 0; i < 4 * n; i += 4) {
			if (!mark[i] && !mark[i+1] && !mark[i+2] && !mark[i+3]) {
				bool flag = true;
				c = 0;
				for (int k = 0; k < 4 && flag; k++) {
					if (must[i+k]) continue;
					while (c) mark[s[--c]] = false;
					if (dfs(i+k)) flag = false;
				}
				if (flag) return false;
			}
		}
		return true;
	}
}solver;

bool flag;
int N, M, a[maxn];
char S[maxn];

inline int idx(char c) {
	if (c == 'A') return 0;
	else if (c == 'G') return 1;
	else if (c == 'T') return 2;
	else return 3;
}

void addClause(int p, int q) {
	for (int i = 0; i < 4; i++) {
		solver.addLink(p * 4 + i, q * 4 + i);
		solver.addLink(q * 4 + i, p * 4 + i);
	}
}

void init () {
	solver.init(N);
	scanf("%s", S);

	int k, x;
	while (M--) {
		scanf("%d%*c", &k);
		for (int i = 0; i < k; i++) scanf("%d", &a[i]);
		for (int i = 0; i < k/2; i++) addClause(a[i], a[k-i-1]);
	}

	// 每个位置不能连续变换两次
	for (int i = 0; i < N; i++) {
		int v = (idx(S[i]) + 2) % 4;
		solver.draw(i*4 + v);
	}

	// 相邻位置只能变化一个
	for (int i = 1; i < N; i++) {
		int u = idx(S[i-1]), v = idx(S[i]);
		for (int j = 1; j < 4; j++) {
			int tu = (u + j) % 4, tv = (v + j) % 4;
			solver.addLink((i-1)*4+tu, i*4+v);
			solver.addLink(i*4+tv, (i-1)*4+u);
		}
	}
}

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init();
		printf("%s\n", solver.solve() ? "YES" : "NO");
		/*
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < 4; j++) {
				if (solver.mark[4*i+j]) {
					printf(" (%d,%d)", i, j);
					break;
				}
			}
		}
		printf("\n");
		*/
	}
	return 0;
}

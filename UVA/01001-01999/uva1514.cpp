#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 1e6 + 5;
const int maxm = 1005;
const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int inv[4] = {2, 3, 0, 1};

struct TwoSAT {
	int n, s[maxn * 2], c;
	vector<int> g[maxn * 2];
	bool mark[maxn * 2];

	void init (int n) {
		this->n = n;
		memset(mark, 0, sizeof(mark));
		for (int i = 0; i < 2*n; i++) g[i].clear();
	}

	void addClause(int x, int xflag, int y, int yflag) {
		x = x * 2 + xflag;
		y = y * 2 + yflag;
		g[x^1].push_back(y);
		g[y^1].push_back(x);
	}

	bool dfs (int u) {
		if (mark[u^1]) return false;
		if (mark[u]) return true;
		mark[u] = true;
		s[c++] = u;
		for (int i = 0; i < g[u].size(); i++) 
			if (!dfs(g[u][i])) return false;
		return true;
	}

	bool solve () {
		for (int i = 0; i < 2 * n; i += 2) {
			if (mark[i] && mark[i+1]) return false;
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

bool flag;
int R, C, B, W, idx, id[maxm][maxm];
char G[maxm][maxm];
vector<pii> M;

inline int ID(int x, int y) {
	int& i = id[x][y];
	if (i == -1) i = idx++;
	return i;
}

void init () {
	flag = true;
	B = W = idx = 0;
	memset(id, -1, sizeof(id));

	scanf("%d%d", &R, &C);
	for (int i = 1; i <= R; i++) {
		scanf("%s", G[i]+1);
		for (int j = 1; j <= C; j++) {
			if (G[i][j] == 'B') {
				B++;
				for (int k = 0; k < 4; k++)
					ID(i + dir[k][0], j + dir[k][1]);
			}
			if (G[i][j] == 'W') {
				W++;
				ID(i, j);
			}
		}
	}
	solver.init(idx * 4);

	// 处理节点关系
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (G[i][j] == 'B') {
				// 每个黑点两侧有且只有一个所属白点
				int up = ID(i + dir[0][0], j + dir[0][1]) * 4 + inv[0];
				int right = ID(i + dir[1][0], j + dir[1][1]) * 4 + inv[1];
				int down = ID(i + dir[2][0], j + dir[2][1]) * 4 + inv[2];
				int left = ID(i + dir[3][0], j + dir[3][1]) * 4 + inv[3];
				solver.addClause(up, 0, down, 0);
				solver.addClause(up, 1, down, 1);
				solver.addClause(right, 0, left, 0);
				solver.addClause(right, 1, left, 1);
			} else if (G[i][j] == 'W') {
				// 每个白点只能属于一个黑点
				for (int k = 0; k < 4; k++) {
					int u = ID(i, j) * 4 + k;
					for (int t = 1; t <= 3; t++) {
						int v =  ID(i, j) * 4 + (k+t)%4;
						solver.g[u*2].push_back(v*2+1);
					}
				}
			}
		}
	}

	// 找出已经确定的条件
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (G[i][j] == 'B') {
				for (int k = 0; k < 4; k++) {
					int x = i + dir[k][0], y = j + dir[k][1];
					// 不是白点，不存在所属关系
					if (x <= 0 || x > R || y <= 0 || y > C || G[x][y] != 'W') {
						int u = ID(x, y) * 4;
						for (int t = 0; t < 4; t++)
							if (!solver.dfs((u+t)*2+1)) flag = false;
					}
				}
			} else if (G[i][j] == 'W') {
				for (int k = 0; k < 4; k++) {
					int x = i + dir[k][0], y = j + dir[k][1];
					if (x <= 0 || x > R || y <= 0 || y > C || G[x][y] != 'B') {
						// 白点旁不是黑点，这个方向的从属关系不成立
						int u = ID(i, j) * 4 + k;
						if (!solver.dfs(u*2+1)) flag = false;
					}
				}
			}
		}
	}
}

bool judge () {
	if (2 * B != W || !flag) return false;
	return solver.solve();
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%s\n", judge() ? "YES" : "NO");
	}
	return 0;
}

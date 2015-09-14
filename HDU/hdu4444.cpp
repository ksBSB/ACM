#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 250;
const int inf = 0x3f3f3f3f;
const int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
vector<int> X, Y;

int N, cx, cy, dp[maxn][maxn][4], vi[maxn][maxn][4];
int sx, sy, ex, ey, G[maxn][maxn], E[maxn][maxn][4];
struct Wall {
	int x1, y1, x2, y2;
	void input () {
		int tx1, tx2, ty1, ty2;
		scanf("%d%d%d%d", &tx1, &ty1, &tx2, &ty2);
		x1 = min(tx1, tx2) * 2; x2 = max(tx1, tx2) * 2;
		y1 = min(ty1, ty2) * 2; y2 = max(ty1, ty2) * 2;

		X.push_back(x1); X.push_back(x1+1);
		X.push_back(x2); X.push_back(x2+1);
		Y.push_back(y1); Y.push_back(y1+1);
		Y.push_back(y2); Y.push_back(y2+1);
		x1++; y1++;
	}
}W[55];

struct state {
	int x, y, d;
	state(int x = 0, int y = 0, int d = 0) {
		this->x = x;
		this->y = y;
		this->d = d;
	}
};

inline int findX(int x) {
	return lower_bound(X.begin(), X.begin() + cx, x) - X.begin();
}
inline int findY(int y) {
	return lower_bound(Y.begin(), Y.begin() + cy, y) - Y.begin();
}

void init () {
	X.clear(); Y.clear();

	sx *= 2; sy *= 2;
	ex *= 2; ey *= 2;
	X.push_back(sx); X.push_back(sx+1);
	X.push_back(ex); X.push_back(ex+1);
	Y.push_back(sy); Y.push_back(sy+1);
	Y.push_back(ey); Y.push_back(ey+1);

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		W[i].input();

	sort(X.begin(), X.end());
	sort(Y.begin(), Y.end());
	cx = unique(X.begin(), X.end()) - X.begin();
	cy = unique(Y.begin(), Y.end()) - Y.begin();

	memset(G, 0, sizeof(G));
	for (int i = 0; i < N; i++) {
		int x1 = findX(W[i].x1);
		int x2 = findX(W[i].x2);
		int y1 = findY(W[i].y1);
		int y2 = findY(W[i].y2);
		for (int x = x1; x <= x2; x++)
			for (int y = y1; y <= y2; y++)
				G[x][y] = 1;
	}

	memset(E, 0, sizeof(E));
	for (int i = 0; i < cx; i += 2) {
		for (int j = 0; j < cy; j += 2) {
			if (G[i][j] && G[i+1][j+1])
				E[i][j+1][2] = E[i+1][j][1] = 1;
			if (G[i+1][j] && G[i][j+1])
				E[i][j][3] = E[i+1][j+1][0] = 1;
		}
	}
}

int solve(int x, int y) {
	queue<state> que;
	memset(vi, 0, sizeof(vi));
	memset(dp, inf, sizeof(dp));

	for (int s = 0; s < 4; s++) {
		int p = findX(x + ((s>>1)&1));
		int q = findY(y + (s&1));

		if (G[p][q])
			continue;
		for (int i = 0; i < 4; i++) {
			que.push(state(p, q, i));
			dp[p][q][i] = 0;
			vi[p][q][i] = 1;
		}
	}

	while (!que.empty()) {
		state u = que.front(); que.pop();
		vi[u.x][u.y][u.d] = 0;

		for (int i = 0; i < 4; i++) {
			int p = u.x + dir[i][0];
			int q = u.y + dir[i][1];

			if (p < 0 || p >= cx || q < 0 || q >= cy || G[p][q])
				continue;
			int w = (i == u.d ? 0 : 1);
			if (dp[p][q][i] > dp[u.x][u.y][u.d] + w) {
				dp[p][q][i] = dp[u.x][u.y][u.d] + w;
				if (vi[p][q][i] == 0) {
					que.push(state(p, q, i));
					vi[p][q][i] = 1;
				}

				int xx = (p / 2) * 2, yy = (q / 2) * 2;
				for (int s = 0; s < 4; s++) {
					int pp = xx + ((s>>1)&1);
					int qq = yy + (s&1);

					if (E[p][q][s] || G[pp][qq]) continue;

					if (dp[pp][qq][i] <= dp[p][q][i])
						continue;

					dp[pp][qq][i] = dp[p][q][i];
					if (vi[pp][qq][i] == 0) {
						que.push(state(pp, qq, i));
						vi[pp][qq][i] = 1;
					}
				}
			}
		}
	}

	int ans = inf;
	for (int s = 0; s < 4; s++) {
		int p = findX(ex + ((s>>1)&1));
		int q = findY(ey + (s&1));
		for (int i = 0; i < 4; i++) {
			ans = min(dp[p][q][i], ans);
		}
	}
	return ans == inf ? -1 : ans;
}

int main () {
	while (scanf("%d%d%d%d", &sx, &sy, &ex, &ey) == 4 && (sx || sy || ex || ey) ) {
		init();
		printf("%d\n", solve(sx, sy));
	}
	return 0;
}

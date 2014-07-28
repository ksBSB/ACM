#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 15;
const int maxt = 210005;
const double INF = 0x3f3f3f3f3f3f3f;
const double eps = 1e-9;

int h[maxn], v[maxn], vis[maxn][maxn][maxt];
double dp[maxn][maxn][maxt], mintval, minv;
int n, m, mint, minvtime;

int N, L, sx, sy, ex, ey, st, et, dx, dy;

int gcd (int a, int b) {
	return b == 0 ? a : gcd(b, a%b);
}

void init () {
	scanf("%d%d", &N, &L);
	for (int i = 1; i <= N; i++)
		scanf("%d", &h[i]);
	for (int i = 1; i <= N; i++)
		scanf("%d", &v[i]);
	scanf("%d%d%d%d%d%d", &sx, &sy, &ex, &ey, &st, &et);

	m = 210 / gcd(L, 210);

	st *= m;
	et *= m;
	dx = (sx > ex ? -1 : 1);
	dy = (sy > ey ? -1 : 1);
}

inline double cal (int x) {
	return ((double)L / (80 - 0.03 * x * x));
}

void move (int x, int y, int t) {
	int p = x + dx;
	int q = y + dy;
	//printf("%d %d %d %lf\n", x, y, t, dp[x][y][t]);

	if (p > 0 && p <= N) {
		for (int i = 5; i <= h[y]; i += 5) {
			int ti = t + m * L * 60 / i;
			if (ti > et)
				continue;

			if (vis[p][y][ti])
				dp[p][y][ti] = min(dp[p][y][ti], dp[x][y][t] + cal(i));
			else {
				dp[p][y][ti] = dp[x][y][t] + cal(i);
				vis[p][y][ti] = 1;
			}
		}
	}

	if (q > 0 && q <= N) {
		for (int i = 5; i <= v[x]; i += 5) {
			int ti = t + m * L * 60 / i;
			if (ti > et)
				continue;

			if (vis[x][q][ti])
				dp[x][q][ti] = min(dp[x][q][ti], dp[x][y][t] + cal(i));
			else {
				dp[x][q][ti] = dp[x][y][t] + cal(i);
				vis[x][q][ti] = 1;
			}
		}
	}
}

void solve () {
	memset(vis, 0, sizeof(vis));
	dp[sx][sy][0] = 0;
	vis[sx][sy][0] = 1;

	for (int i = sx; i != ex + dx; i += dx) {
		for (int j = sy; j != ey + dy; j += dy) {
			for (int t = 0; t < et; t++) {
				if (vis[i][j][t])
					move(i, j, t);
			}
		}
	}

	mint = -1;
	minv = INF;
	for (int t = st; t <= et; t++) {
		if (vis[ex][ey][t]) {
			//printf("%d %lf\n", (int)((double)t / n + 1 - eps), dp[ex][ey][t]);
			if (mint == -1) {
				mint = (int)((double)t / m + 1 - eps);
				mintval = dp[ex][ey][t];
			}

			if (dp[ex][ey][t] < minv) {
				minv = dp[ex][ey][t];
				minvtime = (int)((double)t / m + 1 - eps);
			}
		}
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		solve();
		printf("Scenario %d:\n", i);
		if (mint == -1)
			printf("IMPOSSIBLE\n");
		else {
			printf("The earliest  arrival: %d minutes, fuel %.2lf gallons\n", mint, mintval );
			printf("The economical travel: %d minutes, fuel %.2lf gallons\n", minvtime, minv);
		}
	}
	return 0;
}

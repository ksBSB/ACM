#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;
const int N = 20005;
const int INF = 0x3f3f3f3f;

struct state {
	int id;
	int ra;
}s[N][2];

int n, m, c[N];
int dp[N][10][10], path[N][10][10][3], t[N];

inline void add (int x, int i, int re) {
	s[x][c[x]].id = i;
	s[x][c[x]].ra = re/10;
	c[x]++;
}

void init () {
	n = 0;
	scanf("%d", &m);
	memset(c, 0, sizeof(c));

	int x, re;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &x, &re);
		x++;
		n = max(n, x);
		add(x, i, re);
	}
	n++;
	add(n, m+10, 10);
	add(n, m+10, 10);
}

inline void set (int d, int p, int q, int x, int y, int sign) {
	path[d][p][q][0] = x;
	path[d][p][q][1] = y;
	path[d][p][q][2] = sign;
}

inline void cat (int d, int p) {
	if (c[d] == 0) 
		return ;

	t[s[d][0].id] = p;

	if (c[d] == 2)
		t[s[d][1].id] = 3 - p;
}

int solve () {
	memset(dp, INF, sizeof(dp));
	dp[0][1][1] = 0;

	for (int i = 1; i <= n; i++) {

		for (int x = 1; x <= 5; x++) {
			for (int y = 1; y <= 5; y++) {
				if (dp[i-1][x][y] == INF)
					continue;

				if (c[i] == 0) {
					if (dp[i][x][y] > dp[i-1][x][y]) {
						dp[i][x][y] = dp[i-1][x][y];
						set(i, x, y, x, y, 0);
					}
				} else if (c[i] == 1) {
					int p = s[i][0].ra;

					if (dp[i][p][y] > dp[i-1][x][y] + abs(x-p)*10) {
						dp[i][p][y] = dp[i-1][x][y] + abs(x-p)*10;
						set(i, p, y, x, y, 1);
					}

					if (dp[i][x][p] > dp[i-1][x][y] + abs(y-p)*10) {
						dp[i][x][p] = dp[i-1][x][y] + abs(y-p)*10;
						set(i, x, p, x, y, 2);
					}
				} else {
					int p = s[i][0].ra;
					int q = s[i][1].ra;

					if (dp[i][p][q] > dp[i-1][x][y] + (abs(x-p) + abs(y-q))*10) {
						dp[i][p][q] = dp[i-1][x][y] + (abs(x-p) + abs(y-q))*10;
						set(i, p, q, x, y, 1);
					}

					if (dp[i][q][p] > dp[i-1][x][y] + (abs(x-q) + abs(y-p))*10) {
						dp[i][q][p] = dp[i-1][x][y] + (abs(x-q) + abs(y-p))*10;
						set(i, q, p, x, y, 2);
					}
				}
			}
		}
	}

	int p = 1, q = 1;
	for (int i = n; i >= 0; i--) {
		cat(i, path[i][p][q][2]);
		int x = path[i][p][q][0];
		int y = path[i][p][q][1];
		p = x; q = y;
	}

	return dp[n][1][1] + 15 * m;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();
		printf("%d\n", solve());
		for (int i = 0; i < m; i++)
			printf("%d\n", t[i]);
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 200;
const int maxv = 20;
const int INF = 0x3f3f3f3f;
const int dir[4][3][2] = { { {0, 0}, {-1, 0}, {0, 1} },
						   { {0, 0}, {0, 1}, {1, 0} },
						   { {0, 0}, {-1, 0}, {0, -1} },
						   { {0, 0}, {0, -1}, {1, 0} }
						};

int ans;
int n, N, M, x[maxv], y[maxv], c[maxv];
int v[maxn+5][maxn+5];
char g[maxn+5][maxn+5];

inline int judge (int xi, int yi, const int d[3][2]) {

	for (int i = 0; i < 3; i++) {
		int p = xi + d[i][0];
		int q = yi + d[i][1];

		if (p <= 0 || p > N)
			continue;

		if (q <= 0 || q > M)
			continue;

		if (g[p][q] == '#')
			return 0;
	}
	return 1;
}

inline void set (int xi, int yi, const int d[3][2], int type) {
	for (int i = 0; i < 3; i++) {
		int p = xi + d[i][0];
		int q = yi + d[i][1];

		if (p <= 0 || p > N)
			continue;

		if (q <= 0 || q > M)
			continue;

		v[p][q] = type;
	}
}

void init () {
	n = 0;
	for (int i = 1; i <= N; i++)
		scanf("%s", g[i] + 1);

	for (int i = N; i; i--) {
		for (int j = 1; j <= M; j++) {
			if (g[i][j] == '.') {
				x[n] = i;
				y[n] = j;
				n++;
			}
		}
	}

	memset(c, 0, sizeof(c));
	for (int i = 0; i < n; i++)
		c[i] = judge(x[i], y[i], dir[0]);
}

/*
   int solve (int spi, int id) {

   memset(v, 0, sizeof(v));
   int ans = INF;
   for (int s = 0; s < (1<<n); s++) {

   bool flag = true;
   for (int i = 0; i < n; i++) {
   if (s&(1<<i) && (c[i] == 0 || i == spi)) {
   flag = false;
   break;
   }
   }

   if (flag) {
   int light = 0;
   int tmp = set(x[spi], y[spi], dir[id], 1);

   for (int i = 0; i < n; i++) {
   if (s&(1<<i)) {
   light++;
   tmp += set(x[i], y[i], dir[0], 1);
   }
   }

   if (tmp == n)
   ans = min(ans, light);

   memset(v, 0, sizeof(v));
   }
   }
   return ans+1;
   }
   */

void dfs (int d, int f, int cnt) {

	if (cnt >= ans)
		return;

	if (d == n) {
		ans = cnt;
		return;
	}

	if (v[x[d]][y[d]])
		dfs (d + 1, f, cnt);

	if (c[d] && d != f) {
		set(x[d], y[d], dir[0], 1);
		dfs (d + 1, f, cnt+1);
		set(x[d], y[d], dir[0], 0);
	}
}

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init();

		ans = INF;
		if (n == 0)
			ans = 0;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 4; j++) {
				if (judge (x[i], y[i], dir[j])) {
					memset(v, 0, sizeof(v));

					set(x[i], y[i], dir[j], 1);

					dfs(0, i, 1);

					set(x[i], y[i], dir[j], 0);
				}
			}
		}

		if (ans == INF)
			printf("-1\n");
		else
			printf("%d\n", ans);
	}
	return 0;
}

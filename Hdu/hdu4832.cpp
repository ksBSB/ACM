#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
typedef long long ll;

const int N = 1010;
const ll MOD = 9999991;

int n, m, k, x, y;
ll l[N], r[N], g[N][N*2], c[N][N];

void cat (ll* a, int x, int t) {
	memset(g, 0, sizeof(g));
	g[0][k] = 1;

	int up = k-(x-1);
	int down = k+(t-x);

	for (int i = 1; i <= k; i++) {
		for (int j = up; j <= down; j++) {
			if (g[i-1][j]) {
				if (j != up) {
					g[i][j-1] = (g[i][j-1] + g[i-1][j]) % MOD;
					if (j != up+1)
						g[i][j-2] = (g[i][j-2] + g[i-1][j]) % MOD;
				}

				if (j != down) {
					g[i][j+1] = (g[i][j+1] + g[i-1][j]) % MOD;
					if (j != down-1)
						g[i][j+2] = (g[i][j+2] + g[i-1][j]) % MOD;
				}
			}
			a[i-1] = (a[i-1] + g[i-1][j]) % MOD;
		}
	}

	for (int i = up; i <= down; i++)
		a[k] = (a[k] + g[k][i]) % MOD;
}

void input () {
	for (int i = 0; i < N; i++) {
		c[i][0] = c[i][i] = 1;
		for (int j = 0; j < i; j++)
			c[i][j] = (c[i-1][j-1] + c[i-1][j]) % MOD;
	}
}

void init () {
	//scanf("%d%d%d%d%d", &n, &m, &k, &x, &y);
	cin >> n >> m >> k >> x >> y;
	memset(l, 0, sizeof(l));
	memset(r, 0, sizeof(r));
	cat(l, x, n);
	cat(r, y, m);
}

ll solve () {
	ll ans = 0;
	for (int i = 0; i <= k; i++)
		ans = (ans + (l[i] * r[k-i]) % MOD * c[k][i])%MOD;

	return ans;
}

int main () {
	input();
	int cas;
	cin >> cas;
	for (int i = 1; i <= cas; i++) {
		init();
		//printf("Case #%d:\n%lld\n", i, solve());
		cout << "Case #" << i << ":" << endl;
		cout << solve() << endl;
	}
	return 0;
}

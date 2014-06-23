#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 20;
const int M = 1005;

ll A, B, n, a[N], dp[N][M][2][2];

void del (ll u, ll* p) {
	ll& c = p[0];
	c = 0;

	while (u) {
		p[++c] = u % 10;
		u /= 10;
	}

	if (c == 0)
		p[++c] = 0;

	for (int i = 1; i <= c / 2; i++)
		swap(p[i], p[c-i+1]);
}

ll cat (ll u) {

	if (u == 0)
		return 1;

	int s = 0;
	ll f[N][N][2];
	memset(f, 0, sizeof(f));

	for (int i = 1; i <= a[0]; i++) {
		
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 10; k++) {
				f[i][j][1] += f[i-1][k][1];
				if (j)
					f[i][j][0] += f[i-1][k][0];
				else
					f[i][j][1] += f[i-1][k][0];
			}
		}

		if (a[i] == 0)
			s = 1;
		else if (i > 1)
			f[i][0][1]++;

		for (int j = 1; j < a[i]; j++)
			f[i][j][s]++;
		if (i > 1) {
			for (int j = 1; j < 10; j++)
				f[i][j][0]++;
		}
	}

	ll ans = 0;
	if (s)
		ans++;

	for (int i = 0; i < 10; i++)
		ans += f[a[0]][i][1];
	return ans + 1;
}

ll solve (ll u) {
	if (u < n)
		return 0;

	del(u, a);

	if (n == 0)
		return cat(u);

	memset(dp, 0, sizeof(dp));

	dp[0][0][1][0] = 1;

	ll v = n, tmp = 1;

	if (v) {
		while (v) {
			v /= 10;
			tmp *= 10;
		}
	} else {
		tmp = 10;
	}
	ll mod = tmp / 10;

	for (int i = 1; i <= a[0]; i++) {

		for (int j = 0; j < tmp; j++) {

			for (int k = 0; k < 10; k++) {
				int x = (j % mod) * 10 + k;

				if (x == n) {
					dp[i][x][0][1] += (dp[i-1][j][0][0] + dp[i-1][j][0][1]);
					if (k < a[i])
						dp[i][x][0][1] += (dp[i-1][j][1][0] + dp[i-1][j][1][1]);
					else if (k == a[i])
						dp[i][x][1][1] += (dp[i-1][j][1][0] + dp[i-1][j][1][1]);
				} else {
					dp[i][x][0][0] += dp[i-1][j][0][0];
					dp[i][x][0][1] += dp[i-1][j][0][1];

					if (k < a[i]) {
						dp[i][x][0][0] += dp[i-1][j][1][0];
						dp[i][x][0][1] += dp[i-1][j][1][1];
					} else if (k == a[i]) {
						dp[i][x][1][0] += dp[i-1][j][1][0];
						dp[i][x][1][1] += dp[i-1][j][1][1];
					}
				}
			}
		}
	}

	int c = a[0];
	ll ans = 0;
	for (int i = 0; i < tmp; i++)
		ans += (dp[c][i][0][1] + dp[c][i][1][1]);
	return ans;
}

int main () {
	while (scanf("%lld%lld%lld", &A, &B, &n) == 3) {
		if (A == -1 || B == -1 || n == -1)
			break;
		printf("%lld\n", solve(B) - solve(A-1));
	}
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <iostream>
#define min(a,b) (a)<(b)?(a):(b)

using namespace std;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int N = 5;

bool v[N][N][50];
ll val[N][N], best[N][N], dp[N][N][50];

void init () {
	memset(v, 0, sizeof(v));
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++) {
			cin >> val[i][j];
			best[i][j] = val[i][j];
		}

	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			if (i == j) continue;
			for (int k = 1; k <= 3; k++) if (k != i && k != j) {
				best[i][j] = min(best[i][j], best[i][k] + best[k][j]);
			}
		}
	}
}

ll solve(int l, int r, int n) {
	if (v[l][r][n]) return dp[l][r][n];

	v[l][r][n] = 1;
	ll& ans = dp[l][r][n];
	int x = 6 - l - r;

	if (n == 1) return ans = best[l][r];
	ans = solve(l, x, n-1) + solve(x, r, n-1) + val[l][r];
	ll k = solve(l, r, n-1) * 2 + solve(r, l, n-1) + val[l][x]+ val[x][r];
	ans = min(ans, k);
	return ans;
}

int main () {
	init();
	int n;
	scanf("%d", &n);
	cout << solve(1, 3, n) << endl;
	return 0;
}

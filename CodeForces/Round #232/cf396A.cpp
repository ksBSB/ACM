 #include <stdio.h>
#include <string.h>
#include <iostream>
#include <map>

using namespace std;
typedef long long ll;
const int N = 17000;
const int M = 1000;
const int mod = 1e9+7;

int n, k;
ll c[N][M];
map<int, int> g;

void init () {
	c[0][0] = 1;
	for (int i = 1; i < N; i++) {
		for (int j = 0; j <= i && j < M; j++) {
			if (j == 0 || j == i) c[i][j] = 1;
			else c[i][j] = (c[i-1][j-1] + c[i-1][j])%mod;
		}
	}
}

void solve (ll k) {
	for (int j = 2; j * j <= k; j++)  if (k % j == 0) {
		int cnt = 0;
		while (k%j == 0) {
			k /= j;
			cnt++;
		}
		g[j] += cnt;
	}
	if (k > 1) g[k] += 1;
}

int main () {
	init();

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &k);
		solve(k);
	}

	ll ans = 1;
	for (map<int, int>::iterator i = g.begin(); i != g.end(); i++) {
		int t = (*i).second;
		ans = (ans * c[t+n-1][n-1]) % mod;
	}
	cout << ans << endl;
	return 0;
}

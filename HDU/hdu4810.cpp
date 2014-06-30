#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 1005;
const ll MOD = 1e6+3;

int n, k[40];
ll c[N][N], r[N];

void init () {
	for (int i = 0; i < N; i++) {
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; j++)
			c[i][j] = (c[i-1][j-1] + c[i-1][j]) % MOD;
	}
}

void cal () {
	ll u;
	cin >> u;

	for (int i = 0; i < 32; i++)
		if (u & (1<<i))
			k[i]++;
}

ll Count(int t, int d) {
	ll ans = 0;

	for (int i = 1; i <= t && i <= d; i += 2) {

		if (n - t < d - i)
			continue;

		ans += (c[t][i] * c[n-t][d-i])%MOD;
		ans %= MOD;
	}
	return ans;
}

void solve (int d) {

	ll ans = 0;

	for (int i = 0; i < 32; i++) {
		ans += (Count(k[i], d) * (1<<i))%MOD;
		ans %= MOD;
	}

	r[d] = ans;
}

int main () {
	init();
	while (cin >> n) {

		memset(k, 0, sizeof(k));


		for (int i = 0; i < n; i++)
			cal();

		for (int i = 1; i <= n; i++)
			solve (i);

		for (int i = 1; i < n; i++)
			cout << r[i] << " ";
		cout << r[n] << endl;
	}
	return 0;
}

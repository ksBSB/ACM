#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long ll;
const int N = 1<<18;
const int M = 105;

ll n, dp[N+5][M];
int m, c, t[N], v[N+5][M];

void init () {
	cin >> n >> m;
	c = 0;	
	while (n) {
		t[c++] = n%10;
		n /= 10;
	}
}

ll solve (int s, int k) {
	if (s == 0 && k == 0) return 1;
	if (v[s][k]) return dp[s][k];
	v[s][k] = 1;

	int num[10];
	memset(num, 0, sizeof(num));

	ll& ans = dp[s][k];
	ans = 0;

	for (int i = 0; i < c; i++) if (s&(1<<i)) {
		if (num[t[i]]) continue;
		num[t[i]] = 1;
		ans += solve (s^(1<<i), (k*10+t[i])%m);
	}
	return ans;
}

int main () {
	init ();

	ll ans = 0;
	int s = (1<<c) - 1, num[10];
	memset(num, 0, sizeof(num));
	for (int i = 0; i < c; i++) if (t[i]) {
		if (num[t[i]]) continue;
		num[t[i]] = 1;
		ans += solve(s^(1<<i), t[i]%m);
	}
	cout << ans << endl;
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;

const int N = 20;

int c, t[N];
ll dp[N][N];

void cat (ll u) {
	c = 0;
	while (u) {
		t[c++] = u%10;
		u /= 10;
	}

	for (int i = 0; i < c/2; i++)
		swap(t[i], t[c-i-1]);
}

ll solve (ll u) {
	if (u < 0) return 0;
	else if (u == 0) return 1;

	memset(dp, 0, sizeof(dp));

	cat(u);

	int s = 0;
	for (int i = 1; i <= c; i++) {

		for (int j = 0; j < 10; j++) {

			for (int k = 0; k < 10; k++)
				dp[i][(j+k)%10] += dp[i-1][j];
		}

		for (int k = 0; k < t[i-1]; k++)
			dp[i][(s+k)%10] += 1;
		s = (s + t[i-1]) % 10;
	}

	return dp[c][0] + (s == 0 ? 1 : 0);
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		ll a, b;
		cin >> a >> b;
		printf("Case #%d: ", i);
		cout <<	solve(b) - solve(a-1) << endl;
	}
	return 0;
}

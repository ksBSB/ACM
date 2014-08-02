#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef __int64 ll;
const int maxn = 1024;
const ll MOD = 1e9+7;

int n, num[maxn];
ll l[maxn][maxn+10][2], r[maxn][maxn+10];

void init () {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &num[i]);
}

ll solve () {
	memset(l, 0, sizeof(l));
	memset(r, 0, sizeof(r));

	for (int i = 1; i < n; i++) {
		l[i][num[i]][1]++;
		for (int j = 0; j < maxn; j++) {
			l[i+1][j][1] = (l[i][j^num[i+1]][1] + l[i][j^num[i+1]][0])  % MOD;
			l[i+1][j][0] = (l[i][j][1] + l[i][j][0]) % MOD;
		}
	}

	for (int i = n; i; i--) {
		r[i][num[i]]++;
		for (int j = 0; j < maxn; j++) {
			r[i-1][j] = (r[i-1][j] + r[i][j]) % MOD;
			r[i-1][j&num[i-1]] = (r[i-1][j&num[i-1]] + r[i][j]) % MOD;
		}
	}

	ll ans = 0;
	for (int i = 1; i < n; i++) {
		
		for (int j = 0; j < maxn; j++) {
			/*
			if (l[i][j] * r[i+1][j])
				printf("%d %d %lld %lld\n", i, j, l[i][j], r[i+1][j]);
				*/
			ans = (ans + l[i][j][1] * r[i+1][j] % MOD) % MOD;
		}
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%I64d\n", solve());
	}
	return 0;
}

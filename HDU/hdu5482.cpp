#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 15;
const int maxm = 105;
const int mod = 1e9 + 7;
const int base = 23;
typedef long long ll;

int arr[maxn], dp[maxn][maxn][maxm];
ll temp[maxn];

void modify(int d, int c) {
	int n = 0;
	for (int i = 1; i <= d; i++) {
		ll s = 0;
		for (int j = i; j <= d; j++) {
			s = s * base + arr[j];
			temp[n++] = s;
		}
	}
	sort(temp, temp + n);
	int k = unique(temp, temp + n) - temp;
	dp[d][c][k]++;
}

void dfs (int d, int c) {
	if (d > 10) return ;
	for (int i = 1; i <= c; i++) {
		arr[d] = i;
		modify(d, max(i, c-1));
		dfs(d+1, max(i+1, c));
	}
}

int N, M, K;

int solve () {
	ll c = 1;
	int ret = 0;
	for (int i = 1; i <= N; i++) {
		c = c * (K-i+1) % mod;
		ret = (ret + c * dp[N][i][M] % mod) % mod;
	}
	return ret;
}

int main () {
	memset(dp, 0, sizeof(dp));
	dfs(1, 1);

	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d%d", &N, &M, &K);
		printf("%d\n", solve());
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 505;
const int mod = 1e9 + 7;

int dp[maxn][maxn], catalan[maxn];

void preserve () {
	catalan[0] = catalan[1] = 1;
	for (int i = 2; i <= 500; i++) {
		for (int j = 0; j < i; j++)
			catalan[i] = (catalan[i] + (ll) catalan[j] * catalan[i-j-1]) % mod;
	}

	dp[0][0] = 1;
	for (int i = 1; i <= 500; i++) {
		for (int j = 0; j <= 500; j++) {
			for (int k = 0; k <= j; k++)
				dp[i][j] = (dp[i][j] + (ll) dp[i-1][j-k] * catalan[k]) % mod;
		}
	}
}

int N, M, far[maxn], son[maxn][2], idx[maxn], cnt[maxn], sum[maxn];

inline int newNode (int f) {
	M++;
	cnt[M] = son[M][0] = son[M][1] = 0;
	far[M] = f;
	return M;
}

void init () {
	M = 0;
	int u = newNode(1), t, k;
	idx[u] = M;

	for (int i = 1; i <= N; i++) {
		scanf("%d", &t);
		if (t == 0)
			u = far[u];
		else if (t <= 2) {
			if (son[u][t-1] == 0) {
				son[u][t-1] = newNode(u);
				idx[son[u][t-1]] = idx[u];
				cnt[idx[u]]--;
			}
			u = son[u][t-1];
		} else {
			scanf("%d", &k);
			son[u][t-3] = newNode(u);
			cnt[son[u][t-3]] = k - 1;
			idx[son[u][t-3]] = son[u][t-3];
		}
	}

	memset(sum, 0, sizeof(sum));
	for (int i = 1; i <= M; i++) {
		if (son[i][0] == 0)
			sum[idx[i]]++;
		if (son[i][1] == 0)
			sum[idx[i]]++;
	}
}

int solve () {
	int ret = 1;
	for (int i = 1; i <= M; i++) {
		if (idx[i] != i)
			continue;
		ret = (ll) ret * dp[sum[i]][cnt[i]] % mod;
	}
	return ret;
}

int main () {
	preserve();
	int cas = 1;
	while (scanf("%d", &N) == 1) {
		init ();
		printf("Case #%d: %d\n", cas++, solve ());
	}
	return 0;
}

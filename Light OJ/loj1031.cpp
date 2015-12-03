#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 105;

int N, A[maxn], S[maxn], dp[maxn][maxn];
bool vis[maxn][maxn];

void init () {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
	S[0] = 0;
	for (int i = 1; i <= N; i++) S[i] = S[i-1] + A[i];
	memset(vis, false, sizeof(vis));
}

int solve (int l, int r) {

	int& ret = dp[l][r];
	if (vis[l][r]) return ret;
	vis[l][r] = true;

	int sum = ret = S[r] - S[l-1];
	for (int i = l; i < r; i++) {
		int ls = solve(l, i);
		int rs = solve(i+1, r);
		ret = max(sum - min(ls, rs), ret);
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		int ans = solve(1, N);
		int ret = S[N] - ans;
		printf("Case %d: %d\n", kcas, ans - ret);
	}
	return 0;
}

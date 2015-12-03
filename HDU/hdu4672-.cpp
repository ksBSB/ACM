#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 100005;
const int maxm = 105;

int N, M, T, dp[maxn], A[maxn], B[maxm];
char name[2][maxm];

void init () {
	scanf("%s%s", name[0], name[1]);
	for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
	for (int i = 1; i <= M; i++) scanf("%d", &B[i]);
	sort(B + 1, B + 1 + M);

	T = B[M] * B[M];
	memset(dp, -1, sizeof(dp));
	dp[0] = 0;
	for (int i = 1; i <= M; i++) {
		for (int j = 0; j + B[i] <= T; j++) {
			if (dp[j] == -1) continue;
			dp[j+B[i]] = max(dp[j+B[i]], dp[j] + 1);
		}
	}
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		init();
		int ans = 0;
		for (int i = 1; i <= N; i++) {
			if (A[i] <= T) {
				if (dp[A[i]] == -1) {ans = 0; break; }
				else ans ^= dp[A[i]];
			} else {
				int x = (A[i] - T) % B[1] + T - B[1];
				if (dp[x] == -1) { ans = 0; break; }
				else ans ^= (dp[x] + (A[i]-x) / B[1]);
			}
		}
		ans = (ans ? 0 : 1);
		printf("%s\n", name[ans]);
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 2005;

ll N, M, K, dp[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	dp[1] = 0;
	for (int i = 2; i < maxn; i++)
		dp[i] = dp[(i+1)/2] + 1;

	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%I64d%I64d%I64d", &N, &M, &K);
		printf("Case #%d: %I64d %I64d\n", kcas, N * M * K - 1, dp[N] + dp[M] + dp[K]);
	}
	return 0;
}

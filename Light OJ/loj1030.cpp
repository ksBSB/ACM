#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 105;

int N;
double dp[maxn], A[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
			scanf("%lf", &A[i]);

		double ret = 0;
		memset(dp, 0, sizeof(dp));
		dp[1] = 1;
		for (int i = 1; i <= N; i++) {
			int t = min(i + 6, N);
			for (int j = i + 1; j <= t; j++)
				dp[j] += dp[i] / (t-i);
			ret += dp[i] * A[i];
		}
		printf("Case %d: %.10lf\n", kcas, ret);
	}
	return 0;
}

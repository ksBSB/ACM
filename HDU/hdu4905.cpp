#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef __int64 ll;
const int maxn = 3005;

int N, s[maxn][maxn], g[maxn][maxn];
ll ans, dp[maxn][maxn];

inline void scanf_ (int& a) {
    char in;
    while ((in = getchar()) > '9' || in < '0');
    a = in - '0';
    while (in = getchar(), in >= '0' && in <= '9')
        a = a * 10 + in - '0';
}

/*
inline int gcd (int a, int b) {
    return b == 0 ? a : gcd(b, a%b);
}
*/

inline int gcd (int a, int b) {
	int tmp;
	while (b) {
		tmp = a % b;
		a = b;
		b = tmp;
	}
	return a;
}

ll solve () {
	for (int i = 1; i <= N; i++)
		s[i][i] = i;

    for (int k = 1; k < N; k++) {
        for (int i = 1; i <= N - k; i++) {
            int j = i + k;
			dp[i][j] = 0;
            for (int x = s[i][j-1]; x <= s[i+1][j]; x++) {
				if (x < j && dp[i][x] + dp[x+1][j] + g[i][j] > dp[i][j]) {
					dp[i][j] = dp[i][x] + dp[x+1][j] + g[i][j];
					s[i][j] = x;
				}
			}
		}
	}
	return dp[1][N] + ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		ans = 0;
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			scanf_(g[i][i]);
			ans += g[i][i];
		}

		//memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= N; i++) {

			for (int j = i+1; j <= N; j++)
				g[i][j] = gcd(g[i][j-1], g[j][j]);;
		}
		printf("%I64d\n", solve());
	}
	return 0;
}

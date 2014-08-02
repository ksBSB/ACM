/***********************
 * (0, 0, 0, ...) -> (a, b, c, ...)
 * ans = a + b + c +.. - gcd(a,b) - gcd(a,c) - .. + gcd(a, b, c) ...
***********************/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 15;

int N, d[maxn], g[2][maxn];

inline int gcd (int a, int b) {
	return b == 0 ? a : gcd (b, a%b);
}

void init () {
	scanf("%d", &N);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &g[i][j]);
	for (int i = 0; i < N; i++)
		d[i] = abs(g[0][i] - g[1][i]);
}

ll solve () {
	ll ans = 0;
	for (int i = 1; i < (1<<N); i++) {
		int sign = -1, tmp = -1;
		for (int j = 0; j < N; j++) {
			if (i&(1<<j)) {
				tmp = (tmp == -1 ? d[j] : gcd(tmp, d[j]));
				sign *= -1;
			}
		}
		ans += tmp * sign;
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		printf("Case %d: %lld\n", i, solve());
	}
	return 0;
}

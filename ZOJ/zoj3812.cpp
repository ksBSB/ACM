#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

#define lowbit(x) ((x)&(-x))

typedef unsigned long long ull;
typedef long long ll;
const int maxn = 405;
const int maxt = 200000;

int N, Q, W[maxn], T[maxn];
short dp[maxt + 5][52];
map<ll, int> G;
ull s[maxt];

void init () {
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= N; i++)
		scanf("%d%d", &W[i], &T[i]);

	ull bit = (1LL<<51) - 1;
	memset(s, 0, sizeof(s));
	memset(dp, 0, sizeof(dp));
	s[0] = 1;

	for (int i = 1; i <= N; i++) {
		for (int j = maxt; j >= T[i]; j--) {
			ull v = s[j];

			s[j] |= ((s[j-T[i]]<<W[i]) & bit);

			for (ll k = s[j]^v; k != 0; k -= lowbit(k))
				dp[j][G[lowbit(k)]] = i;
		}
	}
}

int main () {

	for (int i = 0; i <= 50; i++)
		G[1LL<<i] = i;

	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();

		int x, y;
		while (Q--) {
			scanf("%d%d", &x, &y);

			if (dp[y][x]) {
				int u = dp[y][x];
				printf("%d", u);
				while (u) {
					y -= T[u];
					x -= W[u];
					u = dp[y][x];

					if (u)
						printf(" %d", u);
				}
				printf("\n");
			} else
				printf("No solution!\n");
		}
	}
	return 0;
}

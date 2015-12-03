#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;

int N, M;
ll W[maxn];

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		int u, v; ll k;
		for (int i = 1; i <= N; i++) {
			scanf("%lld", &k);
			W[i] = 2 * k;
		}

		while (M--) {
			scanf("%d%d%lld", &u, &v, &k);
			W[u] += k; W[v] += k;
		}

		ll p = 0, q = 0;
		sort(W + 1, W + N + 1);
		for (int i = 1; i <= N; i += 2) {
			p += W[i], q += W[i+1];
		}
		printf("%lld\n", (q-p)>>1);
	}
	return 0;
}

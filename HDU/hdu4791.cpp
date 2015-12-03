#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;

int N, M, S[maxn], P[maxn];
ll W[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &N, &M);
		for (int i = 0; i < N; i++) {
			scanf("%d%d", &S[i], &P[i]);
			W[i] = 1LL * S[i] * P[i];
		}
		W[N] = 1e18;
		for (int i = N-1; i >= 0; i--)
			W[i] = min(W[i], W[i+1]);
		int x, k;
		while (M--) {
			scanf("%d", &x);
			k = upper_bound(S, S + N, x) - S - 1;
			printf("%lld\n", min(1LL * P[k] * x, W[k+1]));
		}
	}
	return 0;
}

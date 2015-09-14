#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

const int bitn = 36;
const int maxn = 1e5 + 5;

int N, A[maxn];
ll pre[maxn], bit[maxn];

ll solve () {
	ll ans = 1LL * N * (N+1) / 2 * (N+1), sum;

	for (int i = 1; i <= bitn; i++) {
		int r = sum = 0;
		for (int j = 1; j <= N; j++) {
			while (r < N && sum < bit[i])
				sum += A[++r];

			if (sum < bit[i])
				break;
			ll n = N - r + 1;
			ans += n * j + n * (r + N) / 2;
			sum -= A[j];
		}
	}
	return ans;
}

inline int get(ll k) {
	if (k == 0)
		return 0;
	return log2(k);
}

ll handle () {
	pre[0] = 0;
	for (int i = 1; i <= N; i++)
		pre[i] = pre[i-1] + A[i];

	ll ans = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = i; j <= N; j++) {
			ans += (ll)(get(pre[j] - pre[i-1]) + 1) * (i + j);
		}
	}
	return ans;
}

int main () {
	bit[0] = 1;
	for (int i = 1; i <= bitn; i++)
		bit[i] = bit[i-1] * 2;

	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
			scanf("%d", &A[i]);
		printf("%lld\n", solve());
		//printf("%lld\n", handle());
	}
	return 0;
}

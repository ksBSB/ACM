#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

int N, K;

ll C(int n, int k) {
	if (n - k < k) k = n - k;
	ll ret = 1;
	for (int i = 0; i < k; i++)
		ret = ret * (n - i) / (i+1);
	return ret;
}

ll solve () {
	if (K > N) return 0;
	ll ret = 1;
	for (int i = 0; i < K; i++)
		ret = ret * (N - i);
	return C(N, K) * ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d%d", &N, &K);
		printf("Case %d: %lld\n", kcas, solve());
	}
	return 0;
}

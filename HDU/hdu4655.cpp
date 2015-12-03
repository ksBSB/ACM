#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e6 + 5;
const int mod = 1e9 + 7;

/* 相同块的贡献算给最左边*/

int N, A[maxn], P[maxn];
ll L[maxn], R[maxn];

int solve () {
	L[0] = R[N+1] = 1;
	for (int i = 1; i <= N; i++) L[i] = L[i-1] * P[i] % mod;
	for (int i = N; i >= 1; i--) R[i] = R[i+1] * P[i] % mod;

	ll ret = R[1];
	for (int i = 2; i <= N; i++) {
		ll tmp = (1LL * max(P[i-1], P[i])-1) * min(P[i-1], P[i]) % mod;
		ret = (ret + L[i-2] * R[i+1] % mod * tmp % mod) % mod;;
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
		sort(A + 1, A + N + 1);
		int p = N;
		for (int i = 2; i <= N; i += 2) P[i] = A[p--];
		for (int i = 1; i <= N; i += 2) P[i] = A[p--];
		printf("%d\n", solve());
	}
	return 0;
}

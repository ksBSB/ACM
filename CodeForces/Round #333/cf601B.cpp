#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;
typedef long long ll;

int N, M, A[maxn], L[maxn], R[maxn];
int S, T[maxn], P[maxn];

void init () {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) scanf("%d", &A[i]);

	S = 0;
	for (int i = 2; i <= N; i++) {
		int tmp = abs(A[i] - A[i-1]);
		while (S && T[S-1] <= tmp) S--;
		L[i] = S ? P[S-1] : 0;

		T[S] = tmp;
		P[S] = i;
		S++;
	}

	S = 0;
	for (int i = N; i > 1; i--) {
		int tmp = abs(A[i] - A[i-1]);
		while (S && T[S-1] < tmp) S--;
		R[i] = S ? P[S-1]-1 : N;

		T[S] = tmp;
		P[S] = i;
		S++;
	}
}

void solve () {
	int l, r;
	while (M--) {
		scanf("%d%d", &l, &r);
		ll ans = 0;
		for (int i = l + 1; i <= r; i++) {
			ll tmp = abs(A[i] - A[i-1]);
			ans += tmp * (i - max(l, L[i])) * (min(r, R[i]) - i + 1);
		}
		printf("%lld\n", ans);
	}
}

int main () {
	init();
	solve();
	return 0;
}

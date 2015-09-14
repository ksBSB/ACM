#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 2 * 1e5 + 5;

ll ans;
int N, C, L, R, D[maxn], S[maxn], B[maxn], W[maxn * 2], V[maxn * 2];

void init () {
	scanf("%d%d", &N, &C);
	for (int i = 1; i <= N; i++)
		scanf("%d", &D[i]);
	for (int i = 0; i <= N; i++)
		scanf("%d%d", &B[i], &S[i]);
}

void merge(int s) {
	int v = 0;
	while (L <= R && W[L] <= s)
		v += V[L++];

	if (v) {
		W[--L] = s;
		V[L] = v;
	}
}

int sell (int s) {
	int ret = 0;
	while (L <= R && W[R] >= s) {
		ans -= 1LL * V[R] * W[R];
		ret += V[R--];
	}
	return ret;
}

void consume(int v) {
	while (v) {
		int k = min(V[L], v);
		v -= k;
		V[L] -= k;
		if (V[L] == 0)
			L++;
	}
}

void solve () {
	ans = 0;
	L = N, R = N - 1;;

	for (int i = 0; i < N; i++) {
		merge(S[i]);
		int add = (i == 0 ? C : D[i] - D[i-1]);
		add += sell(B[i]);
		W[++R] = B[i];
		V[R] = add;
		ans += 1LL * B[i] * add;
		consume(D[i+1] - D[i]);
	}
	merge(S[N]);
	while (L <= R) {
		ans -= 1LL * W[L] * V[L];
		L++;
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();
		solve ();
		printf("%lld\n", ans);
	}
	return 0;
}

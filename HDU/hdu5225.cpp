#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

const int maxn = 100;
const int mod = 1e9+7;
int N, ans, V[maxn + 5], A[maxn + 5];
ll S[maxn + 5], L[maxn + 5];

int query(int x) {
	int ret = 0;
	for (int i = 1; i < x; i++) {
		if (V[i] == 0)
			ret++;
	}
	return ret;
}

int dfs(int d, int s) {

	if (d > N)
		return 0;

	if (s == 0) {
		ans = (ans + S[N-d+1]) % mod;
		return L[N-d+1];
	} else {

		int ret = 0;

		for (int i = 1; i <= A[d]; i++) {
			if (V[i]) continue;

			V[i] = 1;

			int s = query(i);
			ll temp = dfs(d + 1, i == A[d] ? 1 : 0);
			ans = (ans + temp * s % mod) % mod;

			ret = (ret + temp) % mod;

			V[i] = 0;
		}

		return ret;
	}
}

int main () {
	S[1] = 0;
	L[1] = 1;
	for (int i = 2; i <= maxn; i++) {
		S[i] = S[i-1] * i % mod+ L[i-1] * ((1LL * i * (i-1) / 2) % mod) % mod;
		L[i] = L[i-1] * i % mod;
	}

	while (scanf("%d", &N) == 1) {
		ans = 0;
		memset(V, 0, sizeof(V));

		for (int i = 1; i <= N; i++)
			scanf("%d", &A[i]);

		dfs(1, 1);
		printf("%d\n", ans);
	}
	return 0;
}

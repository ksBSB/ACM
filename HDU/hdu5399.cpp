#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 105;
const int mod = 1e9 + 7;
typedef long long ll;

int N, M, C, A[maxn][maxn], F[maxn], V[maxn];

void move (int* t) {
	for (int i = 1; i <= N; i++)
		F[i] = t[F[i]];
}

bool judge (int n) {
	for (int i = 1; i <= N; i++) F[i] = i;
	for (int i = n-1; i >= 0; i--)
		move(A[i]);

	memset(V, 0, sizeof(V));
	for (int i = 1; i <= N; i++) {
		if (V[F[i]]) return false;
		V[F[i]] = 1;
	}
	return true;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		int n = C = 0;

		for (int i = 0; i < M; i++) {
			scanf("%d", &A[n][1]);
			if (A[n][1] == -1) {
				C++;
				continue;
			}

			for (int j = 2; j <= N; j++)
				scanf("%d", &A[n][j]);
			n++;
		}

		ll ans = judge(n) ? 1 : 0, k = 1;
		for (int i = 1; i <= N; i++)
			k = k * i % mod;
		for (int i = 1; i < C; i++)
			ans = ans * k % mod;

		if (C == 0) {
			bool flag = false;
			for (int i = 1; i <= N; i++) {
				if (F[i] != i)
					flag = true;
			}
			if (flag)
				ans = 0;
		}

		printf("%lld\n", ans % mod);
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;

int N, A[maxn], F[maxn], V[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		memset(V, 0, sizeof(V));
		for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
		for (int i = 1; i <= N; i++) scanf("%d", &F[A[i]]);

		int ans = 0;
		for (int i = 1; i <= N; i++) if (!V[A[i]]) {
			if (A[i] == F[A[i]]) continue;
			ans++;
			int u = A[i];
			while (V[u] == 0) {
				V[u] = 1;
				u = F[u];
			}
		}
		printf("%d\n", N - ans);
	}
	return 0;
}

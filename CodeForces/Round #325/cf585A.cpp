#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 4005;

int N, M, A[maxn], V[maxn], D[maxn], P[maxn];

int main () {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d%d%d", &V[i], &D[i], &P[i]);

	M = 0;
	for (int i = 1; i <= N; i++) {
		if (P[i] < 0) continue;
		A[M++] = i;
		int v = V[i], d = 0;

		for (int j = i + 1; j <= N; j++) {
			if (P[j] < 0) continue;
			P[j] -= (v + d);
			if (P[j] < 0) d = min((int)1e7, d + D[j]);
			v = max(0, v-1);
		}
	}

	printf("%d\n", M);
	for (int i = 0; i < M; i++)
		printf("%d%c", A[i], i == M-1 ? '\n' : ' ');
	return 0;
}

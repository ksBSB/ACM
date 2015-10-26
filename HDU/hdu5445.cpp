#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 50000;
const int maxm = 205;
const int inf = 0x3f3f3f3f;

int N, M, P, cost[maxn+5], engy[maxn+5];
int T[maxm], U[maxm], V[maxm];
int X[maxm], Y[maxm], Z[maxm];

void init() {
	scanf("%d%d%d", &N, &M, &P);
	for (int i = 0; i < N; i++)
		scanf("%d%d%d", &T[i], &U[i], &V[i]);
	for (int i = 0; i < M; i++)
		scanf("%d%d%d", &X[i], &Y[i], &Z[i]);
}

inline int getbitmost(int x) {
	if (x == 0) return 0;
	int i = 0;
	while (x) {
		i++;
		x >>= 1;
	}
	return i-1;
}

bool solve () {
	memset(cost, 0, sizeof(cost));

	for (int i = 0; i < M; i++) {
		int t = getbitmost(Z[i]);
		for (int k = t-1; k >= 0; k--) {
			int w = (1<<k) * X[i];
			int d = (1<<k) * Y[i];
			for (int j = maxn; j >= 0; j--) {
				if (j + d > maxn) continue;
				cost[j+d] = max(cost[j+d], cost[j]+w);
			}
		}
		int w = (Z[i] - (1<<t) + 1) * X[i];
		int d = (Z[i] - (1<<t) + 1) * Y[i];
		for (int j = maxn; j >= 0; j--) {
			if (j + d > maxn) continue;
			cost[j+d] = max(cost[j+d], cost[j]+w);
		}
	}

	memset(engy, inf, sizeof(engy));
	engy[0] = 0;
	for (int i = 0; i < N; i++) {
		int t = getbitmost(V[i]);
		for (int k = t-1; k >= 0; k--) {
			int w = (1<<k) * U[i];
			int d = (1<<k) * T[i];
			for (int j = P; j >= 0; j--) {
				int v = min(P, j + d);
				engy[v] = min(engy[v], engy[j] + w);
			}
		}

		int w = (V[i] - (1<<t) + 1) * U[i];
		int d = (V[i] - (1<<t) + 1) * T[i];
		for (int j = maxn; j >= 0; j--) {
			int v = min(P, j + d);
			engy[v] = min(engy[v], engy[j] + w);
		}
	}

	int limit = engy[P];
	for (int i = 0; i <= maxn; i++) {
		if (limit <= cost[i]) {
			printf("%d\n", i);
			return true;
		}
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		if (!solve()) printf("TAT\n");
	}
	return 0;
}

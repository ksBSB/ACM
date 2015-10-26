#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 55;
const int maxm = 505;
const int inf = 0x3f3f3f3f;

int N, M, A[maxn], V[maxn][maxn], L[maxm];
int Lx[maxn], Ly[maxm], W[maxn][maxm];
bool S[maxm], T[maxm];

int match(int i) {
	S[i] = true;
	for (int j = 1; j <= M; j++) {
		if (Lx[i] + Ly[j] == W[i][j] && !T[j]) {
			T[j] = true;
			if (!L[j] || match(L[j])) {
				L[j] = i;
				return true;
			}
		}
	}
	return false;
}

void update () {
	int a = inf;
	for (int i = 1; i <= N; i++) if (S[i]) {
		for (int j = 1; j <= M; j++) if (!T[j])
			a = min(a, Lx[i]+Ly[j]-W[i][j]);
	}

	for (int i = 1; i <= N; i++)
		if (S[i]) Lx[i] -= a;
	for (int i = 1; i <= M; i++)
		if (T[i]) Ly[i] += a;
}

void KM () {

	for (int i = 1; i <= N; i++) {
		Lx[i] = -inf;
		for (int j = 1; j <= M; j++) {
			Lx[i] = max(Lx[i], W[i][j]);
		}
	}
	for (int i = 1; i <= M; i++) L[i] = Ly[i] = 0;


	for (int i = 1; i <= N; i++) {
		while (true) {
			for (int j = 1; j <= M; j++) S[j] = T[j] = 0;
			if (match(i)) break;
			else update();
		}
	}
}

void init () {
	for (int i = 1; i <= M; i++) scanf("%d", &A[i]);

	int s, t, k;
	memset(V, inf, sizeof(V));
	for (int i = 1; i <= N; i++) {
		scanf("%d", &k);
		while (k--) {
			scanf("%d%d", &s, &t);
			for (int j = 1; j <= M; j++) if (A[j] >= s)
				V[i][j] = min(V[i][j], t);
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			for (int p = 1; p <= N; p++) {
				int v = (j-1)*N + p;
				if (V[i][j] == inf)
					W[i][v] = -inf;
				else
					W[i][v] = - p * V[i][j];
			}
		}
	}
	M = M * N;
	KM();
}

int main () {
	int cas = 0;
	while (scanf("%d%d", &M, &N) == 2 && N + M) {
		if (cas++) printf("\n");
		init();
		printf("Case %d\n", cas);

		double ans = 0;
		for (int i = 1; i <= N; i++) ans += Lx[i];
		for (int i = 1; i <= M; i++) ans += Ly[i];
		printf("Average turnaround time = %.2lf\n", -ans / N);

		int P[maxn], RS[maxn], RT[maxn];
		memset(P, 0, sizeof(P));
		for (int i = 1; i <= M; i++) {
			if (L[i]) {
				int rg = (i-1)/N+1;
				P[rg] += V[L[i]][rg];
				RS[L[i]] = rg;
				RT[L[i]] = P[rg];
			}
		}

		for (int i = 1; i <= N; i++) {
			int s = P[RS[i]] - RT[i];
			printf("Program %d runs in region %d from %d to %d\n", i, RS[i], s, s + V[i][RS[i]]);
		}
	}
	return 0;
}

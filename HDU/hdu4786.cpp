#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;
//typedef pair<int,int> pii;

int N, M, C[3], F[3][maxn];

int find (int u, int* f) { return f[u] == u ? u : f[u] = find(f[u], f); }

void link(int u, int v, int k) {
	int fu = find(u, F[k]);
	int fv = find(v, F[k]);
	if (fu != fv) {
		C[k]--;
		F[k][fu] = fv;
	}
}

void init () {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < 3; j++) F[j][i] = i;
	}
	C[0] = C[1] = C[2] = N;

	int u, v, k;
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &u, &v, &k);
		link(u, v, k);
		link(u, v, 2);
	}
}

bool judge () {
	if (C[2] != 1) return false;
	int l = C[0]-1, r = N-C[1];
	int p = 1, q = 1;
	while (q < N) {
		if (l <= q && q <= r) return true;
		int tmp = p + q;
		p = q;
		q = tmp;
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case #%d: %s\n", kcas, judge () ? "Yes" : "No");
	}
	return 0;
}

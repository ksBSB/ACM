/* hdu4797 */
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 105;

int N, E, ans, mv, P[maxn], C[maxn];
pii S[maxn*maxn], R[2][maxn*maxn];

bool cmp(const int& x, const int& y) {
	if (C[x] == C[y]) return x < y;
	return C[x] > C[y];
}

void dfs (int d) {
	sort(P + d, P + N, cmp);

	int rec = mv, rep = -1, u = P[d];


	if (d >= N || C[u] == 0) {
		for (int i = 0; i < mv; i++)
			R[ans][i] = S[i];
		ans++;
		return;
	}

	if (d + C[u] >= N) return;
	int ed = P[d+C[u]];
	if (C[ed] == 0) return;

	if (d+C[u]+1 < N) {
		rep = P[d+C[u]+1];
		if (C[ed] != C[rep]) rep = -1;
	}

	for (int i = 1; i <= C[u]; i++) {
		S[mv++] = make_pair(u, P[d+i]);
		C[P[d+i]]--;
	}
	dfs(d + 1);

	if (ans < 2 && rep != -1) {
		int v = S[--mv].second;
		C[v]++;
		S[mv++] = make_pair(u, rep);
		C[rep]--;

		dfs(d + 1);
	}

	while (mv > rec) {
		int v = S[--mv].second;
		C[v]++;
	}
}

int main () {
	while (scanf("%d", &N) == 1) {
		E = ans = mv = 0;
		for (int i = 0; i < N; i++) {
			scanf("%d", &C[i]);
			P[i] = i;
			E += C[i];
		}

		if ((E&1) == 0) dfs(0);

		E >>= 1;
		if (ans == 1) printf("UNIQUE\n");
		else if (ans == 2) printf("MULTIPLE\n");
		else  printf("IMPOSSIBLE\n");

		for (int i = 0; i < ans; i++) {
			printf("%d %d\n", N, E);

			for (int j = 0; j < E; j++) {
				if (j) printf(" ");
				printf("%d", R[i][j].first+1);
			}
			printf("\n");

			for (int j = 0; j < E; j++)  {
				if (j) printf(" ");
				printf("%d", R[i][j].second+1);
			}
			printf("\n");
		}

	}
	return 0;
}

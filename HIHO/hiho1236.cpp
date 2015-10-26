#include <cstdio>
#include <cstring>
#include <cmath>
#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 5 * 1e4 + 5;
const int maxm = 300 + 5;

int N, M, Q, L[maxm], R[maxm], B[maxn];
pii scores[5][maxn];
bitset<50005> S[5][300], A[10];

void init () {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 5; j++) {
			scanf("%d", &scores[j][i].first);
			scores[j][i].second = i;
		}
	}

	int len = sqrt(N);
	int block = N / len + (N % len ? 1 : 0);
	L[0] = R[0] = -1;
	for (int i = 1; i <= block; i++) {
		L[i] = (i-1) * len;
		R[i] = i * len;
	}
	R[block] = N;

	for (int i = 0; i < 5; i++)
		S[i][0] = 0;

	for (int i = 0; i < 5; i++) {
		sort(scores[i], scores[i] + N);
		for (int j = 1; j <= block; j++) {
			S[i][j] = S[i][j-1];
			for (int k = L[j]; k < R[j]; k++)
				S[i][j][scores[i][k].second] = 1;
		}
	}

	for (int i = 1; i <= block; i++) {
		for (int j = L[i]; j < R[i]; j++)
			B[j] = i;
	}
}

void solve (int u, int x) {
	int t = lower_bound(scores[u], scores[u] + N, make_pair(x, N)) - scores[u];
	//printf("%d %d!!!!\n", t, B[t]);
	A[u] = S[u][B[t]-1];
	for (int i = L[B[t]]; i < t; i++) {
		A[u][scores[u][i].second] = 1;
	//	printf("%d\n", scores[u][i].second);
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();

		int bw = 0, x;
		scanf("%d", &Q);
		while (Q--) {
			for (int i = 0; i < 5; i++) {
				scanf("%d", &x);
				solve(i, x^bw);
			}
			for (int i = 4; i; i--)
					A[i-1] &= A[i];
			bw = A[0].count();
			printf("%d\n", bw);
		}
	}
	return 0;
}

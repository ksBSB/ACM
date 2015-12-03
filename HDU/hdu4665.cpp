#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 2005;

int N, A[maxn], P[maxn], S[maxn];

void init () {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%d", &A[i]);

	memset(P, -1, sizeof(P));
	for (int i = N; i; i--) {
		S[i] = P[A[i]];
		P[A[i]] = i;
	}

	memset(P, 0, sizeof(P));
}

bool dfs (int d, int l, int c) {
	if (l >= N) return c * 2 == N;

	if (P[d]) return dfs(d + 1, l, c);

	if (S[d] > l) {
		P[S[d]] = 1;
		if (dfs(d + 1, S[d], c + 1)) return true;
		P[S[d]] = 0;
	}

	int s = S[d];
	if (s != -1 && S[s] > l) {
		P[S[s]] = 1;
		if (dfs(d + 1, S[s], c + 1)) return true;
		P[S[s]] = 0;
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		dfs(1, 1, 0);
		for (int i = 1; i <= N; i++)
			printf("%d", P[i]);
		printf("\n");
	}
	return 0;
}

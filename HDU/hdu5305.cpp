#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 40;

int N, M, ans, C[maxn], D[maxn], L[maxn], R[maxn];

void init () {
	memset(C, 0, sizeof(C));
	memset(D, 0, sizeof(D));

	scanf("%d%d", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d%d", &L[i], &R[i]);
		D[L[i]]++;
		D[R[i]]++;
	}
}

int dfs(int u, int c) {
	if (M - u + c  < M / 2)
		return 0;
	if (M / 2 == c)
		return 1;

	int ans = 0;
	C[L[u]]++;
	C[R[u]]++;
	if (C[L[u]] <= D[L[u]] / 2 && C[R[u]] <= D[R[u]] / 2)
		ans += dfs(u + 1, c + 1);
	C[L[u]]--;
	C[R[u]]--;
	ans += dfs(u + 1, c);
	return ans;
}

int solve () {
	if (M&1)
		return 0;
	for (int i = 1; i <= N; i++)
		if (D[i]&1)
			return 0;

	return dfs(0, 0);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();	
		printf("%d\n", solve());
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 25;
const int inf = 0x3f3f3f3f;

int N, A, B[maxn], ans;

void init () {
	ans = inf;
	scanf("%d%d", &N, &A);
	for (int i = 1; i <= N; i++)
		scanf("%d", &B[i]);
	sort(B + 1, B + 1 + N);
}

void dfs (int d, int a, int s) {
	if (a == 0) {
		ans = min(ans, s);
		return;
	}

	if (d == 0)
		return;

	dfs(d - 1, a, s);

	if (B[d] <= a)
		dfs(d - 1, a % B[d], s + 1);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();
		dfs(N, A, 0);
		printf("%d\n", ans == inf ? -1 : ans);
	}
	return 0;
}

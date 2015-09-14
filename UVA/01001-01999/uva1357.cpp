#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>

using namespace std;
const int maxn = 3 * 1e5 + 5;
const int maxm = 2 * 1e7 + 5;

int N, M, S[maxn], C[maxn], pre[maxm], post[maxm];

void dfs(int root) {
	stack<int> sta;
	sta.push(root);
	int dfslock = pre[root] = 0;

	while (!sta.empty()) {
		int x = sta.top();
		if (pre[x]) {
			post[x] = ++dfslock;
			sta.pop();
			continue;
		}

		pre[x] = ++dfslock;
		for (int i = S[x]; i < S[x] + C[x]; i++) {
			if (i < N) {
				pre[i] = 0;
				sta.push(i);
			} else {
				pre[i] = ++dfslock;
				post[i] = ++ dfslock;
			}
		}
	}
}

int main () {
	int cas, u, v;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d", &N);
		S[0] = 1;
		for (int i = 0; i < N; i++) {
			scanf("%d", &C[i]);
			if (i) S[i] = S[i-1] + C[i-1];
		}

		dfs(0);

		scanf("%d", &M);
		printf("Case %d:\n", kcas);
		for (int i = 0; i < M; i++) {
			scanf("%d%d", &u, &v);
			printf("%s\n", pre[u] < pre[v] && post[u] > post[v] ? "Yes" : "No");
		}
		if (kcas < cas) printf("\n");
	}
	return 0;
}

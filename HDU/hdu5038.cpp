#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;
//const int maxn = 1e6 + 5;

int N, c[105];
vector<int> g;

int solve (int x) {
	return 10000 - x * x;
}

int main () {
	int cas, x;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d", &N);
		g.clear();
		memset(c, 0, sizeof(c));

		for (int i = 0; i < N; i++) {
			scanf("%d", &x);
			c[abs(100-x)]++;
		}

		int ans = 0;
		for (int i = 100; i >= 0; i--) {
			if (c[i] > ans) {
				ans = c[i];
				g.clear();
			}

			if (c[i] == ans)
				g.push_back(i);
		}

		printf("Case #%d:\n", kcas);

		if (ans == N || ans * g.size() != N) {
			printf("%d", solve(g[0]));
			for (int i = 1; i < g.size(); i++)
				printf(" %d", solve(g[i]));
			printf("\n");
		} else
			printf("Bad Mushroom\n");
	}
	return 0;
}

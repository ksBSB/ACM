#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 1e4+5;

struct item {
	int pos, val;
	item (int pos = 0, int val = 0) {
		this->pos = pos;
		this->val = val;
	}
};

bool cmp (const item& a, const item& b) {
	return a.pos < b.pos;
}

int N, M, arr[105];
vector<item> g[maxn];

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		for (int i = 0; i <= M; i++)
			g[i].clear();

		int k, x;
		for (int i = 1; i <= N; i++) {
			scanf("%d", &k);
			for (int j = 0; j < k; j++)
				scanf("%d", &arr[j]);

			for (int j = 0; j < k; j++) {
				scanf("%d", &x);
				g[arr[j]].push_back(item(i, x));
			}
		}

		printf("%d %d\n", M, N);
		for (int i = 1; i <= M; i++) {
			sort(g[i].begin(), g[i].end(), cmp);

			printf("%lu", g[i].size());
			for (int j = 0; j < g[i].size(); j++)
				printf(" %d", g[i][j].pos);
			printf("\n");

			if (g[i].size() != 0) {
				printf("%d", g[i][0].val);
				for (int j = 1; j < g[i].size(); j++)
					printf(" %d", g[i][j].val);
			}
			printf("\n");
		}
	}
	return 0;
}

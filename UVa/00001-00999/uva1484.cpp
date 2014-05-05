#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int N = 500005;
const int INF = 0x3f3f3f3f;

struct node {
	int v, val;
	node(int v = 0, int val = 0) {
		this->v = v;
		this->val = val;
	}
};
vector<node> g[N];

int n, l, r;

void init () {
	for (int i = 0; i < n; i++)
		g[i].clear();

	int a, b, c;
	for (int i = 1; i < n; i++) {
		scanf("%d%d%d", &a, &b, &c);
		g[a].push_back(node(b, c));
	}
}

int solve (int u, int x, int s) {
	if (g[u].size() == 0)
		return s;

	int ans;

	if (x) {
		ans = INF;
		for (int i = 0; i < g[u].size(); i++) {

			int t = solve(g[u][i].v, 1-x, s+g[u][i].val);

			if (t < l || t > r)
				continue;

			ans = min(ans, t);
		}
	} else {
		ans = 0;
		for (int i = 0; i < g[u].size(); i++) {

			int t = solve(g[u][i].v, 1-x, s+g[u][i].val);

			if (t < l || t > r)
				continue;

			ans = max(ans, t);
		}
	}
	return ans;
}

int main () {
	while (scanf("%d%d%d", &n, &l, &r) == 3) {
		init();
		int ans = solve(0, 0, 0);

		if (ans >= l && ans <= r)
			printf("%d\n", ans);
		else
			printf("Oh, my god!\n");
	}
	return 0;
}

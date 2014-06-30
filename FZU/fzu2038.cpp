#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>

using namespace std;

const int N = 100005;
typedef long long ll;

struct node {
	int next;
	ll val;
	ll size;
	node() { next = 0, val = size = 0; };
	node(int next, ll val) {
		this->next = next;
		this->val = val;	
		this->size = 0;
	}
};

int vis[N];
ll n;
vector<node> v[N];

void init() {
	scanf("%lld", &n);
	for (int i = 0; i < n; i++) v[i].clear();
	memset(vis, 0, sizeof(vis));

	int a, b;
	ll c;
	for (int i = 1; i < n; i++) {
		scanf("%d%d%lld", &a, &b, &c);
		v[a].push_back(node(b, c));
		v[b].push_back(node(a, c));
	}
}

ll dfs(int s) {
	ll cnt = 0;

	vis[s] = 1;
	for (int i = 0; i < v[s].size(); i++) {
		int u = v[s][i].next;
		if (vis[u]) continue;

		ll t = dfs(u);
		v[s][i].size = (n - t) * t;
		cnt += t;
	}

	return cnt + 1;
}

ll solve() {
	dfs(0);
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < v[i].size(); j++)
			ans += v[i][j].val * v[i][j].size;
	}
	return ans * 2;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		printf("Case %d: %lld\n", i, solve());
	}
	return 0;
}

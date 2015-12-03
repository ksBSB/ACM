#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 300005;
const int SIGMA_SIZE = 26;
typedef long long ll;

int SZ = 0;
struct Node {
	int sz, ch[SIGMA_SIZE];
	Node () { memset(ch, 0, sizeof(ch)); }
}nd[maxn<<1];

int newNode () {
	++SZ;
	memset(nd[SZ].ch, 0, sizeof(nd[SZ].ch));
	return SZ;
}

void maintain(int u) {
	nd[u].sz = 1;
	for (int i = 0; i < SIGMA_SIZE; i++) if (nd[u].ch[i])
		nd[u].sz += nd[nd[u].ch[i]].sz;
}

void merge(int &a, int b) {
	if (a == 0) {
		a = b;
	} else {
		for (int i = 0; i < SIGMA_SIZE; i++) {
			if (nd[b].ch[i])
				merge(nd[a].ch[i], nd[b].ch[i]);
		}
	}
	maintain(a);
}

int N;
ll C[maxn];
char S[maxn];
vector<int> G[maxn];

void init () {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		G[i].clear();
		scanf("%lld", &C[i]);
	}
	scanf("%s", S + 1);

	int u, v;
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
}

int dfs(int u, int f) {
	int p = newNode();

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == f) continue;
		merge(p, dfs(v, u));
	}
	maintain(p);

	int r = newNode();
	nd[r].ch[S[u] - 'a'] = p;
	maintain(r);
	C[u] += nd[r].sz - 1;

	return r;
}

int main () {
	init();
	dfs(1, 0);
	ll ans = 0, cnt;
	for (int i = 1; i <= N; i++) {
		if (C[i] > ans) { ans = C[i]; cnt = 0; }
		if (C[i] == ans) { cnt++; }
	}
	printf("%lld\n%lld\n", ans, cnt);
	return 0;
}

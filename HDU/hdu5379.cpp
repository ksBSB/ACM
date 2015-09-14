#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 100005;
const int mod = 1e9 + 7;

int N, son[maxn], tson[maxn], out[maxn], fac[maxn];
vector<int> G[maxn];

int dfs (int u, int f) {
	son[u] = tson[u] = 0;
	ll ret = out[u] = 1;

	//printf("%d %I64d\n", u, ret);
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == f)
			continue;
		ret = ret * dfs(v, u) % mod;

		son[u]++;
		out[u] += out[v];
		if (out[v] > 1)
			tson[u]++;
	}

	ret = ret * fac[son[u] - tson[u]] % mod;

	if (tson[u])
		ret = ret * 2 % mod;

	//printf("%d:%d %d %I64d\n", u, son[u], tson[u], ret);
	if (tson[u] > 2)
		ret = 0;
	return ret;
}

void init () {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		G[i].clear();
	/*
	memset(son, 0, sizeof(son));
	memset(out, 0, sizeof(out));
	memset(tson, 0, sizeof(tson));
	*/

	int u, v;
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
}

int main () {
	fac[0] = fac[1] = 1;
	for (int i = 2; i <= 100000; i++)
		fac[i] = 1LL * i * fac[i-1] % mod;
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init ();
		if (N == 1)
			printf("Case #%d: 1\n", kcas);
		else
			printf("Case #%d: %I64d\n", kcas, 2LL * dfs(1, 0) % mod);
	}
	return 0;
}

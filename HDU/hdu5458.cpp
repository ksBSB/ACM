#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
const int maxn = 3 * 1e4 + 5;
const int maxm = 1e5 + 5;
typedef pair<int,int> pii;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)

namespace SegTree {

	int lc[maxn<<2], rc[maxn<<2], s[maxn<<2], f[maxn<<2];

	void maintain(int u, int v) {
		f[u] = v;
		s[u] = f[u] * (rc[u] - lc[u] + 1);
	}
	void pushup(int u) { s[u] = s[lson(u)] + s[rson(u)]; }
	void pushdown(int u) {
		if (f[u] != -1) {
			maintain(lson(u), f[u]);
			maintain(rson(u), f[u]);
			f[u] = -1;
		}
	}

	void build (int u, int l, int r) {
		lc[u] = l, rc[u] = r, f[u] = -1, s[u] = 1;

		if (l == r) return;
		int mid = (l+r)>>1;
		build(lson(u), l, mid);
		build(rson(u), mid+1, r);
		pushup(u);
	}

	void modify(int u, int l, int r, int v) {
		if (l <= lc[u] && rc[u] <= r) {
			maintain(u, v);
			return;
		}

		pushdown(u);
		int mid = (lc[u] + rc[u]) >> 1;
		if (l <= mid) modify(lson(u), l, r, v);
		if (r > mid) modify(rson(u), l, r, v);
		pushup(u);
	}

	int query(int u, int l, int r) {
		if (l <= lc[u] && rc[u] <= r)
			return s[u];

		pushdown(u);
		int mid = (lc[u] + rc[u]) >> 1, ret = 0;
		if (l <= mid) ret += query(lson(u), l, r);
		if (r > mid) ret += query(rson(u), l, r);
		pushup(u);
		return ret;
	}
};

/* 树链剖分*/
namespace TreeChain {
	int E, first[maxn], jump[maxn<<1], link[maxn<<1];
	int id, idx[maxn], dep[maxn], top[maxn], far[maxn], son[maxn], cnt[maxn];

	inline void addEdge(int u, int v) {
		link[E] = v;
		jump[E] = first[u];
		first[u] = E++;
	}

	void dfs (int u, int pre, int d) {
		far[u] = pre;
		dep[u] = d;
		cnt[u] = 1;
		son[u] = 0;

		for (int i = first[u]; i + 1; i = jump[i]) {
			int v = link[i];
			if (v == pre) continue;
			dfs(v, u, d + 1);
			cnt[u] += cnt[v];
			if (cnt[son[u]] < cnt[v])
				son[u] = v;
		}
	}

	void dfs (int u, int rot) {
		top[u]= rot;
		idx[u] = ++id;
		if (son[u])
			dfs(son[u], rot);

		for (int i = first[u]; i + 1; i = jump[i]) {
			int v = link[i];
			if (v == far[u] || v == son[u]) continue;
			dfs(v, v);
		}
	}

	void init (int n, int m, const vector<pii>& edges) {
		SegTree::build(1, 1, n);
		int u, v;
		id = E = 0;
		memset(first, -1, sizeof(first));

		for (int i = 0; i < m; i++) {
			if (edges[i].first == edges[i].second) continue;
			addEdge(edges[i].first, edges[i].second);
		}

		dfs(1, 0, 0);
		dfs(1, 1);
	}

	void modify (int u, int v, int k) {
		int p = top[u], q = top[v];
		while (p != q) {
			if (dep[p] < dep[q]) {
				swap(p, q);
				swap(u, v);
			}

			SegTree::modify(1, idx[p], idx[u], k);

			u = far[p];
			p = top[u];
		}

		if (dep[u] > dep[v])
			swap(u, v);

		if (u != v)
			SegTree::modify(1, idx[son[u]], idx[v], k);
	}

	int query (int u, int v) {
		int p = top[u], q = top[v], ret = 0;
		while (p != q) {
			if (dep[p] < dep[q]) {
				swap(p, q);
				swap(u, v);
			}

			ret += SegTree::query(1, idx[p], idx[u]);

			u = far[p];
			p = top[u];
		}

		if (dep[u] > dep[v])
			swap(u, v);

		if (u != v)
			ret += SegTree::query(1, idx[son[u]], idx[v]);
		return ret;
	}
};

/* Edge biconneted */
int dfsclock, pre[maxn], iscut[maxm<<1], bccno[maxn], cntbcc;
multiset<pii> chains;
vector<int> G[maxn];
vector<pii> edges;

int dfs (int u, int fa) {  
	int lowu = pre[u] = ++dfsclock;
	for (int i = 0; i < G[u].size(); i++) { 
		int e = G[u][i];
		int v = edges[e].second;
		if (!pre[v]) {
			int lowv = dfs(v, u);
			lowu = min(lowu, lowv);
			if (lowv > pre[u]) 
				iscut[e] = iscut[e^1] = 1;
		} else if (pre[v] < pre[u] && v != fa)
			lowu = min(lowu, pre[v]);
	}
	return lowu;
} 

void dfs (int u) {
	bccno[u] = cntbcc;
	for (int i = 0; i < G[u].size(); i++) { 
		int e = G[u][i];
		int v = edges[e].second;
		if (iscut[e] || bccno[v]) continue;
		dfs(v);
	}
}

void findEdge (int n) {
	dfsclock = cntbcc = 0;
	memset(pre, 0, sizeof(pre));
	memset(iscut, 0, sizeof(iscut));
	for (int i = 1; i <= n; i++)
		if (!pre[i]) dfs(i, -1);

	memset(bccno, 0, sizeof(bccno));
	for (int i = 1; i <= n; i++)
		if (!bccno[i]) {
			++cntbcc;
			dfs(i);
		}
} 

int N, M, Q, T[maxm], U[maxm], V[maxm];
void init () {
	chains.clear();
	scanf("%d%d%d", &N, &M, &Q);

	int u, v;
	for (int i = 1; i <= M; i++) {
		scanf("%d%d", &u, &v);
		if (u > v) swap(u, v);
		chains.insert(make_pair(u, v));
	}
	for (int i = 1; i <= Q; i++) {
		scanf("%d%d%d", &T[i], &U[i], &V[i]);
		if (U[i] > V[i]) swap(U[i], V[i]);
		if (T[i] == 2) continue;
		multiset<pii>::iterator it = chains.find(make_pair(U[i], V[i]));
		chains.erase(it);
		//chains.erase(make_pair(U[i], V[i]));
	}

	/* get final graph */
	edges.clear();
	for (int i = 1; i <= N; i++) G[i].clear();
	for (multiset<pii>::iterator i = chains.begin(); i != chains.end(); i++) {
		int u = i->first, v = i->second;
		//printf("%d %d\n", u, v);
		for (int j = 0; j < 2; j++) {
			edges.push_back(make_pair(u, v));
			G[u].push_back(edges.size()-1);
			swap(u, v);
		}
	}

	/* edge biconnected */
	findEdge(N);

	for (int i = 0; i < edges.size(); i++) {
		edges[i].first = bccno[edges[i].first];
		edges[i].second = bccno[edges[i].second];
	}
	sort(edges.begin(), edges.end());
	int n = unique(edges.begin(), edges.end()) - edges.begin();

	TreeChain::init(cntbcc, n, edges);
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case #%d:\n", kcas);
		vector<int> ans;
		for (int i = Q; i; i--) {
			if (T[i] == 1)
				TreeChain::modify(bccno[U[i]], bccno[V[i]], 0);
			else
				ans.push_back(TreeChain::query(bccno[U[i]], bccno[V[i]]));
		}
		for (int i = ans.size()-1; i >= 0; i--)
			printf("%d\n", ans[i]);
	}
	return 0;
}

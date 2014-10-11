#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
const int mod = 5;
const int maxn = 1e5+5;

int N, M, pos[maxn], v[maxn];
map<ll, int> G;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], c[maxn << 2];
ll s[maxn << 2][6];

inline void maintain (int u, int d) {
	c[u] += d;
	memset(s[u], 0, sizeof(s[u]));
	s[u][0] = (c[u] ? pos[lc[u]] : 0);
}

inline void pushup(int u) {
	int t = c[lson(u)] % mod;
	c[u] = c[lson(u)] + c[rson(u)];
	for (int i = 0; i < mod; i++)
		s[u][i] = s[lson(u)][i] + s[rson(u)][(i + mod - t) % mod];
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	c[u] = 0;
	memset(s[u], 0, sizeof(s[u]));

	if (l == r)
		return;
	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify (int u, int x, int d) {
	if (lc[u] == x && rc[u] == x) {
		maintain(u, d);
		return;
	}

	int mid = (lc[u] + rc[u]) / 2;
	if (x <= mid)
		modify(lson(u), x, d);
	else
		modify(rson(u), x, d);
	pushup(u);
}

struct OP {
	int p, k, id;
	OP (int k = 0, int p = 0, int id = 0) {
		this->k = k;
		this->p = p;
		this->id = id;
	}
	friend bool operator < (const OP& a, const OP& b) {
		if (a.k == 0)
			return false;
		if (b.k == 0)
			return true;
		if (a.p != b.p)
			return a.p < b.p;
		return a.id < b.id;
	}
};

inline bool cmp (const OP& a, const OP& b) {
	return a.id < b.id;
}

vector<OP> vec;

void init () {
	scanf("%d", &N);
	char op[5];
	int x;

	for (int i = 1; i <= N; i++) {
		scanf("%s", op);
		if (op[0] == 's')
			vec.push_back(OP(0, 0, i));
		else {
			scanf("%d", &x);
			vec.push_back(OP(op[0] == 'a' ? 1 : -1, x, i));
		}
	}

	M = 1;
	sort(vec.begin(), vec.end());
	for (int i = 0; i < N; i++) {
		if (vec[i].k < 0)
			continue;
		if (vec[i].k == 0)
			break;

		pos[M] = vec[i].p;
		vec[i].p = M++;
	}
	build(1, 1, M);
}

void solve () {
	sort(vec.begin(), vec.end(), cmp);
	for (int i = 0; i < N; i++) {
		//printf("%d %d!\n", vec[i].k, pos[vec[i].p]);
		if (vec[i].k == 0)
			printf("%lld\n", s[1][2]);
		else if (vec[i].k == -1) {
			int tmp = vec[i].p;
			v[G[tmp]] = 0;
			modify(1, G[tmp], -1);

			if (G[tmp] <= N && v[G[tmp]+1] && pos[G[tmp]] == pos[G[tmp]+1])
				G[tmp]++;
			else
				G[tmp] = 0;
		} else {
			int tmp = pos[vec[i].p];
			v[vec[i].p] = 1;
			modify(1, vec[i].p, 1);
			if (G[tmp] == 0)
				G[tmp] = vec[i].p;
		}
	}
}

int main () {
	init();
	solve();
	return 0;
}

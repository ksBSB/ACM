#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> pos;

const int maxn = 120000;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], v[maxn << 2], s[maxn << 2];

inline void pushup(int u) {
	if (v[u])
		s[u] = pos[rc[u]+1] - pos[lc[u]];
	else if (lc[u] == rc[u])
		s[u] = 0;
	else
		s[u] = s[lson(u)] + s[rson(u)];
}

inline void maintain (int u, int d) {
	v[u] += d;
	pushup(u);
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	v[u] = s[u] = 0;

	if (l == r)
		return;

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify (int u, int l, int r, int d) {

	if (l <= lc[u] && rc[u] <= r) {
		maintain(u, d);
		return;
	}

	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		modify(lson(u), l, r, d);
	if (r > mid)
		modify(rson(u), l, r, d);
	pushup(u);
}

struct Seg {
	int x, l, r, d;
	Seg (int x = 0, int l = 0, int r = 0, int d = 0) {
		this->x = x;
		this->l = l;
		this->r = r;
		this->d = d;
	}
	friend bool operator < (const Seg& a, const Seg& b) {
		return a.x < b.x;
	}
};

typedef long long ll;
typedef pair<int,int> pii;

int N, M, P[10];
pii H[10];
vector<Seg> vec[10];

inline int find (int k) {
	return lower_bound(pos.begin(), pos.end(), k) - pos.begin();
}

void init () {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++) {
		vec[i].clear();
		scanf("%d", &H[i].first);
		H[i].second = i;
	}
	sort(H, H + M + 1);
	for (int i = 0; i <= M; i++)
		P[H[i].second] = i;

	int x1, x2, y1, y2, d;
	for (int i = 0; i < N; i++) {
		scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &d);
		for (int j = 1; j <= P[d]; j++) {
			vec[j].push_back(Seg(x1, y1, y2, 1));
			vec[j].push_back(Seg(x2, y1, y2, -1));
		}
	}
}

ll solve (int idx) {
	pos.clear();
	sort(vec[idx].begin(), vec[idx].end());

	for (int i = 0; i < vec[idx].size(); i++) {
		pos.push_back(vec[idx][i].l);
		pos.push_back(vec[idx][i].r);
	}

	sort(pos.begin(), pos.end());
	build(1, 0, pos.size());

	ll ret = 0;
	for (int i = 0; i < vec[idx].size(); i++) {
		modify(1, find(vec[idx][i].l), find(vec[idx][i].r) - 1, vec[idx][i].d);
		if (i + 1 != vec[idx].size())
			ret += 1LL * s[1] * (vec[idx][i+1].x - vec[idx][i].x);
	}
	return ret;

}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		ll ans = 0;
		for (int i = 1; i <= M; i++)
			ans += 1LL * (H[i].first - H[i-1].first) * solve(i);
		printf("Case %d: %I64d\n", kcas, ans);
	}
	return 0;
}

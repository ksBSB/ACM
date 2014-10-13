#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 1250005;
const double eps = 1e-9;

int N;
vector<int> pos;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2];
double nd[maxn << 2], ad[maxn << 2], sm[maxn << 2];

inline int length(int u) {
	return pos[rc[u]+1] - pos[lc[u]];
}

inline void maintain(int u, double a, double d) {
//	printf("maintain: %d>%d %d>%d %lf %lf\n", lc[u], pos[lc[u]], rc[u], pos[rc[u] + 1], a, d);
	nd[u] += a;
	ad[u] += d;
	int n = length(u);
	sm[u] += a * n + (d * (n-1) * n / 2.0);
}

inline void pushup(int u) {
	sm[u] = sm[lson(u)] + sm[rson(u)];
}

inline void pushdown(int u) {
	if (fabs(ad[u]) < eps && fabs(nd[u]) < eps)
		return;

	maintain(lson(u), nd[u], ad[u]);
	maintain(rson(u), nd[u] + ad[u] * length(lson(u)), ad[u]);
	nd[u] = ad[u] = 0;
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	nd[u] = ad[u] = sm[u] = 0;

	if (l == r)
		return;

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid+1, r);
	pushup(u);
}

void modify(int u, int l, int r, double a, double d) {
	if (l <= lc[u] && rc[u] <= r) {
		maintain(u, a + (pos[lc[u]] - pos[l]) * d, d);
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		modify(lson(u), l, r, a, d);
	if (r > mid)
		modify(rson(u), l, r, a, d);
	pushup(u);
}

double query(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return sm[u];

	pushdown(u);
	double ret = 0;
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		ret += query(lson(u), l, r);
	if (r > mid)
		ret += query(rson(u), l, r);
	pushup(u);
	return ret;
}

struct OP {
	int type;
	int x[10], y[10];
	void read () {
		char tmp[5];
		scanf("%s", tmp);
		if (tmp[0] == 'Q')
			type = 1;
		else
			scanf("%d", &type);

		for (int i = 0; i < type; i++) {
			scanf("%d%d", &x[i], &y[i]);
			pos.push_back(x[i]);
		}

		if (type == 1)
			pos.push_back(y[0]);
	}
}op[25005];

inline int find (int k) {
	return lower_bound(pos.begin(), pos.end(), k) - pos.begin();
}

int  main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		pos.clear();
		for (int i = 0; i < N; i++)
			op[i].read();
		sort(pos.begin(), pos.end());

		build(1, 0, pos.size());
		for (int i = 0; i < N; i++) {
			if (op[i].type == 1) {
				int l = find(op[i].x[0]), r = find(op[i].y[0]);
				printf("%.3lf\n", query(1, l, r - 1));
			} else {
				for (int j = 0; j < op[i].type; j++) {
					int t = (j + 1) % op[i].type, flag = -1;
					int l = find(op[i].x[j]), r = find(op[i].x[t]);

					double d = (op[i].y[j] - op[i].y[t]) * 1.0 / abs(pos[l] - pos[r]);
					double a = (l > r ? op[i].y[t] + d / 2 : op[i].y[j] - d / 2);

					if (l > r) {
						swap(l, r);
						flag = 1;
					}
//					printf("%d %d %d %d %lf %lf\n", op[i].x[j], op[i].y[j], op[i].x[t], op[i].y[t], a * flag, d);
					modify(1, l, r - 1, a * flag, d);
				}
			}
		}
	}
	return 0;
}

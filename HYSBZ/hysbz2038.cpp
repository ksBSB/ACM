#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 50005;

struct State {
	int l, r, id;
}Q[maxn];

int N, M, W[maxn], C[maxn], BSZ;
ll S, ans[maxn], sum[maxn];

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a%b); }

bool cmp(const State& a, const State& b) {
	if (a.l / BSZ == b.l / BSZ) return a.r < b.r;
	return a.l / BSZ < b.l / BSZ;
}

void init () {
	S = 0;
	BSZ = sqrt(N) + 0.5;
	memset(C, 0, sizeof(C));
	for (int i = 1; i <= N; i++) scanf("%d", &W[i]);

	for (int i = 1; i <= M; i++) {
		scanf("%d%d", &Q[i].l, &Q[i].r);
		Q[i].id = i;
	}
	sort(Q + 1, Q + N + 1, cmp);
}

ll query(int u, int v) {

	if (u) {
		for (int i = Q[u].l; i < Q[v].l; i++) {
			C[W[i]]--;
			S -= C[W[i]];
		}
		for (int i = Q[v].l; i < Q[u].l; i++) {
			S += C[W[i]];
			C[W[i]]++;
		}
		for (int i = Q[u].r + 1; i <= Q[v].r; i++) {
			S += C[W[i]];
			C[W[i]]++;
		}
		for (int i = Q[v].r + 1; i <= Q[u].r; i++) {
			C[W[i]]--;
			S -= C[W[i]];
		}
	} else {
		for (int i = Q[v].l; i <= Q[v].r; i++) {
			S += C[W[i]];
			C[W[i]]++;
		}
	}
	return S;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		init();
		for (int i = 1; i <= N; i++) {
			ans[Q[i].id] = query(i-1, i);
			sum[Q[i].id] = Q[i].r - Q[i].l + 1;
		}

		for (int i = 1; i <= M; i++) {
			sum[i] = sum[i] * (sum[i]-1) / 2;
			ll g = gcd(ans[i], sum[i]);
			printf("%lld/%lld\n", ans[i] / g, sum[i] / g);
		}
	}
	return 0;
}

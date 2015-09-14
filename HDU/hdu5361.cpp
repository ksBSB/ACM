#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 2 * 1e5 + 5;
const ll inf = 1LL << 60;

struct Pi {
	int pos;
	ll dis;
	Pi (int pos = 0, ll dis = 0): pos(pos), dis(dis) {}
	bool operator < (const Pi& u) const {
		return dis > u.dis;
	}
};

int N, L[maxn], R[maxn], C[maxn], F[maxn];
ll D[maxn];

int find (int x) {
	return F[x] = (F[x] == x ? x : find(F[x]));
}

void init () {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		F[i] = i;
		D[i] = inf;
	}
	for (int i = 1; i <= N; i++)
		scanf("%d", &L[i]);
	for (int i = 1; i <= N; i++)
		scanf("%d", &R[i]);
	for (int i = 1; i <= N; i++)
		scanf("%d", &C[i]);
}

void solve (int s) {
	D[s] = C[s];
	priority_queue<Pi> Q;
	Q.push(Pi(s, D[s]));

	while (!Q.empty()) {
		int u = Q.top().pos;
		Q.pop();

		for (int i = -1; i <= 1; i += 2) {
			int lp = u + L[u] * i;
			int rp = u + R[u] * i;
			if (lp > rp)
				swap(lp, rp);

			lp = max(lp, 1);
			lp = min(lp, N + 1);

			if (lp > rp)
				continue;

			while (true) {
				lp = find(lp);
				if (lp <= 0 || lp > N || lp > rp)
					break;
				if (D[lp] > D[u] + C[lp]) {
					D[lp] = D[u] + C[lp];
					Q.push(Pi(lp, D[lp]));
				}
				F[find(lp)] = find(lp + 1);
				lp++;
			}
		}
	}

	printf("0");
	for (int i = 2; i <= N; i++)
		printf(" %I64d", D[i] == inf ? -1 : D[i] - C[i]);
	printf("\n");
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve(1);
	}
	return 0;
}

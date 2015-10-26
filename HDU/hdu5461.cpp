#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int N, A, B, T, aidx[2], bidx[2];
ll amax[2], bmax[2];

void update (ll x, int u, ll* m, int* idx) {
	if (m[1] < x) {
		swap(m[1], x);
		swap(idx[1], u);
	}

	if (m[0] < m[1]) {
		swap(m[0], m[1]);
		swap(idx[0], idx[1]);
	}
}

ll solve () {
	if (aidx[0] == bidx[0])
		return max(amax[0] + bmax[1], amax[1] + bmax[0]);
	return amax[0] + bmax[0];
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		amax[0] = amax[1] = bmax[0] = bmax[1] = -inf;

		scanf("%d%d%d", &N, &A, &B);
		for (int i = 0; i < N; i++) {
			scanf("%d", &T);
			update(1LL * T * T * A, i, amax, aidx);
			update(1LL * T * B, i, bmax, bidx);
		}
		printf("Case #%d: %lld\n", kcas, solve());
	}
	return 0;
}

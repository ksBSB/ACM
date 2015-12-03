#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 10005;

int N, R, L[maxn], T[maxn], W[maxn], H[maxn];
ll S;

ll get(int x) {
	ll ret = 0;
	for (int i = 0; i < N; i++)
		ret += 1LL * H[i] * max(min(W[i], x - L[i]), 0);
	return ret;
}

int solve () {
	int l = 0, r = R + 1;
	while (l < r) {
		int mid = (l + r) >> 1;
		ll tmp = get(mid);
		if (tmp >= S - tmp) r = mid;
		else l = mid + 1;
	}

	ll ans = get(r);
	l = 0, r = R + 1;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (get(mid) > ans) r = mid;
		else l = mid + 1;
	}
	return l - 1;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		S = 0;
		scanf("%d%d", &R, &N);
		for (int i = 0; i < N; i++) {
			scanf("%d%d%d%d", &L[i], &T[i], &W[i], &H[i]);
			S += 1LL * W[i] * H[i];
		}
		printf("%d\n", solve());
	}
	return 0;
}

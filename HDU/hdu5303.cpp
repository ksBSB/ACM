#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;

int L, N, K;
ll disl[maxn], disr[maxn];
vector<int> l, r;

ll solve () {
	sort(l.begin(), l.end());
	sort(r.begin(), r.end());
	int sil = l.size(), sir = r.size();
	for (int i = 0; i < sil; i++)
		disl[i + 1] = (i + 1 <= K ? l[i] : disl[i + 1 - K] + l[i]);
	for (int i = 0; i < sir; i++)
		disr[i + 1] = (i + 1 <= K ? r[i] : disr[i + 1 - K] + r[i]);
	ll ans = (disl[sil] + disr[sir]) * 2;

	for (int i = 0; i <= sil && i <= K; i++) {
		int p = max(0, sir - (K - i));
		ans = min(ans, 2 * (disl[sil - i] + disr[p]) + L);
	}

	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		l.clear();
		r.clear();
		int x, a;
		scanf("%d%d%d", &L, &N, &K);

		for (int i = 0; i < N; i++) {
			scanf("%d%d", &x, &a);
			for (int j = 0; j < a; j++) {
				if (2 * x <= L)
					l.push_back(x);
				else
					r.push_back(L - x);
			}
		}
		printf("%lld\n", solve());
	}
	return 0;
}

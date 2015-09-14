#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

const int maxn = 50005;

int N, M, A[maxn], C[maxn];

void init () {
	int l, r;
	memset(C, 0, sizeof(C));
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%d", &A[i]);

	for (int i = 0; i < M; i++) {
		scanf("%d%d", &l, &r);
		C[l]++, C[r+1]--;
	}
}

ll handle(ll x) { return x * (x-1) * (x-2) / 2 / 3; }
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a%b); }

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();
		if (M < 3) {
			printf("0\n");
			continue;
		}
	
		int cnt = 0;
		ll ans = 0, c = handle(M);
		for (int i = 1; i <= N; i++) {
			cnt += C[i];
			if (cnt < 3) continue;
			ans += 1LL * A[i] * handle(cnt);
		}

		ll d = gcd(ans, c);

		ans /= d;
		c /= d;
		if (c != 1)
			printf("%lld/%lld\n", ans, c);
		else
			printf("%lld\n", ans);
	}
	return 0;
}

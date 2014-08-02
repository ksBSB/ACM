#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

const ll INF = 1e18+1;
ll N, ten[20];

void init () {
	ten[0] = 1;
	for (int i = 1; i < 20; i++)
		ten[i] = ten[i-1] * 10;
}

inline ll gcd (ll a, ll b) {
	return b == 0 ? a : gcd(b, a%b);
}

inline int tenbit (ll n) {
	int cnt = 0;
	while (n) {
		n /= 10;
		cnt++;
	}
	return cnt;
}

ll solve () {
	ll ans = INF;
	int bit = tenbit(N);

	if (bit == 1)
		return 11L;

	for (int i = 1; i <= bit; i++) {
		ll u = ten[i] + 1;

		while (true) {
			ll d = gcd(N, u);

			ll a = N / d;
			ll k = u / d;


			if (a < ten[i]) {

				if (a < ten[i-1])
					a = ten[i-1] / a + (ten[i-1] % a ? 1 : 0);
				else
					a = 1;

				if (a * k < ans)
					ans = k * a;
			}

			if (INF / u < ten[i])
				break;

			u = u * ten[i] + 1;
		}
	}
	return ans;
}

int main () {
	init();

	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%lld", &N);
		while (N >= 1e9);
		printf("%lld\n", solve() * N);
	}
	return 0;
}

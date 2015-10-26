#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 100005;
const int mod = 1e9 + 7;

struct Point {
	int x, y;
	Point(int x = 0, int y = 0): x(x), y(y) {}
	void read () { scanf("%d%d", &x, &y); }
	int operator * (const Point& u) { return (1LL * x * u.y % mod - 1LL * y * u.x % mod + mod) % mod; }
	Point operator * (const int u) { return Point(1LL * u * x % mod, 1LL * u * y % mod); }
	Point operator + (const Point& u) { return Point((x+u.x)%mod, (y+u.y)%mod); }
};

int N, mul[maxn], inv[maxn];

int mul_mod(ll x, int n, int mod) {
	int ret = 1;
	while (n) {
		if (n&1) ret = x * ret % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}

int main () {
	mul[0] = inv[0] = 1;
	for (int i = 1; i < maxn; i++) mul[i] = 2 * mul[i-1] % mod;
	ll inv2 = mul_mod(2, mod-2, mod);
	for (int i = 1; i < maxn; i++) inv[i] = inv2 * inv[i-1] % mod;

	int cas;
	scanf("%d", &cas);
	while (cas--) {
		int ans = 0;
		scanf("%d", &N);
		Point fi, fg, fh;
		for (int i = 1; i <= N; i++) {
			fi.read();
			ans = (ans + 1LL * mul[i-1] * (fi * fh) % mod) % mod;
		   	ans = (ans + 1LL * (i==N?inv2:mul[N-i-1]) * (fg * fi) % mod) % mod;
			fg = fg + fi * mul[i];
			fh = fh + fi * inv[i];
		}
		printf("%d\n", ans);
	}
	return 0;
}

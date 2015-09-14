#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 100005;
const ll mod = 365 * 24 * 60 * 60;

struct point {
	ll a, b;
}p[maxn];
int N;

bool cmp (const point& A, const point& B) {
	return A.b * B.a > B.b * A.a;
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		for (int i = 0; i < N; i++)
			scanf("%I64d%I64d", &p[i].a, &p[i].b);
		sort(p, p + N, cmp);

		ll t = 0;
		for (int i = 0; i < N; i++) {
			ll u = (p[i].a + p[i].b * t % mod) % mod;
			t = (t + u) % mod;
		}
		printf("%I64d\n", t);
	}
	return 0;
}

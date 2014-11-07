#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;
const int maxn = 1e5 + 5;

struct Tire {
	int sz, g[maxn * 100][2];

	void init();
	void insert(ll s);
	ll find(ll s);
}T;

int N;
ll A[maxn], prefix[maxn], suffix[maxn];

int main () {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%lld", &A[i]);

	for (int i = 1; i <= N; i++)
		prefix[i] = prefix[i-1] ^ A[i];
	for (int i = N; i; i--)
		suffix[i] = suffix[i+1] ^ A[i];

	ll ans = 0;
	T.init();

	for (int i = N; i >= 0; i--) {
		T.insert(suffix[i+1]);
		ans = max(ans, T.find(prefix[i]));
	}
	printf("%lld\n", ans);
	return 0;
}

void Tire::init() {
	sz = 1;
	memset(g[0], 0, sizeof(g[0]));
}

void Tire::insert(ll s) {
	int u = 0;

	for (int i = 60; i >= 0; i--) {
		int v = (s>>i)&1;

		if (g[u][v] == 0) {
			memset(g[sz], 0, sizeof(g[sz]));
			g[u][v] = sz++;
		}
		u = g[u][v];
	}
}

ll Tire::find (ll s) {
	int u = 0;
	ll ret = 0;

	for (int i = 60; i >= 0; i--) {
		int v = ((s>>i)&1) ^ 1;

		if (g[u][v])
			ret |= (1LL<<i);
		else
			v = v ^ 1;
		u = g[u][v];
	}
	return ret;
}

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1000000;
const double logt = log(10.0);

int N;
double g[maxn+5], s[maxn+5];
int phi[maxn+5];

void phi_table (int n) {
	memset(phi, 0, sizeof(phi));
	phi[1] = 1;

	for (int i = 2; i <= n; i++) {
		if (!phi[i]) {
			for (int j = i; j <= n; j += i) {
				if (!phi[j])
					phi[j] = j;
				phi[j] = phi[j] / i * (i-1);
			}
		}
	}
}

void init (ll n) {

	for (int i = 1; i <= n; i++) {
		double tmp = log(i);
		for (int j = 2 * i; j <= n; j += i)
			g[j] += phi[j/i] * tmp;
	}

	for (int i = 1; i <= n; i++)
		g[i] += g[i-1];
	for (int i = 1; i <= n; i++)
		g[i] /= logt;
}

int main () {
	phi_table(maxn);
	init(maxn);

	int cas = 1;
	while (scanf("%d", &N) == 1 && N) {
		double ans = 0;
		for (int i = 1; i <= N; i++)
			ans += (N-1) * log(i);
		ans /= logt;
		ans -= g[N];
		printf("Case %d: %lld %lld\n", cas++, (ll)(g[N] / 100) + 1, (ll)(ans / 100) + 1);
	}
	return 0;
}

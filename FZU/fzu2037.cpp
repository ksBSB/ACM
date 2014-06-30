#include <stdio.h>
#include <algorithm>

using namespace std;

typedef long long ll;
const int N = 1000005;
const ll mod = 1000000007; 

ll t[N], f[N];
double p[N];

void init() {
	f[1] = t[1] = 1;
	p[1] = 1;
	for (ll i = 2; i < N; i++) {
		f[i] = (f[i - 1] * i + t[i - 1]) % mod;
		t[i] = (t[i - 1] * i) % mod;
		p[i] = p[i - 1] + 1.0 / i;
	}
}

int main () {
	init();
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		int n; scanf("%d", &n);
		printf("Case %d: %lld %.6lf\n", i, f[n], p[n]);
	}
	return 0;
}

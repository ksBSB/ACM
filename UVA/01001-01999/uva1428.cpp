#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define lowbit(x) ((x)&(-x))
const int maxn = 1e5;
typedef long long ll;

int n, s[maxn+5];
int N, a[maxn+5];
ll b[maxn+5];

void add (int x, int v) {
	while (x <= n) {
		s[x] += v;
		x += lowbit(x);
	}
}

int sum (int x) {
	int ret = 0;
	while (x > 0) {
		ret += s[x];
		x -= lowbit(x);
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);

		n = 0;
		memset(s, 0, sizeof(s));
		for (int i = 1; i <= N; i++) {
			scanf("%d", &a[i]);
			n = max(a[i], n);
		}
		
		for (int i = 1; i <= N; i++) {
			b[i] = sum(a[i]-1);
			//printf("%lld ", b[i]);
			add(a[i], 1);
		}
		//printf("\n");

		ll ans = 0;
		memset(s, 0, sizeof(s));
		for (int i = N; i > 0; i--) {
			ll d = sum(a[i]-1);
			add(a[i], 1);
			ans += (b[i] * (N - i - d)) + d * (i - 1 - b[i]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}

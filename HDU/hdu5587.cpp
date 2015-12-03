#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 55;
typedef unsigned long long ll;

ll N, cnt[maxn+5], sum[maxn+5];

ll solve (ll n) {
	int t = maxn;
	ll ret = 0, add = 0;
	while (n) {
		while (cnt[t] > n) t--;
		ret += sum[t] + cnt[t] * add;
		n -= cnt[t];
		add++;
		if (n) { n--, ret += add; }
	}
	return ret;
}

int main () {
	cnt[1] = sum[1] = 1;
	for (int i = 2; i <= maxn; i++) {
		cnt[i] = cnt[i-1] * 2 + 1;
		sum[i] = sum[i-1] * 2 + cnt[i-1] + 1;
	//	printf("%d %lld %lld\n", i, cnt[i], sum[i]);
	}

	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%llu", &N);
		printf("%llu\n", solve(N));
	}
	return 0;
}

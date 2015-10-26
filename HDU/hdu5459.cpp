#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 201314;
const int mod = 530600414;

ll dis[maxn+5], len[maxn+5], cnt[maxn+5], sum[maxn+5];

void init () {
	len[1] = cnt[1] = 1;
	dis[1] = sum[1] = 0;

	len[2] = 2, cnt[2] = 0;
	dis[2] = sum[2] = 0;

	for (int i = 3; i <= maxn; i++) {
		dis[i] = (dis[i-2] + dis[i-1] + cnt[i-1] * len[i-2] % mod) % mod;
		len[i] = (len[i-1] + len[i-2]) % mod;
		cnt[i] = (cnt[i-1] + cnt[i-2]) % mod;
		ll add = cnt[i-2] * (dis[i-1] + cnt[i-1] * len[i-2] % mod) % mod;
		ll del = cnt[i-1] * dis[i-2] % mod;
		sum[i] = ((sum[i-1] + sum[i-2] + add - del) % mod + mod) % mod;
	}
}

int main () {
	init();

	int cas, n;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d", &n);
		printf("Case #%d: %lld\n", kcas, sum[n]);
	}
	return 0;
}

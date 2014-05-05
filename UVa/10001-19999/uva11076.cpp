#include <stdio.h>
#include <string.h>

const int N = 105;
typedef unsigned long long ll;

int n;
ll C[N][N], cnt[N];

void init () {
	C[0][0] = 1;
	for (int i = 1; i <= 12; i++) {
		for (int j = 0; j <= i; j++)
			C[i][j] = C[i-1][j] + C[i-1][j-1];
	}
}

ll count () {
	int k = n - 1;
	ll t = 1;
	for (int i = 0; i < 10; i++) {
		t *= C[k][cnt[i]];
		k -= cnt[i];
	}
	return t;
}

ll solve () {
	ll tmp = 0;	
	for (ll i = 0; i < 10; i++) {
		if (cnt[i]) {
			cnt[i]--;
			ll t = count();
			cnt[i]++;
			tmp += i * t;
		}
	}

	ll ans = 0;
	for (int i = 0; i < n; i++)
		ans = ans * 10 + tmp;
	return ans;
}

int main () {
	init ();
	while (scanf("%d", &n), n) {
		memset(cnt, 0, sizeof(cnt));
		int a;
		for (int i = 0; i < n; i++) {
			scanf("%d", &a);
			cnt[a]++;
		}
		printf("%lld\n", solve ());
	}
	return 0;
}

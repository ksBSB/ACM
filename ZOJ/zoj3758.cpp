#include <stdio.h>
#include <string.h>

typedef unsigned long long ll;

bool judge(ll k) {
	if (k == 1) return false;
	for (ll i = 2; i*i <= k; i++) {
		if (k % i == 0) return false;
	}
	return true;
}

int main () {
	int n;
	ll bas, ans;

	while (scanf("%lld%d", &bas, &n) == 2) {
		ans = 1;
		for (int i = 0; i < n; i++) ans *= bas;
		ans = (ans-1)/(bas-1);
		printf("%s\n", judge(ans) ? "YES" : "NO");
	}
	return 0;
}

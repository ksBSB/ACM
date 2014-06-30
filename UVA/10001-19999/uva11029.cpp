#include <stdio.h>
#include <math.h>
int n, k;

long long pow_mod(long long a, long long c) {
	if (c == 1) return a % 1000;
	long long ans = pow_mod(a, c / 2);
	ans = (ans * ans) % 1000;
	return c % 2 ? (ans * a) % 1000 : ans;
}

void solve() {
	int l = (int) pow(10, 2 + fmod(k * log10(n), 1));
	int r = pow_mod(n, k);
	printf("%d...%03d\n", l, r);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &n, &k);
		solve();
	}
	return 0;
}

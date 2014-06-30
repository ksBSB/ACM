#include <stdio.h>
#include <string.h>

const int N = 1e5+5;
const int MOD = 10007;

int n, jump[N*2];
char s[N*2];

int getCnt (int p) {
	int ans = 0;
	while (p) {
		ans++;
		p = jump[p];
	}
	return ans;
}

int getJump () {
	int p = 0, ans = n % MOD;

	for (int i = 2; i <= n; i++) {
		while (p > 0 && s[p+1] != s[i])
			p = jump[p];

		if (s[p+1] == s[i])
			p++;

		jump[i] = p;
		ans = (ans + getCnt(p)) % MOD;
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%s", &n, s+1);
		printf("%d\n", getJump());
	}
	return 0;
}

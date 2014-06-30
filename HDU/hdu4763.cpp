#include <stdio.h>
#include <string.h>

const int N = 1e6+5;

int n, jump[N];
char s[N];

void getJump () {
	int p = 0;
	for (int i = 2; i <= n; i++) {
		while (p > 0 && s[p+1] != s[i])
			p = jump[p];

		if (s[p+1] == s[i])
			p++;
		jump[i] = p;
	}
}

bool KMP (int l, int r, int k) {
	int p = 0;
	for (int i = l; i <= r; i++) {
		while (p > 0 && s[p+1] != s[i])
			p = jump[p];

		if (s[p+1] == s[i])
			p++;

		if (p == k) return true;
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s", s+1);

		n = strlen(s+1);

		getJump ();
		int p = jump[n];
		while (p) {
			if (p <= n/3 && KMP (p+1, n-p, p)) break;
			p = jump[p];
		}
		printf("%d\n", p);
	}
	return 0;
}

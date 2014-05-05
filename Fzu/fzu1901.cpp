#include <stdio.h>
#include <string.h>

const int N = 1e6+5;

int n, jump[N], ans[N];
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

void solve () {
	int c = 0, p = n;
	while (p) {
		p = jump[p];
		ans[c++] = p;
	}

	printf("%d\n", c);
	printf("%d", n-ans[0]);
	for (int i = 1; i < c; i++)
		printf(" %d", n-ans[i]);
	printf("\n");
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		scanf("%s", s+1);

		n = strlen(s+1);

		getJump ();

		printf("Case #%d: ", i);
		solve ();
	}
	return 0;
}

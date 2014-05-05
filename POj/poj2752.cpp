#include <stdio.h>
#include <string.h>

const int N = 1e5+5;

int n, ans[N*4], jump[N*4];
char s[N*4];

void getJump () {
	n = strlen (s+1);
	int p = 0;
	for (int i = 2; i <= n; i++) {
		while (p > 0 && s[p+1] != s[i])
			p = jump[p];
		if (s[p+1] == s[i])
			p++;
		jump[i] = p;
	}
}

int main () {
	while (scanf("%s", s+1) == 1) {
		getJump ();
		int p = n, c = 0;
		while (p) {
			ans[c++] = p;
			p = jump[p];
		}
		printf("%d", ans[c-1]);
		for (int i = c-2; i >= 0; i--)
			printf(" %d", ans[i]);
		printf("\n");
	}
	return 0;
}

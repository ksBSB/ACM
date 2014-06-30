#include <stdio.h>
#include <string.h>

const int N = 1e6+5;

int n, next[N];
char s[N];

void getNext () {
	int p = 0;
	for (int i = 2; i <= n; i++) {
		while (p > 0 && s[p+1] != s[i])
			p = next[p];

		if (s[p+1] == s[i])
			p++;

		next[i] = p;

		if (p) {
			int k = i - next[i];
			if (i%k == 0)
				printf("%d %d\n", i, i/k);
		}
	}
}

int main () {
	int cas = 1;
	while (scanf("%d", &n) == 1 && n) {
		scanf("%s", s+1);
		printf("Test case #%d\n", cas++);
		getNext();
		printf("\n");
	}
	return 0;
}

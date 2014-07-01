#include <stdio.h>
#include <string.h>

const int N = 1000005;

int n, next[N];
char s[N];

void getNext () {
	int p = 0;
	n = strlen(s+1);
	for (int i = 2; i <= n; i++) {
		while (p > 0 && s[p+1] != s[i])
			p = next[p];

		if (s[p+1] == s[i])
			p++;

		next[i] = p;
	}
}

int main () {
	while (scanf("%s", s+1) == 1 && strcmp(s+1, ".") ) {
		getNext ();
		int k = n - next[n];
		printf("%d\n", n%k == 0 ? n/k : 1);
	}
	return 0;
}

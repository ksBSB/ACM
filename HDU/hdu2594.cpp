#include <stdio.h>
#include <string.h>
#define min(a,b) (a)<(b)?(a):(b)

const int N = 1e5+5;

int n, m, next[N];
char s1[N], s2[N];

void getNext () {
	int p = 0;
	m = strlen(s1+1);
	for (int i = 2; i <= m; i++) {
		while (p > 0 && s1[p+1] != s1[i])
			p = next[p];

		if (s1[p+1] == s1[i])
			p++;

		next[i] = p;
	}
}

int main () {
	while (scanf("%s%s", s1+1, s2+1) == 2) {
		n = min (strlen(s1+1), strlen(s2+1));
		strcat (s1+1, s2+1);

		getNext ();

		while(n < next[m]) {
			m = next[m];
		}

		int ans = next[m];
		for (int i = 1; i <= ans; i++) printf("%c", s1[i]);
		if (ans) printf(" ");
		printf("%d\n", ans);
	}
	return 0;
}

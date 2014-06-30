#include <stdio.h>
#include <string.h>

const int N = 1e5+5;

int n, m, next[N];
char s1[2*N], s2[N], tmp[N];

void getNext () {
	int p = 0;
	for (int i = 2; i <= m; i++) {
		while (p > 0 && s2[p+1] != s2[i])
			p = next[p];

		if (s2[p+1] == s2[i])
			p++;

		next[i] = p;
	}
}

bool KMP () {
	getNext ();
	strcpy(tmp, s1+1);
	strcat(s1+1, tmp);
    n = strlen(s1+1);
	int p = 0;
	for (int i = 1; i <= n; i++) {
		while (p > 0 && s2[p+1] != s1[i])
			p = next[p];

		if (s2[p+1] == s1[i])
			p++;

		if (p == m) return true;
	}
	return false;
}

int main () {
	while (scanf("%s%s", s1+1, s2+1) == 2) {
		n = strlen(s1+1);
		m = strlen(s2+1);
		printf("%s\n", n >= m && KMP() ? "yes" : "no");
	}
	return 0;
}

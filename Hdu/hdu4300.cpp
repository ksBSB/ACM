#include <stdio.h>
#include <string.h>

const int N = 1e5+5;

int n, jump[N];
char t[30], v[30], s[N], f[N];

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

int KMP () {
	int p = 0;
	for (int i = 1; i <= n; i++) {
		while (p > 0 && s[p+1] != f[i])
			p = jump[p];

		if (s[p+1] == f[i])
			p++;

		if (p == n)
			p = jump[p];
	}

	while (n - p < p)
		p = jump[p];
	return p;
}

void init () {
	scanf("%s%s", t, f+1);
	n = strlen (f+1);
	for (int i = 0; i < 26; i++)
		v[t[i]-'a'] = i + 'a';

	for (int i = 1; i <= n; i++)
		s[i] = v[f[i]-'a'];

	s[n+1] = '\0';
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();

		getJump ();
		int k = n - KMP ();
		for (int i = 1; i <= k; i++)
			printf("%c", f[i]);
		for (int i = 1; i <= k; i++)
			printf("%c", v[f[i]-'a']);
		printf("\n");
	}
	return 0;
}

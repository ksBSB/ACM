#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 105;
int n, len[N], m, jump[N];
char s[N][N], f[N][N], t[N];

void init () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", s[i]+1);
		len[i] = strlen (s[i]+1);

		for (int j = 1; j <= len[i]; j++)
			f[i][j] = s[i][len[i]-j+1];
	}
}

void getJump () {

	int p = 0;
	for (int i = 2; i <= m; i++) {
		while (p > 0 && t[p+1] != t[i])
			p = jump[p];

		if (t[p+1] == t[i])
			p++;

		jump[i] = p;
	}
}

int KMP (int j) {
	int ans = 0, p = 0;
	for (int i = 1; i <= len[j]; i++) {
		while (p > 0 && t[p+1] != s[j][i])
			p = jump[p];

		if (t[p+1] == s[j][i])
			p++;

		ans = max(ans, p);
		if (p == m) p = jump[p];
	}

	p = 0;
	for (int i = 1; i <= len[j]; i++) {
		while (p > 0 && t[p+1] != f[j][i])
			p = jump[p];

		if (t[p+1] == f[j][i])
			p++;

		ans = max(ans, p);
		if (p == m) p = jump[p];
	}

	return ans;
}

int solve () {
	int ans = 0;

	for (int i = 1; i <= len[0]; i++) {
		strcpy (t+1, s[0]+i);
		m = strlen(t+1);

		int tmp = m;
		getJump ();
		for (int j = 1; j < n; j++)
			tmp = min (tmp, KMP (j));

		ans = max(ans, tmp);
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();
		printf("%d\n", solve ());
	}
	return 0;
}

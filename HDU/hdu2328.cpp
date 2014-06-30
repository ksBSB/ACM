#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 4005;
const int M = 205;

int n, m, len, jump[M];
char s[N][M], str[M];

void getJump () {
	int p = 0;
	for (int i = 2; i <= m; i++) {
		while (p > 0 && str[p+1] != str[i])
			p = jump[p];

		if (str[p+1] == str[i])
			p++;

		jump[i] = p;
	}
}

int KMP (int j) {
	int ans = 0, p = 0;
	for (int i = 1; i <= len; i++) {
		while (p > 0 && str[p+1] != s[j][i])
			p = jump[p];

		if (str[p+1] == s[j][i])
			p++;

		ans = max(p, ans);
		if (p == m) break;
	}
	return ans;
}

bool judge (int p, int q, int k) {
	for (int i = 0; i < k; i++) {
		if (s[0][p+i] != s[0][q+i])
			return s[0][p+i] < s[0][q+i];
	}
	return true;
}

void solve () {
	int ans = 0, rec = 0;
	len = strlen(s[0]+1);;

	for (int i = 1; i < len; i++) {

		strcpy (str+1, s[0]+i);
		m = strlen (str+1);

		getJump ();

		int tmp = len;
		for (int j = 1; j < n; j++)
			tmp = min(tmp, KMP(j));

		if (tmp > ans || (tmp == ans && judge (i, rec, ans))) {
			ans = tmp;
			rec = i;
		}
	}

	if (ans) {
		for (int i = 0; i < ans; i++) 
			printf("%c", s[0][i+rec]);
		printf("\n");
	} else {
		printf("IDENTITY LOST\n");
	}
}

int main () {
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			scanf("%s", s[i]+1);
		solve ();
	}
	return 0;
}

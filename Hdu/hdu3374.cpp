#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 1e6+5;

int n, jump[N];
char s[N*2], Min[N], Max[N], t[N];

inline bool cmp (char a, char b, int id) {
	if (id)
		return a < b;
	else
		return a > b;
}

int getString (int id) {
	int i = 0, j = 1, k = 0;
	while (i + k < n && j + k < n) {
		if (s[i+k] == s[j+k]) {
			k++;
		} else {
			if (cmp (s[i+k], s[j+k], id))
				i = i + k + 1;
			else 
				j = j + k + 1;
			k = 0;
			if (i == j) j++;
		}
	}
	return min (i, j);
}

void getJump (char* f) {
	int p = 0;
	for (int i = 2; i <= n/2; i++) {
		while (p > 0 && f[p+1] != f[i])
			p = jump[p];

		if (f[p+1] == f[i])
			p++;

		jump[i] = p;
	}
}

int KMP (char* f) {
	int p = 0, ans = 0;
	for (int i = 1; i <= n; i++) {
		while (p > 0 && f[p+1] != s[i])
			p = jump[p];

		if (f[p+1] == s[i])
			p++;

		if (p == n/2) {
			ans++;
			p = jump[p];
		}
	}
	return ans;
}

int main () {
	while (scanf("%s", t) == 1) {
		strcpy (s, t);
		strcat (s, t);
		n = strlen(s);
		int l = getString(0);
		int r = getString(1);

		strncpy (Min+1, s+l, n/2);
		strncpy (Max+1, s+r, n/2);

		getJump (Min);
		int cl = KMP (Min);

		getJump (Max);
		int cr = KMP (Max);

		printf("%d %d %d %d\n", l+1, cl, r+1, cr);
	}
	return 0;
}

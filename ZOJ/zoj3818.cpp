#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
char s[105];

bool check (int a, int b, int l) {
	for (int i = 0; i < l; i++)
		if (s[a + i] != s[b + i])
			return false;
	return true;
}

bool judge (int l, int r, int flag) {
	int a = l + r;
	if (flag == 1) {

		if (!check(0, a, l) || !check(0, a*2, l))
			return false;

		if (!check(l, l + a, r))
			return false;
	} else {
		int c = n - 3 * a;
		if (!check(0, a, a) || !check(0, a*2+c, a))
			return false;

		if (l == c && check(0, 2*a, c))
			return false;

		if (r == c && check(l, 2*a, c))
			return false;
	}

	if (l == r && l == 1 && s[0] == s[1])
		return false;
	return true;
}

bool solve () {

	scanf("%s", s);
	n = 0;
	int len = strlen(s);
	for (int i = 0; i < len; i++)
		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
			s[n++] = s[i];
	s[n] = '\0';

	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++) {

			if (3 * i + 2 * j == n && judge(i, j, 1))
				return true;

			if (3 * (i + j) < n && judge(i, j, 2))
				return true;
		}
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		printf("%s\n", solve() ? "Yes" : "No");
	}
	return 0;
}

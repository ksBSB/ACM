#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 50;

int n, m;
char s[maxn], t[maxn];

bool dfs (int l, int r) {

	if (l > n && r > m)
		return true;
	
	if (l > n || r > m)
		return false;

	if (s[l] == '*') {

		while (s[l+1] == '*')
			l++;

		if (s[l+1] == t[r] && dfs(l + 1, r))
			return true;
		return dfs(l, r + 1);
	} else {

		if (s[l] != t[r])
			return false;
		return dfs(l + 1, r + 1);
	}

	return false;
}

bool judge () {
	n = strlen(s);
	m = strlen(t);
	return dfs(0, 0);
}

int main () {
	int cas = 0;
	while (gets(s)) {

		int ret = 0;
		while (gets(t) && t[0] != '\0') {

			if (judge()) {
				if (ret++ == 0) {
					if (cas)
						printf("\n");
					printf("MATCHES FOR THE PATTERN: %s\n", s);
				}
				printf("%s\n", t);
			}
		}
		if (ret)
			cas++;
	}
	return 0;
}

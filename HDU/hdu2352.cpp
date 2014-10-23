#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;

char s[maxn];

inline int idx(char c) {
	if (c == 'I') return 1;
	else if (c == 'V') return 5;
	else if (c == 'X') return 10;
	else if (c == 'L') return 50;
	else if (c == 'C') return 100;
	else if (c == 'D') return 500;
	else if (c == 'M') return 1000;
	return 0;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s", s);
		int ans = 0, len = strlen(s);
		for (int i = 0; i < len; i++) {
			int k = (idx(s[i]) >= idx(s[i+1]) ? 1 : -1);
			ans += k * idx(s[i]);
		}
		printf("%d\n",  ans);
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>

using namespace std;

const int maxn = 1005;
char s[maxn];

int solve () {
	stack<int> sta;

	int len = strlen(s), c = 0;
	for (int i = 0; i < len; i++) {
		if (s[i] == '*')
			c++;
		else
			sta.push(i);
	}

	if (c == 0)
		return 0;

	int n = len - c;
	int ret = n = max(c + 1 - n, 0);

	for (int i = 0; i < len; i++) {
		if (s[i] == '*') {
			if (n <= 1) {
				s[sta.top()] = '*';
				sta.pop();
				n++;
				ret++;
			} else
				n--;
		} else 
			n++;
	}

	if (ret == 0 && s[len-1] != '*')
		ret++;
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s", s);
		printf("%d\n", solve());
	}
	return 0;
}

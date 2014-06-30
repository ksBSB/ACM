#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 1e6+5;
const int INF = 0x3f3f3f3f;

struct state {
	int c, f;
}s[N];
int n;

void init () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &s[i].f);
	for (int i = 0; i < n; i++) scanf("%d", &s[i].c);
	int tmp = INF;
	for (int i = n - 1; i >= 0; i--) {
		tmp = min(tmp, s[i].c);
		tmp = max(tmp, s[i].f);
		s[i].c = tmp;
	}
}

int solve () {
	int ans = 0, tmp = INF;
	for (int i = 0; i < n; i++) {
		tmp = max(tmp, s[i].f);
		tmp = min(tmp, s[i].c);
		s[i].c = tmp;
			
		ans += s[i].c - s[i].f;
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}

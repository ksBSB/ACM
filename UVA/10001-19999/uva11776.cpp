#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 1005;
int n;
struct state {
	int x, y;
}s[N];

bool cmp(const state& a, const state& b) {
	return a.x < b.x;
}

void init() {
	for (int i = 0; i < n; i++) scanf("%d %d", &s[i].x, &s[i].y);
	sort(s, s + n, cmp);
}

int solve() {
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (int j = 0; j < n; j++) {
			if (s[j].x > s[i].y) break;
		    if (s[j].x <= s[i].y && s[j].y >= s[i].y) cnt++;
		}
		ans = max(ans, cnt);
	}
	return ans;
}

int main() {
	int cas = 1;
	while (scanf("%d", &n) == 1 && n != -1) {
		init();
		printf("Case %d: %d\n", cas++, solve());
	}
	return 0;
}

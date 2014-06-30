#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>

using namespace std;
const int N = 150005;
const int INF = 0x3f3f3f3f;

struct state {
	int sum, id, key;
}s[N], c[N];

int n, p, ans, cnt;
char a[N], b[N];

int find (int key) {
	int l = 0, r = cnt - 1;
	while (l < r) {
		int mid = (l + r) / 2;
		if (c[mid].key <= key) r = mid;
		else l = mid+1;
	}
	return c[l].id;
}

bool solve () {
	ans = 0;

	cnt = 1;
	s[0].sum = s[0].id = 0; s[0].key = 0;
	c[0] = s[0];

	for (int i = 1; i <= n; i++) {
		s[i].sum = s[i-1].sum + (a[i-1] != b[i-1]);
		s[i].id = i; s[i].key = i * p - 100 * s[i].sum;

		if (s[i].key < c[cnt-1].key) {
			c[cnt++] = s[i];
		} else {
			int t = find(s[i].key);
			ans = max(ans, s[i].id - t);
		}
	}
	if (ans) return true;
	return false;
}

int main () {
	while (scanf("%d%d", &n, &p) == 2 && n + p) {
		scanf("%s%s", a, b);
		if (solve()) printf("%d\n", ans);
		else printf("No solution.\n");
	}
	return 0;
}

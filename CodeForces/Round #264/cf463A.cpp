#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int n, s, ans = -1, x, y;
	scanf("%d%d", &n, &s);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &x, &y);
		if (x < s || (x == s && y == 0))
			ans = max(ans, y == 0 ? 0 : 100 - y);
	}
	printf("%d\n", ans);
	return 0;
}

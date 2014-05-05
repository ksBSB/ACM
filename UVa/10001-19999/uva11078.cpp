#include <stdio.h>
#include <algorithm>

using namespace std;
const int INF = 0x3f3f3f3f;

int main() {
	int cas, n;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		int ans = -INF, Max = -INF, c;
		for (int i = 0; i < n; i++) {
			scanf("%d", &c);
			ans = max(ans, Max - c);
			Max = max(Max, c);
		}
		printf("%d\n", ans);
	}
	return 0;
}

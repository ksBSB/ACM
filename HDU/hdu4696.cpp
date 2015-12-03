#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int n, m;
	while (scanf("%d%d", &n, &m) == 2) {
		int c = 0, x;
		for (int i = 1; i <= n; i++) scanf("%d", &x);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &x);
			if (x == 1) c = 1;
		}
		for (int i = 0; i < m; i++) {
			scanf("%d", &x);
			if (x > 0 && (c == 1 || (x % 2 == 0)))
				printf("YES\n");
			else printf("NO\n");
		}
	}
	return 0;
}

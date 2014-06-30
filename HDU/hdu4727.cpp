#include <cstdio>
#include <cstring>

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		int n, first, x, ans = 0;
		scanf("%d%d", &n, &first);
		for (int j = 1; j < n; j++) {
			scanf("%d", &x);

			if (ans)
				continue;

			if (x != first + j)
				ans = j;
		}
		printf("Case #%d: %d\n", i, ans+1);
	}
	return 0;
}

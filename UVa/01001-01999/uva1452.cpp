#include <stdio.h>
#include <string.h>

int main () {
	int cas, n, k;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &n, &k);
		int ans1 = 0, ans2, ans3;
		for (int i = 2; i <= n; i++) {
			ans1 = (ans1 + k) % i;
			if (i == 2) ans2 = 1 - ans1;
			else {
				ans2 = (ans2 + k) % i;
				if (i == 3) ans3 = 3 - ans1 - ans2;
				else ans3 = (ans3 + k) % i;
			}
		}
		printf("%d %d %d\n", ans3+1, ans2+1, ans1+1);
	}
	return 0;
}

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main () {
	int cas, n, L, R;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d%d", &n, &L, &R);
		int ans = 0;
		for (int i = L; i <= R; i++)
			ans += n / i;
		printf("%d\n", ans);
	}
	return 0;
}

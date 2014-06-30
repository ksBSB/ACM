#include <stdio.h>

int main () {
	int cas, g, l;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &g, &l);
		if (l%g) {
			printf("-1\n");
		} else
			printf("%d %d\n", g, l);
	}
	return 0;
}

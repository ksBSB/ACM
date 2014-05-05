#include <cstdio>
#include <cstring>

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		int a;
		scanf("%d", &a);
		a /= 10;
		printf("Case #%d:\n", i);
		printf("*------------*\n");
		for (int j = 0; j < 10 - a; j++)
			printf("|............|\n");
		for (int j = 0; j < a; j++)
			printf("|------------|\n");
		printf("*------------*\n");
	}
	return 0;
}

#include <stdio.h>
#include <string.h>

const int N = 10100;
const char sign[2][N] = {"Even", "Odd"};

int main () {
	char str[N];
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		scanf("%s", str);
		int len = strlen(str);
		printf("Case %d: %s\n", i, sign[len % 2]);
	}
	return 0;
}

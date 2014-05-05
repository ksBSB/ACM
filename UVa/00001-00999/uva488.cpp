#include <stdio.h>

void print(int len, int n) {
    while (n--) {
	for (int i = 1; i <= len; i++) {
	    for (int j = 0; j < i; j++)
		printf("%d", i);
	    printf("\n");
	}
	for (int i = len - 1; i > 0; i--) {
	    for (int j = 0; j < i; j++)
		printf("%d", i);
	    printf("\n");
	}
	if (n)	printf("\n");
    }
}

int main() {
    int cas, len, n;
    scanf("%d", &cas);
    while (cas--) {
	scanf("%d%d", &len, &n);
	print(len, n);
	if (cas) printf("\n");
    }
    return 0;
}

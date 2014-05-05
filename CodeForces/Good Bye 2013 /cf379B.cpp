#include <stdio.h>
#include <string.h>

const int N = 305;

int n, c[N];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &c[i]);
	for (int i = 0; i < c[0]; i++) printf("PRL");

	for (int i = 1; i < n; i++) {
		printf("R");
		for (int j = 0; j < c[i]; j++) printf("PLR");
	}
	printf("\n");
	return 0;
}

#include <stdio.h>
#include <string.h>

const int N = 100005;

int n, a[N], b[N];
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d%d", &a[i], &b[i]);
	int p = 0, q = 0, k = n / 2;
	for (int i = 0; i < n; i++) {
		if (a[p] < b[q]) p++;
		else q++;
	}

	for (int i = 0; i < n; i++) {
		if (i < p || i < k) printf("1");
		else printf("0");
	}
	printf("\n");
	for (int i = 0; i < n; i++) {
		if (i < q || i < k) printf("1");
		else printf("0");
	}
	printf("\n");
	return 0;
}

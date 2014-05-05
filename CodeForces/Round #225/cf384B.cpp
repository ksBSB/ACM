#include <stdio.h>
#include <string.h>

int main () {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) scanf("%*d");
	printf("%d\n", m * (m - 1) / 2);
	if (k) {
		for (int i = m; i > 1; i--) {
			for (int j = m; j > m - i + 1; j--) printf("%d %d\n", j, j-1);
		}
	} else {
		for (int i = m - 1; i; i--) {
			for (int j = 1; j <= i; j++) printf("%d %d\n", j, j+1);
		}
	}
	return 0;
}

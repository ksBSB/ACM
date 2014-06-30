#include <stdio.h>
int main() {
    int cas;
    int n, size, ani, val;
    scanf("%d", &cas);
    while (cas--) {
	int sum = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
	    scanf("%d%d%d", &size, &ani, &val);
	    sum += size * val;
	}
	printf("%d\n", sum);
    }
    return 0;
}

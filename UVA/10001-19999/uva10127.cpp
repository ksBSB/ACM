#include <cstdio>
#include <cstring>

int main () {
	int n;
	while (scanf("%d", &n) == 1) {
		int ans = 1, c = 1;
		while (c) {
			c = (c * 10 + 1) % n;
			ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}

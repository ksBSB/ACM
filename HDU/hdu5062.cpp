#include <cstdio>
#include <cstring>

const int ans[10] = {1, 9, 18, 54, 90, 174, 258};

int main () {
	int cas, n;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		printf("%d\n", ans[n]);
	}
	return 0;
}

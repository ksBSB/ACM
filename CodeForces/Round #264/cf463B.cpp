#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int n, x, ans = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		ans = max(ans, x);
	}
	printf("%d\n", ans);
	return 0;
}

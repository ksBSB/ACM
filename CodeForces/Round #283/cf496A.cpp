#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 105;


int main () {
	int n, a[maxn], ans = 0, tmp = 0x3f3f3f3f;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i < n; i++)
		ans = max(ans, a[i+1] - a[i]);

	for (int i = 2; i < n; i++)
		tmp = min(tmp, a[i+1] - a[i-1]);
	printf("%d\n", max(tmp, ans));
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int n, k;
	scanf("%d%d", &n, &k);

	int ans = n;
	while (n >= k) {
		ans += n / k;
		n = n / k + n % k;
	}
	printf("%d\n", ans);
	return 0;
}

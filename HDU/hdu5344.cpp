#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int cas, n, m, z, l;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d%d%d", &n, &m, &z, &l);
		int ans = 0, a = 0;
		for (int i = 0; i < n; i++) {
			ans ^= (2 * a);
			a = (1LL * a * m + z) % l;
		}
		printf("%d\n", ans);
	}
	return 0;
}

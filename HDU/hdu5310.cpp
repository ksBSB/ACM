#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int cas, n, m, p, q;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d%d%d", &n, &m, &p, &q);
		int k = n / m, s = n % m;
		int ans = k * min(q, p * m) + min(q, s * p);
		printf("%d\n", ans);
	}
	return 0;
}

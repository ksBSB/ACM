#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int n, m, k, c[maxn];

inline int bitcount (int x) {
	return x == 0 ? 0 : bitcount(x>>1) + (x&1);
}

int main () {
	int ret = 0;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i <= m; i++)
		scanf("%d", &c[i]);

	for (int i = 0; i < m; i++) {
		if (bitcount(c[i]^c[m]) <= k)
			ret++;
	}
	printf("%d\n", ret);
	return 0;
}

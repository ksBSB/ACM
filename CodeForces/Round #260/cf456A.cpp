#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;
const int INF = 0x3f3f3f3f;

int n, p, q, c[maxn];

bool judge () {
	int ans = INF;
	for (int i = 1e5; i >= 0; i--) {
		if (c[i] == INF)
			continue;
		if (c[i] > ans)
			return true;
		ans = c[i];
	}
	return false;
}

int main () {
	scanf("%d", &n);
	memset(c, INF, sizeof(c));

	for (int i = 0; i < n; i++) {
		scanf("%d%d", &p, &q);
		c[p] = min(c[p], q);
	}

	printf("%s\n", judge() ? "Happy Alex" : "Poor Alex");
	return 0;
}

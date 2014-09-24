#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 105;

int main () {
	int n, m, x, c[maxn];
	memset(c, 0, sizeof(c));
	scanf("%d", &n);

	for (int i = 0; i < 2; i++) {
		scanf("%d", &m);
		for (int j = 0; j < m; j++) {
			scanf("%d", &x);
			c[x]++;
		}
	}

	int flag = true;
	for (int i = 1; i <= n; i++)
		if (c[i] == 0) {
			flag = false;
			break;
		}
	printf("%s\n", flag ? "I become the guy." : "Oh, my keyboard!");
	return 0;
}

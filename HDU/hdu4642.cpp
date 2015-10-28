#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int cas, n, m, x;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d", &x);
		printf("%s\n", x ? "Alice" : "Bob");
	}
	return 0;
}

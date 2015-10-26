#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int n, m;
	while (scanf("%d%d", &n, &m) == 2) {
		int u, v, t = 0;
		while (m--) {
			scanf("%d%d", &u, &v);
			if (u > v) swap(u, v);
			if (u == 1 && v == n) t = 1;
		}

		if (t) printf("1 %d\n", n * (n-1) / 2);
		else printf("1 1\n");
	}
	return 0;
}

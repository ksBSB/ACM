#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int n, m, a, k = 0, id = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a);
		int t = (a-1) / m + 1;
		if (t >= k) {
			k = t;
			id = i;
		}
	}
	printf("%d\n", id);
	return 0;
}

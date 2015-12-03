#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int n, c;
	char order[5];
	while (scanf("%d", &n) == 1) {
		int ans = 0;
		while (n--) {
			scanf("%s", order);
			if (order[0] == 'S') ans++;
			else {
				scanf("%d", &c);
				if (c == 1) ans++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

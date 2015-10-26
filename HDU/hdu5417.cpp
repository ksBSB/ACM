#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int x, y, w, n;
	while (scanf("%d%d%d%d", &x, &y, &w, &n) == 4) {
		int ans = 0, now = 0, shutup = x;
		while (n--) {
			ans = now;
			if (now + w > shutup) {
				now = shutup + y;
				shutup = now + x;
			} else
				now += w;
		}
		printf("%d\n", ans);
	}
	return 0;
}

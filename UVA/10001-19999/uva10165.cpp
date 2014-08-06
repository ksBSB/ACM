#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	int n, u;
	while (scanf("%d", &n) == 1 && n) {
		int ans = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &u);
			ans ^= u;
		}
		printf("%s\n", ans ? "Yes" : "No");
	}
	return 0;
}

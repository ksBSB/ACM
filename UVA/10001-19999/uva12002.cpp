#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 505;

int n, s[N], up[N], down[N];

void init () {

	for (int i = 1; i <= n; i++)
		scanf("%d", &s[i]);

	for (int i = n; i; i--) {
		up[i] = down[i] = 1;
		for (int j = n; j > i; j--) {
			if (s[j] <= s[i])
				down[i] = max(down[i], down[j] + 1);
			if (s[j] >= s[i])
				up[i] = max(up[i], up[j] + 1);
		}	
	}
}

int cat (int k, int p, int a) {
	int ans = 0;
	for (int i = p; i <= n; i++) {
		if (a == 1 && s[i] >= k)
			ans = max(ans, up[i]);
		if (a == -1 && s[i] <= k)
			ans = max(ans, down[i]);
	}
	return ans;
}

int solve () {
	int ans = 0;

	for (int i = 1; i <= n; i++) {
		int u = up[i] + cat(s[i]-1, i, -1);
		int v = down[i] + cat(s[i]+1, i, 1);
		ans = max(ans, max(u, v));
	}
	return ans;
}

int main () {
	while (scanf("%d", &n) == 1 && n) {
		init ();
		printf("%d\n", solve());
	}
	return 0;
}

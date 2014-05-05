#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 2005;

int n, t[N], up[N], down[N];

void init () {
	memset(t, 0, sizeof(t));
	memset(up, 0, sizeof(up));
	memset(down, 0, sizeof(down));

	scanf("%d", &n);
	for (int i = n; i; i--)
		scanf("%d", &t[i]);
}

int solve () {
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < i; j++) {
			if (t[i] > t[j])
				up[i] = max(up[i], up[j]);
			if (t[i] < t[j])
				down[i] = max(down[i], down[j]);
		}
		up[i]++; down[i]++;
		ans = max(ans, up[i]+down[i]-1);
	}

	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();
		printf("%d\n", solve ());
	}
	return 0;
}

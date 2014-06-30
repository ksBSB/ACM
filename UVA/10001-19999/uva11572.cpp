#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>

using namespace std;
const int N = 1000005;

int n, g[N];

map<int, int> v;

void init() {
	v.clear();
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &g[i]);
}

int solve() {
	int l = 0, ans = 0;
	for (int r = 0; r < n; r++) {
		v[g[r]]++;
		while (v[g[r]] == 2) v[g[l++]]--;
		ans = max(r - l + 1, ans);
	}
	return ans;
}

int main() {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}

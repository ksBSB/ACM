#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 10005;

struct state {
	int pi, di;
}s[N];
int n, v[N];

bool cmp(const state& a, const state& b) {
	return a.pi > b.pi;
}

int find(int x) {
	return v[x] == -1 ? x : v[x] = find(v[x]);
}

void init() {
	memset(v, -1, sizeof(v));
	for (int i = 0; i < n; i++) scanf("%d%d", &s[i].pi, &s[i].di);
	sort(s, s + n, cmp);
}

int solve() {
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int k = find(s[i].di);
		if (k) {
			ans += s[i].pi;
			v[k] = k - 1;
		}
	}
	return ans;
}

int main() {
	while (scanf("%d", &n) == 1) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}

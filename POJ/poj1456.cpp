#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 10005;

struct product {
	int val, day;
}pro[N];
int n, f[N];

int getfar(int x) {
	return x == f[x] ? x : f[x] = getfar(f[x]);
}

bool cmp (const product& a, const product& b) {
	return a.val > b.val;
}

void init () {
	for (int i = 0; i < N; i++)
		f[i] = i;

	for (int i = 0; i < n; i++)
		scanf("%d%d", &pro[i].val, &pro[i].day);

	sort(pro, pro + n, cmp);
}

int solve () {
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int p = getfar(pro[i].day);

		if (p == 0) continue;
		f[p] = p-1;
		ans += pro[i].val;
	}
	return ans;
}

int main () {
	while (scanf("%d", &n) == 1) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}

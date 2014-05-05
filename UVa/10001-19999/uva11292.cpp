#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 20005;

int n, m, d[N], l[N];

void init() {
	for (int i = 0; i < n; i++)
		scanf("%d", &d[i]);
	sort(d, d + n);
	
	for (int i = 0; i < m; i++)
		scanf("%d", &l[i]);
	sort(l, l + m);
}

bool judge() {
	int i, j, ans = 0;

	for (i = j = 0; i < n && j < m; j++) {
		if (d[i] <= l[j]) {
			i++, ans += l[j];
		}
	}

	if (i < n) return true;
	printf("%d\n", ans);
	return false;
}

int main () {
	while (scanf("%d%d", &n, &m), n + m) {
		init();
		if (judge()) printf("Loowater is doomed!\n");
	}
	return 0;
}

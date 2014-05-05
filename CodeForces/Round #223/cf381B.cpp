#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 5005;

int n, c[N], t[N*2], cnt;

void init () {
	cnt = 0;
	memset(c, 0, sizeof(c));

	int a;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a);
		c[a]++;
	}
}

void solve () {
	int tmp = 0;
	for (int i = 0; i < N; i++) if (c[i]) {
		t[cnt++] = i;
		tmp = max(tmp, i);
		c[i]--;
	}
	for (int i = tmp - 1; i >= 0; i--) if (c[i]) {
		t[cnt++] = i;
	}
	printf("%d\n%d", cnt, t[0]);
	for (int i = 1; i < cnt; i++) printf(" %d", t[i]);
	printf("\n");
}

int main () {
	init();
	solve();
	return 0;
}

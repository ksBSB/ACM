#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int INF = 2*1e9+5;
int n, l, r;

int cat (char* s) {
	if (strcmp(s, "<") == 0) return 0;
	if (strcmp(s, "<=") == 0) return 1;
	if (strcmp(s, ">") == 0) return 2;
	if (strcmp(s, ">=") == 0) return 3;
	return 4;
}

void solve (int a, int c) {
	if (c == 0) {
		r = min(r, a - 1);
	} else if (c == 1) {
		r = min(r, a);
	} else if (c == 2) {
		l = max(l, a + 1);
	} else {
		l = max(l, a);
	}
}

int main () {
	scanf("%d", &n);

	int a;
	char sign[10], flag[10];
	l = -INF, r = INF;

	for (int i = 0; i < n; i++) {
		scanf("%s%d%s", sign, &a, flag);
		int c = cat(sign);
		if (flag[0] == 'N') c = 3 - c;
		solve (a, c);
	}

	if (l > r)
		printf("Impossible\n");
	else 
		printf("%d\n", l);
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 1e5+10;

int l, h, r, v[N], R;

int main () {
	R = 0;
	memset(v, 0, sizeof(v));

	while (scanf("%d%d%d", &l, &h, &r) == 3) {
		for (int i = l; i < r; i++)
			v[i] = max(v[i], h);
		R = max(r, R);
	}
	for (int i = 1; i < R; i++) {
		if (v[i] != v[i-1]) printf("%d %d ", i, v[i]);
	}
	printf("%d %d\n", R, 0);
	return 0;
}

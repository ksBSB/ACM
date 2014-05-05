#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 4005;

int n, k, v[N];

void solve () {
	v[0] = 1;
	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (v[i] == 0) {
			l++;

			if (v[i-1] == 0) {
				v[i] = 1;
				r++;
			}
		}
	}
	printf("%d %d\n", l-r, l);
}

int main () {
	memset(v, 0, sizeof(v));
	scanf("%d%d", &n, &k);

	int t, a, b;
	for (int i = 0; i < k; i++) {
		scanf("%d", &t);

		if (t == 2) {
			scanf("%d", &a);
			v[a] = 1;
		} else {
			scanf("%d%d", &a, &b);
			v[a] = v[b] = 1;
		}
	}
	solve ();
	return 0;
}

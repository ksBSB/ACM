#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 500005;

int n, l, r, left[N], right[N];

void init() {
	l = r = 0;
	memset(right, 0, sizeof(right));
	memset(left, 0, sizeof(left));

	int c;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &c);
		if (c < 0)  left[l++] = -c;
		else	right[r++] = c;
	}

	sort(left, left + l);
	sort(right, right + r);
}

int solve() {
	if (l && r) {
		int p, q, begin, ans = 1, tmp;
		if (left[0] < right[0]) {
			p = 1, q = 0, begin = 0;
			tmp = left[0];
		}
		else {
			p = 0, q = 1, begin = 1;
			tmp = right[0];
		}

		for (int i = begin; p < l || q < r; i++) {
			bool flag = true;

			if (i % 2) {
			//	if (p >= l) break;

				while (p < l) {
					if (tmp <= left[p]) {
						ans++;
						tmp = left[p++];
						flag = false;
						break;
					} else	p++;
				}
			} else {
//				if (q >= r) break;

				while (q < r) {
					if (tmp <= right[q]) {
						ans++;
						tmp = right[q++];
						flag = false;
						break;
					} else	q++;
				}
			}
			if (flag) break;
		}
		return ans;
	} else	return 1;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve() );
	}
	return 0;
}

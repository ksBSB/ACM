#include <stdio.h>
#include <string.h>

const int N = 1e4+1;

int x, c, v[N], l[N], r[N];

bool judge(int n)
{
	int p = 0, q = n-1, cnt = 0;

	while (p <= q) {
		int mid = (p + q) / 2;
		cnt++;
		if (cnt > c) return false;
		if (mid == x) return cnt == c;

		if (x < mid)
			q = mid - 1;
		else
			p = mid + 1;
	}
	return false;
}

int main () {
	while (scanf("%d%d", &x, &c) == 2) {
		memset(v, 0, sizeof(v));

		bool flag = false;
		int ans = 0;
		for (int i = x+1; i < N; i++) {
			if (judge(i)) {
				if (!flag) {
					l[ans] = i;
					flag = true;
				}
			} else {
				if (flag) {
					r[ans++] = i-1;
					flag = false;
				}
			}
		}

		if (flag) r[ans++] = N-1;

		printf("%d\n", ans);
		for (int i = 0; i < ans; i++)
			printf("%d %d\n", l[i], r[i]);
	}
	return 0;
}

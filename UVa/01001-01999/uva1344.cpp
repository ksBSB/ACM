#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 1005;

int n, ans, t[N], q[N];

bool cmp(const int& a, const int& b) {
	return a > b;
}

void judge(int w, int e) {
	int sum = (2 * w + e - n) * 200;
	if (sum > ans) ans = sum;
}

void solve(int x, int y, int w, int e) {

	if (y >= n || x >= n) {
		judge(w, e);
		return ;
	}

	while(t[x] < q[y]) {
		y++;
		if (y >= n) {
			judge(w, e);
			return;
		}
	}

	if (t[x] == q[y]) {
		solve(x + 1, y + 1, w, e + 1);
		solve(x, y + 1, w, e);
	} else {
		solve(x + 1, y + 1, w + 1, e);
	}
}

int main () {
	while (scanf("%d", &n) == 1 && n) {
		ans = -200 * n;
		for (int i = 0; i < n; i++) scanf("%d", &t[i]);
		for (int i = 0; i < n; i++) scanf("%d", &q[i]);
		sort(t, t + n, cmp); sort(q, q + n, cmp);

		solve(0, 0, 0, 0);
		printf("%d\n", ans);
	}
	return 0;
}

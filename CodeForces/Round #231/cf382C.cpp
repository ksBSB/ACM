#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <set>

using namespace std;
const int N = 100005;

int n, a[N];
struct state {
	int k, v;
};

void init () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	sort(a, a + n);
}

void solve () {
	set<int> ans;
	if (n == 2) {
		int d = a[1] - a[0];
	    ans.insert(a[0]-d); ans.insert(a[1]+d);
		if (d % 2 == 0) ans.insert(a[1]-d/2);
	} else if (n == 3) {
		int d1 = a[1] - a[0], d2 = a[2] - a[1];
		if (d1 == d2) { ans.insert(a[0]-d1); ans.insert(a[2]+d1); }
		else {
			if (d1 == d2 * 2) {
				ans.insert(a[0] + d2);
			} else if (d2 == d1 * 2) {
				ans.insert(a[1] + d1);
			}
		}
	} else {
		int cnt = 0, d[10];
		map<int, int> g;

		for (int i = 1; i < n; i++) {
			int k = a[i] - a[i-1];
			g[k]++;
			if (g[k] == 1) {
				d[cnt++] = k;
				if (cnt >= 3) break;
			}
		}

		if (cnt == 1) {
			ans.insert(a[0]-d[0]); ans.insert(a[n-1]+d[0]);
		} else if (cnt == 2 && g[d[0]] == 1 && d[0] == 2 * d[1]) {
			for (int i = 1; i < n; i++) if (a[i] - a[i-1] == d[0]) {
				ans.insert(a[i]-d[1]); break;
			}
		} else if (cnt == 2 && g[d[1]] == 1 && d[1] == 2 * d[0]) {
			for (int i = 1; i < n; i++) if (a[i] - a[i-1] == d[1]) {
				ans.insert(a[i]-d[0]); break;
			}
		}
	}

	bool flag = false;
	printf("%lu\n", ans.size());
	for (set<int>::iterator i = ans.begin(); i != ans.end(); i++) {
		if (flag) printf(" ");
		printf("%d", *i); flag = true;
	}
	if (ans.size()) printf("\n");
}

int main () {
	init();
	if (n == 1) printf("-1\n");
	else solve();
	return 0;
}

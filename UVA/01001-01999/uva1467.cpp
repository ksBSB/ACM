#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 505;
const int INF = 0x3f3f3f3f;
struct job {
	int s, d;
}j[N];
int n, p;

bool cmp(const job& a, const job& b) {
	 return a.d < b.d;
}

void init() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d%d", &j[i].s, &j[i].d);
	sort(j, j + n, cmp);
}

int handle(int x) {
	int t = 0, a = 0, b = 0, k;
	for (int i = 0; i <= p; i++) {
		if (i == x) continue;
		t += j[i].s;
		k = max(0, t - j[i].d);
		b = max(b, k);
		if (b > a) swap(a, b);
	}

	t += j[x].s;
	k = max(0, t - j[x].d);
	b = max(b, k);
	return a + b;
}

int solve() {
	int t = 0, a = 0, b = 0;
	for (int i = 0; i < n; i++) {
		t += j[i].s;
		if (t - j[i].d >= b) {
			b = t - j[i].d;
			p = i;
		}
		if (b > a) swap(a, b);
	}

	int ans = a + b;
	for (int i = 0; i < p; i++) 
		ans = min(ans, handle(i));
	return ans;
}

int main() {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}

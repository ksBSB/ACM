#include <stdio.h>
#include <string.h>
#include <math.h>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;
const int N = 5005;
const int INF = 0x3f3f3f3f;
const double pi = acos(-1.0);
struct point {
	int x, y, cnt;
	double r, c;
	void get() {
		scanf("%d%d", &x, &y);
		r = sqrt(x * x * 1.0 + y * y * 1.0);
		c = atan2(y, x);
		cnt = 1;
	}
}p[N], rec[N];
int n, k;

bool cmpR(const point& a, const point& b) {
	return a.r < b.r;
}

bool cmpC(const point& a, const point& b) {
	return a.c < b.c;
}

void init () {
	for (int i = 0; i < n; i++) p[i].get();
	sort(p, p + n, cmpR);
	for (int i = 1; i < n; i++) p[i].cnt += p[i-1].cnt;
}

double solve () {
	if (k == 0) return 0;

	double ans = INF;
	set<double> v;
	sort(p, p + n, cmpC);

	for (int i = 0; i < n; i++) {
		if (p[i].cnt < k) continue;
		double R = p[i].r, C = 2 * pi;
		if (v.find(R) != v.end()) continue;
		v.insert(R);
		int tmp = 0; 
		for (int j = 0; j < n; j++) if (p[j].r < R || fabs(p[j].r - R) < 1e-9) {
			rec[tmp++] = p[j];
			if (tmp >= k)
				C = min(C, rec[tmp-1].c - rec[tmp-k].c);
		}
		if (tmp < k) continue;
		for (int j = 0; j < k - 1; j++)
			C = min(C, rec[j].c - rec[tmp+j-k+1].c + 2 * pi);
		ans = min(ans, R * R * C / 2);
	}
	return ans;
}

int main () {
	int cas = 1;
	while (scanf("%d%d", &n, &k) == 2 && n + k) {
		init();
		printf("Case #%d: %.2lf\n", cas++, solve());
	}
	return 0;
}

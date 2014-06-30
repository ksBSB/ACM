#include <stdio.h>
#include <string.h>

typedef long long ll;
const int N = 105;

struct point {
	ll x, y;
	void get() {
		scanf("%lld%lld", &x, &y);
	}
}p[N];

int n;

void init() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) p[i].get(); 
}

bool isOK(point a, point b, point c) {
	point pi, qi;
	pi.x = b.x - a.x, pi.y = b.y - a.y;
	qi.x = c.x - a.x, qi.y = c.y - a.y;

	if (pi.x * qi.x + pi.y * qi.y > 0) return true;
	return false;
}

bool judge(point a, point b, point c) {
	if (isOK(a, b, c) && isOK(b, a, c) && isOK(c, a, b) ) return true;
	return false;
}

int solve() {
	int ans = 0;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			for (int k = j + 1; k < n; k++)
				if (judge(p[i], p[j], p[k])) ans++;
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

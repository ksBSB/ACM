#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 20;
const int maxans = 1e6;
const int INF = 0x3f3f3f3f;

struct Sava {
	int c, p, l;
}s[maxn];
int n;

void gcd (int a, int b, int& d, int& x, int& y) {
	if (b == 0) {
		d = a;
		x = 1;
		y = 0;
	} else {
		gcd(b, a%b, d, y, x);
		y -= (a/b) * x;
	}
}

bool judge (int m) {
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			int A = s[j].p - s[i].p;
			int C = s[i].c - s[j].c;
			int L = min(s[i].l, s[j].l);
			int d, x, y;

			gcd(A, m, d, x, y);
			if (C % d)
				continue;

			int up = INF, lower = -INF;

			if (m / d > 0) {
				up = min(up, (int)floor( (L * d * 1.0 - x * C * 1.0) / m));
				lower = max(lower, (int)ceil( (-x * C * 1.0) / m));
			} else {
				up = min(up, (int)floor( (-x * C * 1.0) / m));
				lower = max(lower, (int)ceil( (L * d * 1.0 - x * C * 1.0) / m));
			}

			if (up >= lower)
				return false;
		}
	}
	return true;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		int star = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d%d%d", &s[i].c, &s[i].p, &s[i].l);
			star = max (star, s[i].c);
		}

		for (int i = star; i <= maxans; i++) {
			if (judge(i)) {
				printf("%d\n", i);
				break;
			}
		}
	}
	return 0;
}

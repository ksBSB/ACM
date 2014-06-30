#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 5005;

struct point {
	int x, y;
	void get () {
		scanf("%d%d", &x, &y);
	}
	void set (int x, int y) {
		this->x = x;
		this->y = y;
	}
}p[N], l[N*N/2];
int n, m;

inline bool cmp(const point& a, const point& b) {
	if (a.x != b.x)
		return a.x < b.x;
	return a.y < b.y;
}

void init () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		p[i].get();

	sort(p, p + n, cmp);

	m = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			if (p[i].x != p[j].x)
				break;

			l[m++].set(p[i].y, p[j].y);
		}
	}
	sort(l, l + m, cmp);
}

ll solve () {
	ll ans = 0;

	for (int i = 0; i < m;) {
		int mv = i+1;

		while (l[i].x == l[mv].x && l[i].y == l[mv].y)
			mv++;

		ll c = mv - i;

		if (c >= 2)
			ans += c * (c - 1) / 2;
		i = mv;
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		printf("Case %d: %lld\n", i, solve());
	}
	return 0;
}

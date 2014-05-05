#include <stdio.h>
#include <string.h>

const int N = 1e5+10;
int n, L;

struct point {
	int x, y;
	point() { x = y = 0; }
	point(int x, int y) {
		this->x = x; this->y = y;
	}
}p[N], q[N];

struct line {
	point p0, p1;
	line() {}
	line(point a, point b) {
		p0 = a; p1 = b;
	}
	bool operator > (const line& c) {
		return (p1.y - p0.y) * (c.p1.x-c.p0.x) > (p1.x - p0.x) * (c.p1.y - c.p0.y);
	}
	bool operator == (const line& c) {
		return (p1.y - p0.y) * (c.p1.x-c.p0.x) == (p1.x - p0.x) * (c.p1.y - c.p0.y);
	}
	bool operator >= (const line& c) {
		return *this > c || *this == c;
	}

	line operator = (const line& a) {  
		p0 = a.p0; p1 = a.p1;  
		return *this;  
	}  
	int len() {
		return p1.x - p0.x;
	}
};

void init () {
	char str[N];
	scanf("%d%d%s", &n, &L, str);

	int c = 0;
	for (int i = 1; i <= n; i++) {
		if (str[i-1] == '1') c++;
		p[i].x = i; p[i].y = c;
	}
}

void solve () {
	int l = 0, r = -1;
	line Max(p[0], p[L]);

	for (int i = L; i <= n; i++) {
		int u = i - L;
		while (l < r && line(q[r-1], p[u]) >= line(q[r], p[u])) r--;
		q[++r] = p[u];
		while (l < r && line(q[l+1], p[i]) >= line(q[l], p[i])) l++;
		line t(q[l], p[i]);
		if (t > Max || ((t == Max) && t.len() <  Max.len() )) {
			Max = t;
		}
	}
	printf("%d %d\n", Max.p0.x+1, Max.p1.x);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
	}
	return 0;
}

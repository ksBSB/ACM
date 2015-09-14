#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

struct Point {
	ll x, y;
	void read() { scanf("%lld%lld", &x, &y); }
	bool operator < (const Point& u) const { return x < u.x || (x == u.x && y < u.y); };
	Point (ll x = 0, ll y = 0): x(x), y(y) {}
	Point operator + (const Point& u) { return Point(x+u.x,y+u.y); }
	Point operator - (const Point& u) { return Point(x-u.x,y-u.y); }
	ll operator * (const Point& u) { return x*u.y - y*u.x; }
};

const int maxn = 10005;

int N;
Point A[maxn];

ll dis(Point u) {
	return u.x*u.x + u.y*u.y;
}

bool judge () {
	ll x = A[0].x + A[N-1].x;
	ll y = A[0].y + A[N-1].y;
	for (int i = 1; i < N/2; i++) {
		int j = N - i - 1;
		if (A[i].x + A[j].x != x || A[i].y + A[j].y != y)
			return false;
	}
	return true;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			A[i].read();
		sort(A, A + N);

		printf("%s\n", judge() ? "yes" : "no");
	}
	return 0;
}

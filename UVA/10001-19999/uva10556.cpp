#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

struct Point {
	ll x, y;
	void read() { scanf("%lld%lld", &x, &y); }
	Point (ll x = 0, ll y = 0): x(x), y(y) {}
	Point operator + (const Point& u) { return Point(x+u.x,y+u.y); }
	Point operator - (const Point& u) { return Point(x-u.x,y-u.y); }
	ll operator * (const Point& u) { return x*u.y - y*u.x; }
};

const int maxn = 20;

int N;
Point A[maxn], B[maxn];

ll dis(Point u) {
	return u.x*u.x + u.y*u.y;
}

bool judge () {

	if (N <= 2)
		return true;

	ll rad = (A[1]-A[0]) * (B[1] - B[0]);
	ll lenA = dis(A[1]-A[0]), lenB = dis(B[1]-B[0]);
	for (int i = 2; i < N; i++) {
		ll trad = (A[i]-A[0]) * (B[i]-B[0]);
		ll tlenA = dis(A[i]-A[0]), tlenB = dis(B[i]-B[0]);
		if (tlenA*lenB != tlenB*lenA || trad*trad*lenA*lenB != rad*rad*tlenA*tlenB)
			return false;
	}
	return true;
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		for (int i = 0; i < N; i++) A[i].read();
		for (int i = 0; i < N; i++) B[i].read();

		printf("%s\n", judge() ? "similar" : "dissimilar");
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 3000;
typedef long long ll;

struct Point {
	int type;
	ll x, y, z;
	Point (int type = 0, ll x = 0, ll y = 0, ll z = 0) {
		this->type = type;
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

struct Shape {
	int type;
	ll a, b, c, d;
	Shape (int type = 0, ll a = 0, ll b = 0, ll c = 0, ll d = 0) {
		this->type = type;
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
	}
	bool judge (Point u) {
		if (type) {
			ll ta = u.x - a, tb = u.y - b, tc = u.z - c;
			return ta * ta + tb * tb + tc * tc - d * d > 0;
		}
		return a * u.x + b * u.y + c * u.z + d > 0;
	}
};

int M, N, P, Q, V[maxn];
vector<Shape> s;
vector<Point> p;

void init () {
	s.clear();
	p.clear();
	memset(V, 0, sizeof(V));

	ll a, b, c, d;
	scanf("%d%d%d%d", &M, &N, &P, &Q);
	for (int i = 0; i < M; i++) {
		scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
		s.push_back(Shape(0, a, b, c, d));
	}
	for (int i = 0; i < N; i++) {
		scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
		s.push_back(Shape(1, a, b, c, d));
	}
	for (int i = 0; i < P; i++) {
		scanf("%lld%lld%lld", &a, &b, &c);
		p.push_back(Point(0, a, b, c));
	}
	for (int i = 0; i < Q; i++) {
		scanf("%lld%lld%lld", &a, &b, &c);
		p.push_back(Point(1, a, b, c));
	}
}

void solve () {
	if (P == 0) {
		for (int i = 0; i < Q; i++)
			printf("Both\n");
		return;
	}

	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < p.size(); j++) {
			if (s[i].judge(p[j]))
				V[j] ^= 1;
		}
	}

	int yellow = -1;
	for (int i = 0; i < p.size(); i++) {
		if (p[i].type == 0) {
			if (yellow == -1)
				yellow = V[i];
			else if (yellow != V[i]) {
				printf("Impossible\n");
				return;
			}
		}
	}

	for (int i = 0; i < p.size(); i++) {
		if (p[i].type) {
			printf("%s\n", V[i] == yellow ? "Y" : "R");
		}
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
		if (cas)
			printf("\n");
	}
	return 0;
}

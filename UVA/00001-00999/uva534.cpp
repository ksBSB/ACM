#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 205;

struct Point {
	double x, y, d;
	//Point(int x = 0, int y = 0, int d = 0): x(x), y(y), d(d) {}
	//void read() { scanf("%d%d", &x, &y); }
	Point(double x = 0, double y = 0, double d = 0): x(x), y(y), d(d) {}
	void read() { scanf("%lf%lf", &x, &y); }
	bool operator < (const Point& u) const { return d < u.d; }
}P[maxn], T[maxn * maxn];

int N, M, F[maxn];

int find(int x) { return x == F[x] ? x : F[x] = find(F[x]); }
//int getPLength(const Point& a, const Point& b) { return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y); } 
double getLength(const Point& a, const Point& b) { return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)); } 

void init () {
	for (int i = 1; i <= N; i++) {
		P[i].read(), F[i] = i;
	}

	M = 0;
	for (int i = 1; i <= N; i++)
		for (int j = i+1; j <= N; j++)
			T[M++] = Point(i, j, getLength(P[i], P[j]));

	sort(T, T + M);
}

int main () {
	int cas = 1;
	while (scanf("%d", &N) == 1 && N) {
		init ();
		printf("Scenario #%d\nFrog Distance = ", cas++);
		for (int i = 0; i <= M; i++) {
			int p = T[i].x, q = T[i].y;
			if (find(p) != find(q)) {
				F[find(p)] = find(q);
				N--;
				if (find(1) == find(2)) {
					printf("%.3lf\n\n", T[i].d);
					break;
				}
			}
		}
	}
	return 0;
}

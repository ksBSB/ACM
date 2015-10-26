#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 305;
const double inf = 1e20;
const double eps = 1e-8;

struct Point {
	double x, y;
	Point(double x = 0, double y = 0): x(x), y(y) {}
	void read() { scanf("%lf%lf", &x, &y); }
	Point operator - (const Point& u) { return Point(x - u.x, y - u.y); }
}L[maxn], R[maxn];

int N, M, S, T, A[maxn];
vector<Point> P;
double D[maxn][maxn];

double getCross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
double distant(double x, double y) { return sqrt(x*x+y*y); }
int dcmp(double x) { if (fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }

bool haveIntersection(Point a1, Point a2, Point b1, Point b2) {
	double c1 = getCross(a2-a1, b1-a1), c2 = getCross(a2-a1, b2-a1);
	double c3 = getCross(b2-b1, a1-b1), c4 = getCross(b2-b1, a2-b1);
	return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}

bool judge (Point l, Point r) {
	for (int i = 0; i < M; i++) {
		if (haveIntersection(l, r, L[i], R[i])) return false;
	}
	return true;
}

void init () {
	P.clear();
	scanf("%d%d%d", &N, &M, &S);

	double x, y;
	for (int i = 0; i < N; i++) {
		scanf("%lf%lf", &x, &y);
		P.push_back(Point(x, y));
	}

	for (int i = 0; i < M; i++) {
		L[i].read(), R[i].read();
		P.push_back(L[i]);
		P.push_back(R[i]);
	}
	for (int i = 0; i < N; i++) { scanf("%d", &A[i]); A[i]--; } 

	T = P.size();
	for (int i = 0; i < T; i++) {
		D[i][i] = 0;
		for (int j = i + 1; j < T; j++) {
			if (judge(P[i], P[j]))
				D[i][j] = D[j][i] = distant(P[i].x - P[j].x, P[i].y - P[j].y);
			else
				D[i][j] = D[j][i] = inf;
		}
	}

	for (int k = 0; k < T; k++) {
		for (int i = 0; i < T; i++) {
			for (int j = 0; j < T; j++)
				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
		}
	}
}

/***************************/
int l[maxn];
bool t[maxn], vis[maxn][maxn];
vector<int> G[maxn];

bool match(int u) {
	for (int i = 0; i < G[u].size(); i++) {
		int j = G[u][i];
		if (!t[j]) {
			t[j] = true;
			if (!l[j] || match(l[j])) {
				l[j] = u;
				return true;
			}
		}
	}
	return false;
}

int KM () {
	int ret = 0;
	memset(l, 0, sizeof(l));

	for (int i = 1; i <= N; i++) {
		memset(t, false, sizeof(t));
		if (match(i)) ret++;
	}
	return ret;
}

int get(double len) {
	memset(vis, false, sizeof(vis));
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++)
			if (dcmp(D[A[i]][A[j]] - len) <= 0)
				vis[A[i]+1][A[j]+1] = true;
	}

	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				if (vis[i][k] && vis[k][j])
					vis[i][j] = true;
	}

	for (int i = 1; i <= N; i++) {
		G[i].clear();
		for (int j = 1; j <= N; j++) if (vis[i][j])
			G[i].push_back(j);
	}
	return N - KM();
}

/**************************/

double solve () {
	double l = 0, r = 0;
	for (int i = 0; i < N; i++)
		for (int j = i + 1; j < N; j++) r = max(D[i][j], r);
	r += 1;

	while (r - l > 1e-3) {
		double mid = (l + r) / 2;
		if (get(mid) <= S) r = mid;
		else l = mid;
	}
	return l;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%.2lf\n", solve());
	}
	return 0;
}

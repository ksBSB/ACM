#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;
const double eps = 1e-9;

inline int dcmp (double x) { if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }

struct Point3 {
	double x, y, z;

	Point3 (double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}
	bool operator < (const Point3& u) const { return dcmp(x-u.x)<0 || (dcmp(x-u.x)==0 && dcmp(y-u.y)<0) || (dcmp(x-u.x)==0 && dcmp(y-u.y)==0 && dcmp(z-u.z) < 0); }
	bool operator > (const Point3& u) const { return u < (*this); }
	bool operator == (const Point3& u) const { return !(u < (*this) || (*this) < u); }
	bool operator != (const Point3& u) const { return !((*this) == u); }
	Point3 operator + (const Point3& u) const { return Point3(x+u.x, y+u.y, z+u.z); }
	Point3 operator - (const Point3& u) const { return Point3(x-u.x, y-u.y, z-u.z); }
	Point3 operator * (const double u) const { return Point3(x*u, y*u, z*u); }
	Point3 operator / (const double u) const { return Point3(x/u, y/u, z/u); }

	void read () { scanf("%lf%lf%lf", &x, &y, &z); }
};

typedef Point3 Vector3;

namespace Vectorial {
	double getDot(Vector3 a, Vector3 b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
	double getLength(Vector3 a) { return sqrt(getDot(a, a)); }
	double getAngle(Vector3 a, Vector3 b) { return acos(getDot(a, b) / getLength(a) / getLength(b)); }
	Vector3 getCross (Vector3 a, Vector3 b) { return Vector3(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x); }
	Vector3 getNormal(Point3 a, Point3 b, Point3 c) {  
		Vector3 u = a-b, v = b-c;
		Vector3 k = getCross(u, v);
		return k / getLength(k);
	}
	double getDistancePointToPlane (Point3 p, Point3 p0, Vector3 v) { return fabs(getDot(p-p0, v)); }
	Point3 getPlaneProjection (Point3 p, Point3 p0, Vector3 v) { return p - v * getDot(p-p0, v); }
};

namespace Linear {
	using namespace Vectorial;
	double getDistancePointToLine(Point3 p, Point3 a, Point3 b) {
		Vector3 v1 = b-a, v2 = p-a;
		return getLength(getCross(v1,v2)) / getLength(v1);
	}
	double getDistancePointToSegment(Point3 p, Point3 a, Point3 b) {
		if (a == b) return getLength(p-a);
		Vector3 v1 = b-a, v2 = p-a, v3 = p-b;
		if (dcmp(getDot(v1, v2)) < 0) return getLength(v2);
		else if (dcmp(getDot(v1, v3)) > 0) return getLength(v3);
		else return getLength(getCross(v1, v2)) / getLength(v1);
	}

	bool getPointLineToLine (Point3 a, Vector3 u, Point3 b, Vector3 v, double& s) {
		double p = getDot(u, u) * getDot(v, v) - getDot(u, v) * getDot(u, v);
		if (dcmp(p) == 0) return false;
		double q = getDot(u, v) * getDot(v, a-b) - getDot(v, v) * getDot(u, a-b);
		s = p/q;
		return true;
	}

	double getDistanceLineToLine (Point3 a, Vector3 u, Point3 b, Vector3 v) {
		double s, t;
		bool flag1 = getPointLineToLine(a, u, b, v, s);
		bool flag2 = getPointLineToLine(b, v, a, u, t);
		if (flag1 && flag2) {
			Point3 p = a + u * s, q = b + v * t;
			return getLength(p-q);
		}
		return 0;
	}

	double getDistanceSegmentToSegment(Point3 a, Point3 b, Point3 c, Point3 d) {
		double s, t;
		bool flag1 = getPointLineToLine(a, b-a, c, d-c, s);
		bool flag2 = getPointLineToLine(c, d-c, a, b-a, t);
		if (flag1 && flag2 && dcmp(s) > 0 && dcmp(s - 1) < 0 && dcmp(t) > 0 && dcmp(t-1) < 0) {
			Vector3 u = b-a, v = d-c;
			Point3 p = a + u * s, q = b + v * t;
			return getLength(p-q);
		} else {
			double ans = 1e20;
			ans = min(ans, getDistancePointToSegment(a, c, d));
			ans = min(ans, getDistancePointToSegment(b, c, d));
			ans = min(ans, getDistancePointToSegment(c, a, b));
			ans = min(ans, getDistancePointToSegment(d, a, b));
			return ans;
		}
	}
};

namespace Triangular {
	using namespace Vectorial;
	double getArea (Point3 a, Point3 b, Point3 c) { return getLength(getCross(b-a, c-a)); }
	bool onTriangle (Point3 p, Point3 a, Point3 b, Point3 c) {
		double area1 = getArea(p, a, b);
		double area2 = getArea(p, b, c);
		double area3 = getArea(p, c, a);
		return dcmp(area1 + area2 + area3 - getArea(a, b, c)) == 0;
	}
	bool haveIntersectionTriSeg (Point3 p0, Point3 p1, Point3 p2, Point3 a, Point3 b, Point3& p) {
		Vector3 v = getCross(p1-p0, p2-p0);
		if (dcmp(getDot(v, b-a)) == 0) return false;
		else {
			double t = getDot(v, p0 - a) / getDot(v, b-a);
			if (dcmp(t) < 0 || dcmp(t-2) > 0) return false;
			p = a + (b-a) * t;
			return onTriangle(p, p0, p1, p2);
		}
	}
};

struct Face {
	int v[3];
	Face (int a = 0, int b = 0, int c = 0) { v[0] = a, v[1] = b, v[2] = c;}
	Vector3 normal (Point3 *p) const { return Vectorial::getCross(p[v[1]] - p[v[0]], p[v[2]]-p[v[0]]); }
	int cansee (Point3 *p, int i) const {
		return Vectorial::getDot(p[i]-p[v[0]], normal(p)) > 0 ? 1 : 0;
	}
};

namespace Polygonal {
	using namespace Vectorial;

	double getVolume (Point3 a, Point3 b, Point3 c, Point3 d) { return getDot(d-a, getCross(b-a, c-a)) / 6; }

	int vis[1005][1005];
	double rand01() { return rand() / (double) RAND_MAX; }
	double randeps() { return (rand01() - 0.5) * eps; }
	Point3 addNoise(Point3 p) { return Point3(p.x+randeps(), p.y+randeps(), p.z+randeps()); }
	vector<Face> CH3D (Point3 *o, int n, Point3* p) {
		for (int i = 0; i < n; i++) p[i] = addNoise(o[i]);

		memset(vis, -1, sizeof(vis));
		vector<Face> cur;
		cur.push_back(Face(0, 1, 2));
		cur.push_back(Face(2, 1, 0));

		for (int i = 3; i < n; i++) {
			vector<Face> net;
			for (int j = 0; j < cur.size(); j++) {
				Face& f = cur[j];
				int res = f.cansee(p, i);
				if (!res) net.push_back(f);
				for (int k = 0; k < 3; k++) vis[f.v[k]][f.v[(k+1)%3]] = res;
			}

			for (int j = 0; j < cur.size(); j++) {
				for (int k = 0; k < 3; k++) {
					int a = cur[j].v[k], b = cur[j].v[(k+1)%3];
					if (vis[a][b] != vis[b][a] && vis[a][b])
						net.push_back(Face(a, b, i));
				}
			}
			cur = net;
		}
		return cur;
	}

	Point3 getCenter (const vector<Face>& f, Point3* p) {
		int n = f.size();
		double sv = 0, sx = 0, sy = 0, sz = 0;
		for (int i = 0; i < n; i++) {
			double v = getVolume(Point3(0, 0, 0), p[f[i].v[0]], p[f[i].v[1]], p[f[i].v[2]]);
			sv += v;
			sx += (p[f[i].v[0]].x + p[f[i].v[1]].x + p[f[i].v[2]].x) * v;
			sy += (p[f[i].v[0]].y + p[f[i].v[1]].y + p[f[i].v[2]].y) * v;
			sz += (p[f[i].v[0]].z + p[f[i].v[1]].z + p[f[i].v[2]].z) * v;
		}
		return Point3(sx/sv/4, sy/sv/4, sz/sv/4);
	}
};

using namespace Vectorial;
using namespace Polygonal;
const int maxn = 105;
const double inf = 1e20;

int N, M;
vector<Face> Poly1, Poly2;
Point3 P[maxn], Q[maxn], T[maxn];

int main () {
	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; i++) P[i].read();
		scanf("%d", &M);
		for (int i = 0; i < M; i++) Q[i].read();
		sort(P, P + N);
		sort(Q, Q + M);
		N = unique(P, P + N) - P;
		M = unique(Q, Q + M) - Q;

		Poly1 = CH3D(P, N, T);
		Poly2 = CH3D(Q, M, T);
		Point3 center1 = getCenter(Poly1, P), center2 = getCenter(Poly2, Q);
		double dis1 = inf, dis2 = inf;
		for (int i = 0; i < Poly1.size(); i++) {
			int a = Poly1[i].v[0], b = Poly1[i].v[1], c = Poly1[i].v[2];
			dis1 = min(dis1, getDistancePointToPlane(center1, P[a], getNormal(P[a], P[b], P[c])));
		}
		for (int i = 0; i < Poly2.size(); i++) {
			int a = Poly2[i].v[0], b = Poly2[i].v[1], c = Poly2[i].v[2];
			dis2 = min(dis2, getDistancePointToPlane(center2, Q[a], getNormal(Q[a], Q[b], Q[c])));
		}
		printf("%.6lf\n", dis1 + dis2);
	}
	return 0;
}

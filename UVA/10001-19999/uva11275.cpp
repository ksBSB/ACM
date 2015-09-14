#include <cstdio>
#include <cstring>
#include <cmath>
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
	Point3 operator + (const Point3& u) { return Point3(x+u.x, y+u.y, z+u.z); }
	Point3 operator - (const Point3& u) { return Point3(x-u.x, y-u.y, z-u.z); }
	Point3 operator * (const double u) { return Point3(x*u, y*u, z*u); }
	Point3 operator / (const double u) { return Point3(x/u, y/u, z/u); }

	void read () { scanf("%lf%lf%lf", &x, &y, &z); }
};

typedef Point3 Vector3;

namespace Vectorial {
	double getDot(Vector3 a, Vector3 b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
	double getLength(Vector3 a) { return sqrt(getDot(a, a)); }
	double getAngle(Vector3 a, Vector3 b) { return acos(getDot(a, b) / getLength(a) / getLength(b)); }
	double getDistanceToPlane (Point3 p, Point3 p0, Vector3& v) { return fabs(getDot(p-p0, v)); }
	Point3 getPlaneProjection (Point3 p, Point3 p0, Vector3 v) { return p - v * getDot(p-p0, v); }
	Vector3 getCross (Vector3 a, Vector3 b) { return Vector3(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x); }
};

namespace Linear {
	using namespace Vectorial;
	double getDistanceToLine(Point3 p, Point3 a, Point3 b) {
		Vector3 v1 = b-a, v2 = p-a;
		return getLength(getCross(v1,v2)) / getLength(v1);
	}
	double getDistanceToSegment(Point3 p, Point3 a, Point3 b) {
		if (a == b) return getLength(p-a);
		Vector3 v1 = b-a, v2 = p-a, v3 = p-b;
		if (dcmp(getDot(v1, v2)) < 0) return getLength(v2);
		else if (dcmp(getDot(v1, v3)) > 0) return getLength(v3);
		else return getLength(getCross(v1, v2)) / getLength(v1);
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
			if (dcmp(t) < 0 || dcmp(t-1) > 0) return false;
			p = a + (b-a) * t;
			return onTriangle(p, p0, p1, p2);
		}
	}
};


namespace Polygonal {
	using namespace Vectorial;

	struct Face {
		int v[3];
		Face (int a = 0, int b = 0, int c = 0) { v[0] = a, v[1] = b, v[2] = c;}
		Vector3 normal (Point3 *p) const { return getCross(p[v[1]] - p[v[0]], p[v[2]]-p[v[0]]); }
		int cansee (Point3 *p, int i) const {
			return getDot(p[i]-p[v[0]], normal(p)) > 0 ? 1 : 0;
		}
	};

	double getVolume (Point3 a, Point3 b, Point3 c, Point3 d) { return getDot(d-a, getCross(b-a, c-a)) / 6; }

	vector<Face> CH3D (Point3 *p, int n) {
		int vis[3][3];
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
};

Point3 T1[3], T2[3];
//bool haveIntersectionTriSeg (Point3 p0, Point3 p1, Point3 p2, Point3 a, Point3 b, Point3& p);

using namespace Triangular;

bool judge(Point3* t1, Point3* t2) {
	Point3 p;
	for (int i = 0; i < 3; i++) {
		if (haveIntersectionTriSeg(t1[0], t1[1], t1[2], t2[i], t2[(i+1)%3], p)) return true;
		if (haveIntersectionTriSeg(t2[0], t2[1], t2[2], t1[i], t1[(i+1)%3], p)) return true;
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);

	while (cas--) {
		for (int i = 0; i < 3; i++) T1[i].read();
		for (int i = 0; i < 3; i++) T2[i].read();
		printf("%d\n", judge(T1, T2) ? 1 : 0);
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;
const double eps = 1e-8;

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
		return getCross(u, v);
//		Vector3 k = getCross(u, v);
//		return k / getLength(k);
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

	bool getPointLineToLine (Point3 a, Vector3 u, Point3 b, Vector3 v, double& s) {
		double p = getDot(u, u) * getDot(v, v) - getDot(u, v) * getDot(u, v);
		if (dcmp(p) == 0) return false;
		double q = getDot(u, v) * getDot(v, a-b) - getDot(v, v) * getDot(u, a-b);
		s = p/q;
		return true;
	}

	double getDistanceLineToLine (Point3 a, Vector3 u, Point3 b, Vector3 v) {
		Vector3 p = getCross(u, v);
		return fabs(getDot(p, (a-b)) / getLength(p));
	}
};

using namespace Vectorial;
using namespace Linear;
const int maxn = 35;

double R[maxn];
Point3 P[maxn];
Vector3 V[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		int n;
		scanf("%d", &n);
		Point3 a, b;
		for (int i = 0; i < n; i++) {
			P[i].read();
			a.read();
			b.read();
			V[i] = getNormal(P[i], a, b);
			R[i] = getLength(P[i] - a);
		}

		double ans = 1e20;
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				double d = getDistanceLineToLine(P[i], V[i], P[j], V[j]); 
				ans = min(ans, d - R[i] - R[j]);
			}
		}
		if (dcmp(ans) <= 0) printf("Lucky\n");
		else printf("%.2lf\n", ans);
	}
	return 0;
}

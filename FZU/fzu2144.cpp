#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>

using namespace std;

const int N = 100005;
const double eps = 0;

inline bool scan_d(double &ret) {  
	char c; int sgn;  
	if(c = getchar(),c == EOF) return 0; //EOF  
	while(c != '-' && (c < '0' || c > '9')) c = getchar();  
	sgn = (c == '-') ? -1 : 1;  
	ret = (c == '-') ? 0 : (c - '0');  
	while(c=getchar(),c>='0'&&c<='9') ret=ret*10+(c-'0');  
	ret *= sgn;  
	return 1;  
} 

struct point {
	double x, y, z;
	void get() { scan_d(x); scan_d(y); scan_d(z); }
};

struct state {
	double x, y;
}s[N];
int n, tmp;
double r;

void add(point p, point q) {
	double a = q.x * q.x + q.y * q.y + q.z * q.z;
	double b = 2 * (p.x * q.x + p.y * q.y + p.z * q.z);
	double c = p.x * p.x + p.y * p.y + p.z * p.z - r * r;
	double t = b * b - 4 * a * c;

	if (t < 0) return;
	else if (t == 0) {
		double i = -b / (2.0 * a);
		if (i < 0) return;
		s[tmp].x = s[tmp].y = i;
	}
	else {
		double i = (-b + sqrt(t) ) / (2 * a);
		double j = (-b - sqrt(t) ) / (2 * a);
		if (i < 0 && j < 0) return;
		else if (i < 0) i = 0;
		else if (j < 0) j = 0;

		s[tmp].x = min(i, j);
		s[tmp].y = max(i, j);
	}
	tmp++;
}

void init() {
	tmp = 0;
	point p, q;

	scanf("%d%lf", &n, &r);
	for (int i = 0; i < n; i++) {
		p.get(); q.get();
		add(p, q);
	}
}

bool cmp(const state& a, const state& b) {
	if (fabs(a.y - b.y) > eps) return a.y - b.y < eps;
	return a.x - b.x < eps;
}

int solve() {
	int ans = 0;
	double c = -1;
	for (int i = 0; i < tmp; i++) {
		if (s[i].x - c > eps) {
			c = s[i].y;
			ans++;
		}
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		sort(s, s + tmp, cmp);
		printf("Case %d: %d %d\n", i, tmp, solve());
	}
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;
const double sq3 = sqrt(3.0);
struct point {
	double x, y;
};

vector<point> ans;
double T;

bool cmp(const point& a, const point& b) {
	if (fabs(a.x - b.x) > 1e-6) return a.x < b.x;
	return a.y < b.y;
}

double dis(double x, double y) {
	return sqrt(x*x + y*y);
}

void dfs (point A, point B) {

	double len = dis(A.x - B.x, A.y - B.y);
	if (len / 2 < T) return;

	point C, D, E;

	C.x = B.x + 3 * (A.x-B.x) / 4;
	C.y = B.y + 3 * (A.y-B.y) / 4;

	D.x = B.x + (A.x-B.x) / 4;
	D.y = B.y + (A.y-B.y) / 4;

	E.x = (A.x+B.x)/2 + sq3/4*(A.y-B.y);
	E.y = (A.y+B.y)/2 - sq3/4*(A.x-B.x);

	ans.push_back(C);
	ans.push_back(D);
	ans.push_back(E);

	dfs(C, E);
	dfs(E, D);
}

int main () {
	int cas = 1;
	point A, B;
	while (scanf("%lf%lf%lf%lf%lf", &A.x, &A.y, &B.x, &B.y, &T) == 5 && T >= 1) {
		ans.clear();
		ans.push_back(A);
		ans.push_back(B);

		dfs(A, B);

		printf("Case %d:\n", cas++);
		sort(ans.begin(), ans.end(), cmp);
		printf("%lu\n", ans.size());
		for (int i = 0; i < ans.size(); i++) printf("%.5lf %.5lf\n", ans[i].x, ans[i].y);
	}
	return 0;
}

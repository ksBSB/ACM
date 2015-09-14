#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <map>
#include <algorithm>

using namespace std;
//Lab  =  R * arccos(cos(wa)*cos(wb)*cos(ja-jb)  +  sin(wa)*sin(wb))

const int maxn = 105;
const double pi = 4 * atan(1.0);
const double R = 6378.0;
map<string, int> G;
double lat[maxn], lot[maxn];

double toRad(double x) { return x / 180 * pi; }
double solve (int i, int j) {
	//return R * acos(cos(lat[i])*cos(lat[j])*cos(lot[j]-lot[i]) + sin(lat[i])*sin(lat[j]));
	double dlot = lot[j] - lot[i];
	double dlat = lat[j] - lat[i];
	double a = pow(sin(dlat/2), 2) + cos(lat[i])*cos(lat[j])*pow(sin(dlot/2), 2);
	double c = 2 * atan2(sqrt(a), sqrt(1-a));
	return c * R;
}

int main () {
	int n = 0;
	char s[50], t[50];
	G.clear();

	while (scanf("%s", s) == 1 && s[0] != '#') {
		scanf("%lf%lf", &lat[n], &lot[n]);
		string tmp = s;
		G[tmp] = n++;
	}
	
	for (int i = 0; i < n; i++) {
		lat[i] = toRad(lat[i]);
		lot[i] = toRad(lot[i]);
	}

	while (scanf("%s%s", s, t) == 2) {
	   	if (s[0] == '#' && t[0] == '#') break;
		string tmp1 = s, tmp2 = t;
		if (G.find(tmp1) == G.end() || G.find(tmp2) == G.end()) {
			printf("%s - %s\nUnknown\n", s, t);
			continue;
		}
		int a = G[tmp1], b = G[tmp2];
		printf("%s - %s\n%.0lf km\n", s, t, solve(a, b));
	}
	return 0;
}

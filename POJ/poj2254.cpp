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
	return R * acos(cos(lat[i])*cos(lat[j])*cos(lot[j]-lot[i]) + sin(lat[i])*sin(lat[j]));
}

int main () {
	int n = 0;
	char s[50], t[50];
	G.clear();

	while (scanf("%s", s) == 1 && s[0] != '#') {
		scanf("%lf%lf", &lat[n], &lot[n]);
		G[s] = n++;
	}
	
	for (int i = 0; i < n; i++) {
		lat[i] = toRad(lat[i]);
		lot[i] = toRad(lot[i]);
	}

	while (scanf("%s%s", s, t) == 2) {
	   	if (s[0] == '#' && t[0] == '#') break;
		if (G.find(s) == G.end() || G.find(t) == G.end()) {
			printf("%s - %s\nUnknown\n", s, t);
			continue;
		}
		int a = G[s], b = G[t];
		printf("%s - %s\n%.0lf km\n", s, t, solve(a, b));
	}
	return 0;
}

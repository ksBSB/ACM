#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;

int mv, n;
char s[maxn], t[maxn];

double expr () {
	int p = 0;
	double val;

	while ((s[mv] >= '0' && s[mv] <= '9') || s[mv] == '.' || s[mv] == '-')
		t[p++] = s[mv++];
	t[p] = '\0';
	sscanf(t, "%lf", &val);
	return val;
}

double solve () {
	double val;
	while (s[mv] == ' ') mv++;

	if (s[mv] == '(') {
		mv++;
		double p = expr();
		double a = solve();
		double b = solve();
		val = p * (a + b) + (1 - p) * (a - b);
		mv++;
	} else
		val = expr();
	return val;
}

int main () {
	while (gets(s) && strcmp(s, "()") != 0) {
		mv = 0;
		n = strlen(s);
		printf("%.2lf\n", solve());
	}
	return 0;
}

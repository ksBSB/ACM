#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int idx(char ch) {
	if (ch == 'B') return 0;
	if (ch == 'K') return 1;
	if (ch == 'M') return 2;
	if (ch == 'G') return 3;
	if (ch == 'T') return 4;
	if (ch == 'P') return 5;
	if (ch == 'E') return 6;
	if (ch == 'Z') return 7;
	if (ch == 'Y') return 8;
	return 0;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		double k, p = 1;
		char s[5];
		scanf("%lf[%s]", &k, s);
		int n = idx(s[0]);
		for (int i = 0; i < n; i++)
			p = p * 1000 / 1024;
		printf("Case #%d: %.2lf%%\n", kcas, 100.0 * (1-p));
	}
	return 0;
}

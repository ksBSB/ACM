#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a%b); }

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		int n, x, s = 0, c = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			if (x > 0) c++;
			else x = -x;
			s += x;
		}

		printf("Case %d: ", kcas);
		if (c == 0) printf("inf\n");
		else {
			int d = gcd(s, c);
			printf("%d/%d\n", s / d, c / d);
		}
	}
	return 0;
}

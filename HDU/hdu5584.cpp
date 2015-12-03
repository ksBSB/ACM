#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		int a, b, c = 1, d;
		scanf("%d%d", &a, &b);
		d = gcd(a, b);
		a /= d, b /= d;
		while (true) {
			if (a > b) swap(a, b);
			if (b % (a + 1)) break;
			b /= (a + 1);
			c++;
		}
		printf("Case #%d: %d\n", kcas, c);
	}
	return 0;
}

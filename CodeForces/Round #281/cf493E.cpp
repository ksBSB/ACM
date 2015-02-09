#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

ll t, a, b;

int main () {
	scanf("%lld%lld%lld", &t, &a, &b);
	if (t == a) {
		if (a == b)
			printf("%s\n", t == 1 ? "inf" : "2");
		else
			printf("0\n");
	} else if (a == b)
		printf("1\n");
	else if (t > a || a > b)
		printf("0\n");
	else {
		ll d = 0, p = 1;
		while (b) {
			d += (b % a) * p;
			b /= a;
			p *= t;
		}
		if (t == 1)
			printf("%s\n", d == a || d == 1 ? "1" : "0");
		else
			printf("%s\n", d == a ? "1" : "0");
	}
	return 0;
}

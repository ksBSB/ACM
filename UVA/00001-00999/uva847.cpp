#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

bool judge (ll n) {
	ll p = 1;
	while (p < n) {
		p *= 9;
		if (p >= n)
			return true;

		p *= 2;
		if (p >= n)
			return false;
	}
	return false;
}

int main () {
	ll n;
	while (scanf("%lld", &n) == 1) {
		printf("%s wins.\n", judge(n) ? "Stan" : "Ollie");
	}
	return 0;
}

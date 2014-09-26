#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

int main () {
	ll n, b;
	while (scanf("%lld%lld", &n, &b) == 2) {

		ll m = (1LL<<(b+1)) - 1;
		printf("%s\n", n <= m ? "yes" : "no");
	}
	return 0;
}

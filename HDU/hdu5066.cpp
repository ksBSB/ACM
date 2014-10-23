#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;

ll v, v0;

int main () {
	while (scanf("%lld%lld", &v, &v0) == 2) {
		printf("%lld\n", -v0 + 2 * v);
	}
	return 0;
}

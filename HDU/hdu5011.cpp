#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

int main () {
	int n;
	ll x, ret;
	while (scanf("%d", &n) == 1) {
		ret = 0;
		for (int i = 0; i < n; i++) {
			scanf("%I64d", &x);
			ret ^= x;
		}
		printf("%s\n", ret ? "Win" : "Lose");
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

int main () {
	int cas, n;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		ll s = 0, u = 0, x;

		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%I64d", &x);
			s += x;
			u = max(u, x);
		}

		s = (s + 1) / 2;
		printf("Case #%d: %I64d\n", kcas, max(s, u));
	}
	return 0;
}

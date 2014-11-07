#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int inf = 0x3f3f3f3f;

int main () {
	int N, x, y;
	int Tx = -inf, Ty = -inf, Bx = inf, By = inf;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d%d", &x, &y);
		Tx = max(Tx, x);
		Ty = max(Ty, y);
		Bx = min(Bx, x);
		By = min(By, y);
	}
	long long r = max(Tx - Bx, Ty - By);
	printf("%lld\n", r * r);
	return 0;
}

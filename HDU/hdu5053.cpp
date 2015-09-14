#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

int main () {
	int cas;
	scanf("%d", &cas);

	for (int kcas = 1; kcas <= cas; kcas++) {
		ll A, B, S = 0;
		scanf("%I64d%I64d", &A, &B);
		for (ll i = A; i <= B; i++)
			S += i * i * i;
		printf("Case #%d: %I64d\n", kcas, S);
	}
	return 0;
}

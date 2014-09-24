#include <cstdio>
#include <cstring>
#include <algorithm>

using  namespace std;
typedef long long ll;

ll A, M = 1e17;

int main () {
	scanf("%lld", &A);
	A -= 5 * (9 * (M * 18 % A) % A) % A;
	printf("%lld %lld\n", A, A + M * 10 - 1);
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	long long n;
	scanf("%lld", &n);
	if (n&1)
		printf("%lld\n", -n+n/2);
	else
		printf("%lld\n", n/2);
	return 0;
}

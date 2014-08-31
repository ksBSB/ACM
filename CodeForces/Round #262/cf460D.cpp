#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

ll l, r, k;

void solve (int n) {
	int s = 1;
	ll ret = l;

	for (int i = 2; i < (1<<n); i++) {
		ll u = 0;
		for (int j = 0; j < n; j++)
			if (i&(1<<j))
				u ^= (l+j);

		if (u < ret) {
			ret = u;
			s = i;
		}

	}

	int x = 0;
	ll arr[10];
	for (int i = 0; i < n; i++)
		if (s&(1<<i))
			arr[x++] = l + i;

	printf("%lld\n%d\n", ret, x);
	printf("%lld", arr[0]);
	for (int i = 1; i < x; i++)
		printf(" %lld", arr[i]);
	printf("\n");
}

void fuck () {
	ll x = 1;
	while (x <= l) x <<= 1;

	if ((x | (x>>1)) <= r) {
		printf("0\n3\n");
		printf("%lld %lld %lld\n", l, x | (x>>1), (x | (x>>1)) ^ l);
		return;
	}

	printf("1\n2\n");
	if (l&1)
		l++;
	printf("%lld %lld\n", l, l+1);
}

int main () {
	scanf("%lld%lld%lld", &l, &r, &k);

	if (k == 1)
		printf("%lld\n1\n%lld\n", l, l);
	else if (k >= 5) {

		if (l&1)
			l++;
		printf("0\n4\n%lld %lld %lld %lld\n", l, l+1, l+2, l+3);
	} else if (k == 4 && (r - l + 1 > 4 || l%2 == 0)) {

		if (l&1)
			l++;
		printf("0\n4\n%lld %lld %lld %lld\n", l, l+1, l+2, l+3);
	} else if (k == 2 && (r - l + 1 > 2 || l%2 == 0)) {

		if (l&1)
			l++;
		printf("1\n2\n%lld %lld\n", l, l+1);
	} else if (k == 2) {

		if ((l^r) > l)
			printf("%lld\n1\n%lld\n", l, l);
		else
			printf("%lld\n2\n%lld %lld\n", l^r, l, r);
	} else if (k == 4) {
		solve(k);
	} else {
		fuck();
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 20005;

int n, m, c;
ll num[N];

ll cat(int k) {
	return 1LL << k;
}

void init () {
	c = 0;
	scanf("%d%d", &n, &m);

	char str[100];
	for (int i = 0; i < n; i++) {
		scanf("%s", str);
		
		ll p = 0, q = 0;
		for (int j = 0; j < m; j++) {
			if (str[j] == '1')
				p += cat(m-j-1);
			else
				q += cat(m-j-1);
		}
		/*
		printf("%s\n", str);
		printf("%lld %lld\n", p, q);
		*/
		num[c++] = p;
		num[c++] = q;
	}
	sort(num, num + c);
}

ll solve () {
	if (n == 1)
		return 0;

	ll p = num[0];
	ll q = num[c-1];

	ll e = cat(m-1);
	if (((p^q)&e) == e) {
		return max(num[c-2] - num[0], num[c-1] - num[1]);
	} else
		return q - p;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		printf("Case #%d: %lld\n", i, solve());
	}
	return 0;
}

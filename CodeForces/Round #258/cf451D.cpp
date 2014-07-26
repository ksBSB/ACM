#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e5+5;

char str[maxn];

ll cal (ll u) {
	return u * (u-1) / 2;
}

int main () {
	ll oddA = 0, evenA = 0;
	ll oddB = 0, evenB = 0;
	scanf("%s", str);

	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		if (str[i] == 'a') {
			if (i&1)
				oddA++;
			else
				evenA++;
		} else {
			if (i&1)
				oddB++;
			else
				evenB++;
		}
	}

	ll even = oddA * evenA + oddB * evenB;
	ll odd = cal(oddA) + cal(evenA) + cal(oddB) + cal(evenB) + len;
	printf("%lld %lld\n", even, odd);
	return 0;
}

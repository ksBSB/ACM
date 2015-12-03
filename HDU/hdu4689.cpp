#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = (1<<20) + 5;
typedef unsigned long long ll;

int N, K, S, bit[maxn];
char str[25];

int bitcount(int s) { return s == 0 ? 0 : bitcount(s>>1) + (s&1); }

ll add(int s) {
	int c = 0;
	ll ret = 1;

	for (int i = 0; i < N; i++) {
		if (s&(1<<i)) {
			if (c == 0) return 0;
			ret *= c;
			c--;
		}
		if (str[i] == '+') c++;
	}
	return ret;
}

ll del(int s) {
	int c = 0;
	ll ret = 1;

	for (int i = N-1; i >= 0; i--) {
		if (s&(1<<i)) {
			if (c == 0) return 0;
			ret *= c;
			c--;
		}
		if (str[i] == '-') c++;
	}
	return ret;
}

ll solve () {
	N = strlen(str), K = 0, S = (1<<N)-1;
	for (int i = 0; i < N; i++) if (str[i] == '+') K++;

	ll ret = 0;
	for (int i = 0; i < (1<<N); i++) if (bit[i] == K) {
		ll l = add(i);
		if (l == 0) continue;
		ll r = del(i^S);
		ret += l * r;
	}
	return ret;
}

int main () {
	for (int i = 0; i < (1<<20); i++) bit[i] = bitcount(i);

	while (scanf("%s", str) == 1) {
		printf("%llu\n", solve());
	}
	return 0;
}

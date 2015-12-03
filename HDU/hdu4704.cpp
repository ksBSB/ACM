#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 5;

struct bign {
	int len, num[maxn];

	void delzero() {
		while (len && num[len-1] == 0) len--;
		if (len == 0) num[len++] = 0;
	}
	void operator = (char* number) {
		len = strlen(number);
		for (int i = 0; i < len; i++)
			num[i] = number[len-i-1] - '0';
		delzero();
	}
	void operator -- () {
		if (num[0] == 0 && len == 1) return;
		int s = -1;
		for (int i = 0; i < len; i++) {
			s = s + num[i];
			num[i] = (s + 10) % 10;
			if (s >= 0) break;
		}
		delzero();
	}
	int operator % (const int& k) {
		int s = 0;
		for (int i = len-1; i >= 0; i--)
			s = (10LL * s + num[i]) % k;
		return s;
	}
};

char str[maxn];
bign N;

int pow_mod(int x, int n) {
	int ret = 1;
	while(n) {
		if (n&1) ret = 1LL * ret * x % mod;
		x = 1LL * x * x % mod;
		n >>= 1;
	}
	return ret;
}

int main () {
	while (scanf("%s", str) == 1) {
		N = str;
		--N;
		int k = N % (mod-1);
		printf("%d\n", pow_mod(2, k));
	}
	return 0;
}


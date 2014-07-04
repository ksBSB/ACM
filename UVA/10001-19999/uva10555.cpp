#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 105;
const ll INF = 0x3f3f3f3f3f3f3f;

char s[maxn];

ll gcd (ll a, ll b) {
	return b ? gcd(b, a%b) : a;
}

int main () {
	while (scanf("%s", s) == 1 && strcmp(s, "0")) {
		int len = strlen(s)-5;
		ll ansu, ansd = INF;
		for (int i = 0; i < len; i++)
			s[i] = s[i+2];

		for (int i = 0; i < len; i++) {
			ll d = 1, u = 0;
			for (int j = 0; j < i; j++) {
				d = d * 10;
				u = u * 10 + s[j] - '0';
			}

			ll x = 0, y = 0;
			for (int j = i; j < len; j++) {
				x = x * 10 + s[j] - '0';
				y = y * 10 + 9;
			}
			d = d * y;
			u = u * y + x;
			ll g = gcd(d, u);
			u /= g;
			d /= g;

			if (d < ansd) {
				ansd = d;
				ansu = u;
			}
		}
		printf("%lld/%lld\n", ansu, ansd);
	}
	return 0;
}

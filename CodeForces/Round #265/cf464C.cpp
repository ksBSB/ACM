#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e5+5;
const ll mod = 1e9+7;

char s[maxn], o[maxn];
int n;
ll v[20], l[20];

ll pow_mod (ll x, int n) {
	ll ret = 1;
	while (n) {
		if(n&1)
			ret = ret * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}

struct state {
	int r;
	vector<int> vec;

	void set (char* str) {
		int len = strlen(str);
		r = str[0] - '0';
		vec.clear();
		for (int i = 3; i < len; i++) {
			if (str[i] >= '0' && str[i] <= '9')
				vec.push_back(str[i] - '0');
		}
	}

	void solve () {
		ll val = 0, len = 0;

		for (int i = 0; i < vec.size(); i++) {
			int u = vec[i];

			len += l[u];
			val = (val * pow_mod(10, l[u]) + v[u]) % mod;
			len %= (mod-1);
		}
		v[r] = val;
		l[r] = len;
	}
}com[maxn];

void init () {
	for (int i = 0; i < 10; i++) {
		v[i] = i;
		l[i] = 1;
	}

	for (int i = 0; i < n; i++) {
		scanf("%s", o);
		com[i].set(o);
	}

	for (int i = n - 1; i >= 0; i--) {
		int u = com[i].r;
		com[i].solve();
	}
}

int main () {
	scanf("%s%d", s, &n);
	init();

	int len = strlen(s);
	ll ans = 0;
	for (int i = 0; i < len; i++) {
		int u = s[i] - '0';
		ans = (ans * pow_mod(10, l[u]) + v[u]) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;

inline ll cal (ll u) {
	if (u <= 2)
		return u;
	else
		return 2;
}

int main () {
	ll R, Y, B;
	while (cin >> R >> Y >> B) {
		ll h = cal(R) + cal(Y) + cal(B);
		ll n = R + Y + B;

		ll ans = 0;

		for (ll i = 0; i < n && i < h; i++)
			ans += i;

		if (n > h)
			ans += h * (n-h);;
		cout << ans << endl;
	}	
	return 0;
}

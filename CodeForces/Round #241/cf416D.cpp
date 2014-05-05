#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
typedef long long ll;
ll n, a, pl, pr, val, cnt, ans, d, cur;

void set(ll pos, int value, int count) {
	pl = pos;
	val = value;
	cnt = count;
}

int main () {

	pl = pr = -1;
	ans = cnt = 0;

	cin >> n;

	for (ll i = 1; i <= n; i++) {
		cin >> a;

		if (a < 0) {
			if (pl < 0)
				cnt++;
			else if (pr < 0)
				continue;
			else if (cur + d > 0)
				cur = cur + d;
			else {
				set(-1, 0, 1);
				pr = -1;
				ans++;
			}
		} else {
			if (pl < 0) {
				set(i, a, cnt);
			} else if (pr < 0) {
				ll sum = a - val;
				d = sum / (i - pl);

				if (val + (i-pl)*d != a || val <= cnt * d) {
					set(i, a, 0);
					ans++;
				} else {
					pr = i;
					cur = a;
				}
			} else {
				if (cur + d == a)
					cur = a;
				else {
					set(i, a, 0);

					pr = -1;
					ans++;
				}
			}
		}
	}
	cout << ans + 1<< endl;
	return 0;
}

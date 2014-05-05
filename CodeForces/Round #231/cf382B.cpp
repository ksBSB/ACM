#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>

using namespace std;
typedef long long ll;

ll a, b, w, x, c;

ll solve () {
	if (c <= a) return 0;
	ll ans = (ll) ceil(1.0 * (x * (c - a) - b) / (w - x)); 
	return ans + c - a;
}

int main () {
	cin >> a >> b >> w >> x >> c;
	cout << solve() << endl;
	return 0;
}

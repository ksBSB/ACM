#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;

int main () {
    ll n, ans = 0;

    cin >> n;

    double R = n;
    ll tmp = n, k;

    for (ll i = 1; i <= n; i++) {
        double r = i;
        k = (ll)sqrt(R*R - r*r);
        ans += (tmp == k ? 1 : tmp - k);
        tmp = k;
    }
    if (n == 0) cout << 1 << endl;
    else cout << ans * 4 << endl;
    return 0;
}

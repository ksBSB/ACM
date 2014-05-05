#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
typedef long long ll;
const int N = 60;

ll t = 1;
int main () {
	int n;
	char str[N];
	scanf("%d%s", &n, str);

	ll ans = 0;
	for (int i = 0; i < n; i++) if (str[i] == 'B') {
		ans += (t<<i);
	}
	cout << ans << endl;
	return 0;
}

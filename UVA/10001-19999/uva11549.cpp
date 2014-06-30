#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
typedef long long ll;
int n;
ll k;

ll Pow(ll c) {
	ll t = c * c;
	char str[20];
	sprintf(str, "%lld", t);
	t = 0;
	for (int i = 0; i < strlen(str) && i < n; i++) 
		t = t * 10 + str[i] - '0';
	return t;
}

ll solve() {
	ll a = k, b = k, ans = k;
	while (true) {
		a = Pow(a);
		b = Pow(b); ans = max(ans, b);
		b = Pow(b); ans = max(ans, b);
		if (a == b) break;
	}
	return ans;
}

int main() {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%lld", &n, &k);
		printf("%lld\n", solve());
	}
	return 0;
}

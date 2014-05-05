#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
typedef long long ll;

const int N = 50005;

int main() {
	char str[N];
	scanf("%s", str);	

	ll x = 0, len = strlen(str), ans = 0;
	for (ll i = 0; i < len - 3; i++) {
		if (str[i] == 'b' && str[i+1] == 'e' && str[i+2] == 'a' && str[i+3] == 'r') {
			ans += ((i + 1) * (len - i - 3) - x * (len - i - 3));
			x = i + 1;
		}
	}
	cout << ans << endl;
	return 0;
}

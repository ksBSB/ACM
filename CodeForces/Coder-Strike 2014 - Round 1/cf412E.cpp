#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
const int N = 1e6+5;

char s[N];

bool isLetter(char c) {
	if (c >= 'a' && c <= 'z') return true;
	if (c >= 'A' && c <= 'Z') return true;
	return false;
}

int main () {
	scanf("%s", s);

	int n = strlen(s);
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == '@') {
			ll x = 0, y = 0;
			for (int j = i-1; j >= 0; j--) {
				if (s[j] == '@' || s[j] == '.')
					break;
				if (isLetter(s[j]))
					x++;;
			}

			for (int j = i+1; j < n; j++) {
				if (s[j] == '@' || s[j] == '_') {
					i = j-1;
					break;
				}

				if (s[j] == '.') {
					if (j - i == 1) break;
					int k;
					for (k = j+1; k < n; k++) {
						if (!isLetter(s[k]))
							break;
						y++;
					}
					i = k-1;
					break;
				}
			}
			ans += x * y;
		}
	}
	cout << ans << endl;;
	return 0;
}

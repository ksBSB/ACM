#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxt = 100;
const int maxn = 205;

int t[maxt];
char s[maxn];

int pow_mod(int a, int n) {
	int ans = 1;
	while (n) {
		if (n&1)
			ans = ans * a % 10;
		n /= 2;
		a = a * a % 10;
	}
	return ans;
}

void init () {
	t[0] = 0;
	for (int i = 1; i <= maxt; i++) {
		t[i] = (t[i-1] + pow_mod(i%10, i))%10;
	}
}

int main () {
	init();
	while (scanf("%s", s) == 1 && strcmp(s, "0")) {
		int len = strlen(s);
		int ans = 0;
		for (int i = 0; i < len; i++)
			ans = (ans * 10 + s[i] - '0')%maxt;
		printf("%d\n", t[ans]);
	}
	return 0;
}

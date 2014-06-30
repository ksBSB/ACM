#include <stdio.h>
#include <string.h>
const int N = 1030;
const int g = 34943;
const int tmp = 256;

int main() {
	char num[N], c[] = "0123456789ABCDEF";
	int sign[4];
	while (gets(num) && num[0] != '#') {
		long long ans, t = 0;
		for (int i = 0; num[i]; i++)
			t = (t * tmp + num[i]) % g;
		t = (t * tmp * tmp) % g;
		ans = (g - t) % g;
		for (int i = 0; i < 4; i++) {
			sign[i] = ans % 16;
			ans = ans / 16;
		}
		printf("%c%c %c%c\n", c[sign[3]], c[sign[2]], c[sign[1]], c[sign[0]]);
	}
	return 0;
}

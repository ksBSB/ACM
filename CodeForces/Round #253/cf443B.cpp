#include <cstdio>
#include <cstring>

const int N = 205;

int n, len;
char s[N];

bool judge (int l) {

	if (l <= n)
		return true;

	for (int i = 0; i < len-l+n; i++) {

		bool flag = true;

		for (int j = 0; j < l; j++) {

			if (i + j + l >= len + n) {
				flag = false;
				break;
			}

			if (i + j >= len || i + j + l >= len)
				continue;

			if (s[i+j] == s[i+j+l])
				continue;

			flag = false;
			break;
		}

		if (flag)
			return true;
	}
	return false;
}

int main () {
	scanf("%s%d", s, &n);

	len = strlen(s);

	if (n >= len) {
		printf("%d\n", (n + len) / 2 * 2);
	} else {
		for (int i = len; i >= 0; i--) {
			if (judge(i)) {
				printf("%d\n", i*2);
				break;
			}
		}
	}
	return 0;
}

#include <stdio.h>
#include <string.h>

#define max(a, b) (a)>(b)?(a):(b)
const int N = 1005;

int len;
char str[N];

int handle(int& x, int& c, char& rec) {
	int cnt = 0;
	char ch = str[x];
	while (x < len) {
		if (str[x] == ch) cnt++;
		else break;
		x++;
	}
	x--;

	int ans;
	if (cnt >= c) {
		ans = max(cnt, c+1);
		c = cnt;
		rec = ch;
	} else {
		ans = max(cnt+1, c);
		c = cnt + 1;
		rec = ch;
	}
	return ans;
}

int solve() {

	len = strlen(str);
	int ans = 1, c = 0;
	char rec = '\0';

	for (int i = 0; i < len; i++) {
		if (str[i] == '?') {
			int cnt = 0,  flag = i;

			while (i < len) {
				if (str[i] == '?') cnt++;
				else break;
				i++;
			}

			if (i == len) ans = max(ans, c);
			else if (cnt % 2) {

				if (str[i] == rec) {
					ans = max(ans, c);
					rec = str[i]; c = 1;
				} else {
					if (cnt == 1) {
						int t = handle(i, c, rec);
						ans = max(ans, t);
					} else {
						if (flag) ans = max(ans, 2);
						ans = max(ans, c);
						rec = str[i]; c = 1;
					}

				}
			} else {
				ans = max(ans, c);
				if (str[i] == rec) ans = max(ans, 2);
				rec = str[i]; c = 1;
			}

		} else if (str[i] == rec) {
			c++;
		} else {
			ans = max(ans, c);
			rec = str[i]; c = 1;
		}
	}
	return max(ans, c);
}

int main() {
	int cas; 
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		scanf("%s", str);
		printf("Case %d: %d\n", i , solve());
	}
	return 0;
}

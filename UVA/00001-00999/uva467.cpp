#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;
const int maxd = 15;
const int INF = 0x3f3f3f3f;

char str[maxn];
int n, c[maxd];

inline bool isDight (char ch) {
	return ch >= '0' && ch <= '9';
}

void init () {
	n = 0;
	int num = 0, len = strlen(str);
	for (int i = 0; i <= len; i++) {
		if (isDight(str[i]))
			num = num * 10 + str[i] - '0';
		else {
			c[n++] = num;
			num = 0;
		}
	}
}

bool judge (int u) {
	for (int i = 0; i < n; i++) {
		int d = u % (2 * c[i]);

		if (d >= c[i] - 5)
			return false;
	}
	return true;
}

int main () {
	int cas = 1;
	while (gets(str) != NULL) {
		init();

		int s = INF;
		for (int i = 0; i < n; i++)
			s = min(s, c[i]);
		s -= 5;

		bool flag = true, t = true;
		for (int u = s+1; u <= 3600; u++) {

			if (t) {
				if (judge(u))
					t = true;
				else
					t = false;
			} else {
				if (judge(u)) {
					flag = false;
					printf("Set %d synchs again at %d minute(s) and %d second(s) after all turning green.\n", cas++, u/60, u%60);
					break;
				}
			}
		}

		if (flag)
			printf("Set %d is unable to synch after one hour.\n", cas++);
	}
	return 0;
}

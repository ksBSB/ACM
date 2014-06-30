#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 105;

int n, l[N], r[N];

inline int cal (char ch) {
	if (ch == 'B')
		return 0;
	else if (ch == 'Y')
		return 1;
	else if (ch == 'W')
		return 2;
	else if (ch == 'G')
		return 3;
	else if (ch == 'R')
		return 4;
	return -1;
}

int bit (int i) {
	return 1<<i;
}

int bitCount (int x) {
	return x == 0 ? 0 : bitCount(x/2) + (x&1);
}

bool judge (int s) {

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {

			if (l[i] == l[j]) {

				if (r[i] != r[j] && (s&bit(r[i]+5)) == 0 && (s&bit(r[j]+5)) == 0)
					return false;

			} else {

				if ((s&bit(l[i])) || (s&bit(l[j])))
					continue;

				if (r[i] != r[j] && ( (s&bit(r[i]+5)) || (s&bit(r[j]+5)) ))
					continue;

				return false;
			}
		}
	}
	return true;
}

int main () {
	char str[N];
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%s", str);
		l[i] = cal(str[0]);
		r[i] = str[1] - '1';
	}

	int ans = 10;
	for (int i = 0; i < (1<<10); i++) {
		int cnt = bitCount(i);

		if (cnt >= ans)
			continue;

		if (judge(i))
			ans = cnt;
	}
	printf("%d\n", ans);
	return 0;
}

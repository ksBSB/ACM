#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1<<22;
typedef long long ll;

int n, len;
char str[maxn], ch;

bool solve () {
	ll ans = 1, tmp = 1e5;

	for (int i = 0; i < len; i++) {

		ll cnt = 1;
		if (str[i] == '$') {

			int j;
			for (j = i+1; str[j] != '$';) {
				ll k = 0;
				while (str[j++] == ' ')
					k++;

				if (k)
					j--;
				if ((k+1) > tmp / cnt)
					return true;
				/*
					*/

				cnt *= (k+1);

				if (cnt > tmp)
					return true;
			}
			i = j;
		} else if (str[i] == '{') {

			i++;
			while (str[i] != '}') {
				if (str[i++] == '|')
					cnt++;
			}

			if (cnt > tmp)
				return true;
		}

		ans *= cnt;
		tmp = 1e5 / ans;
	}

	if (ans > 1e5)
		return true;

	printf("%d\n", (int)ans);
	return false;
}

int main () {
	while (scanf("%d%c", &n, &ch) == 2) {
		len = 0;
		for (int i = 0; i < n; i++) {
			gets(str+len);
			len += strlen(str+len);
		}

		if (solve())
			printf("doge\n");
	}
	return 0;
}

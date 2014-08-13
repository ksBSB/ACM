#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 30;

int main () {
	char s[maxn];
	int cas, v[maxn], c[maxn];

	scanf("%d", &cas);
	while (cas--) {
		memset(v, 0, sizeof(v));
		memset(c, 0, sizeof(c));

		scanf("%s", s);
		for (int i = 0; i < 26; i++) {
			if (v[i])
				continue;

			int j = i, ret = 0;
			do {
				v[j] = 1;
				j = s[j] - 'A';
				ret++;
			} while (i != j);
			c[ret]++;
		}

		bool flag = true;
		for (int i = 2; i < 26; i += 2)
			if (c[i]&1)
				flag = false;
		printf("%s\n", flag ? "Yes" : "No");
	}
	return 0;
}

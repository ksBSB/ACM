#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 105;
const int maxc = 200;

int k, len1, len2, rec[maxc][3];
char str1[maxn], str2[maxn];

bool check (int l, int r, int pos) {
	for (int i = 0; i + l <= r; i++) {
		if (str2[l+i] != str2[pos+i])
			return false;
	}
	return true;
}

bool dfs (int pos1, int pos2) {
	if (pos1 == len1)
		return pos2 == len2;

	if (pos2 == len2)
		return false;

	char ch = str1[pos1];
	if (rec[ch][0] == -1) {

		rec[ch][0] = pos2;
		for (int i = 1; i <= k; i++) {
			rec[ch][1] = pos2+i-1;
			if (dfs(pos1+1, pos2 + i))
				return true;
		}
		rec[ch][0] = -1;
	} else {

		if (!check(rec[ch][0], rec[ch][1], pos2))
			return false;
		if (dfs(pos1+1, pos2 + rec[ch][1] - rec[ch][0] + 1))
			return true;
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%s%s", &k, str1, str2);
		memset(rec, -1, sizeof(rec));
		len1 = strlen(str1);
		len2 = strlen(str2);

		printf("%d\n", dfs(0,0) ? 1 : 0);
	}
	return 0;
}

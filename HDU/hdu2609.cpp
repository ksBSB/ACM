#include <stdio.h>
#include <string.h>
#include <string>
#include <set>
#include <algorithm>

using namespace std;
const int N = 205;

int n, len;
set<string> v;
char s[N], t[N];

int getMinString () {
	int i = 0, j = 1, k = 0;

	while (i + k < len && j + k < len) {
		if (s[i+k] == s[j+k]) {
			k++;
		} else {
			if (s[i+k] > s[j+k])
				i = i + k + 1;
			else 
				j = j + k + 1;
			k = 0;
			if (i == j) j++;
		}
	}
	return min(i, j);
}

void getMin (char* str) {
	str[len/2] = '\0';
	v.insert (str);
}

int main () {
	while (scanf("%d", &n) == 1) {
		v.clear();
		for (int i = 0; i < n; i++) {
			scanf("%s", t);
			strcpy(s, t);
			strcat(s, t);

			len = strlen(s);

			int k = getMinString ();
			getMin (s+k);
		}
		printf("%lu\n", v.size());
	}
	return 0;
}

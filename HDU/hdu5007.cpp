#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e4;

int len;
char s[maxn];

int judge (int k) {
	if (k + 3 < len) {
		if (strncmp(s + k, "iPod", 4) == 0 || strncmp(s + k, "iPad", 4) == 0)
			return 1;
	}

	if (k + 4 < len) { 
		if (strncmp(s + k, "Apple", 5) == 0)
			return 1;
	}

	if (k + 5 < len && strncmp(s + k, "iPhone", 6) == 0)
		return 1;

	if (k + 3 < len && strncmp(s + k, "Sony", 4) == 0)
		return 2;
	return 0;
}

int main () {
	while (gets(s)) {
		len = strlen(s);
		for (int i = 0; i < len; i++) {
			int k = judge(i);
			if (k == 1)
				printf("MAI MAI MAI!\n");
			else if (k == 2)
				printf("SONY DAFA IS GOOD!\n");
		}
	}
	return 0;
}

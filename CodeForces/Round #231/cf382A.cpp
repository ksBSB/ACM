#include <stdio.h>
#include <string.h>

const int N = 105;

int l, r, v[N];
char str[N], add[N];

void init () {
	scanf("%s%s", str, add);
	l = r = 0;
	memset(v, 0, sizeof(v));
	int i;
	for (i = 0; str[i] != '|'; i++) { l++; v[str[i] - 'A'] = 1; }
	for (i++; i < strlen(str); i++) { r++; v[str[i] - 'A'] = 2; }
}

bool solve () {
	for (int i = 0; i < strlen(add); i++) {
		if (l < r) {
			v[add[i] - 'A'] = 1; l++;
		} else {
			v[add[i] - 'A'] = 2; r++;
		}
	}
	if (l != r) return true;
	for (int i = 0; i < 26; i++) if (v[i] == 1) printf("%c", 'A' + i);
	printf("|");
	for (int i = 0; i < 26; i++) if (v[i] == 2) printf("%c", 'A' + i);
	printf("\n");
	return false;
}

int main () {
	init();
	if (solve()) printf("Impossible\n");
	return 0;
}

#include <stdio.h>
#include <string.h>

const int N = 505;
char str[N];
int a, b, c, s;

void init() {
	gets(str);

	s = a = b = c = 0;
	int len = strlen(str);

	for (int i = 0; i < len; i++) {
		if (str[i] == '|') {
			if (s == 0) a++;
			else if (s == 1) b++;
			else c++;
		} else s++;
	}
}

bool judge() {

	if (a + b - c == 2) {
		c++;
		if (a != 1) a--;
		else if (b != 1) b--;
	} else if (a + b - c == -2) {
		c--;
		a++;
	}

	if (a + b == c) {
		for (int i = 0; i < a; i++) printf("|");
		printf("+");
		for (int i = 0; i < b; i++) printf("|");
		printf("=");
		for (int i = 0; i < c; i++) printf("|");
		printf("\n");
		return true;
	}
	return false;
}

int main () {
	init();
	if (!judge()) printf("Impossible\n");
	return 0;
}

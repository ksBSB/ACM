#include <cstdio>
#include <cstring>

int l[4];
char str[105];

bool judgeLonger (int x) {
	for (int i = 0; i < 4; i++) {
		if (i == x)
			continue;

		if (l[i] * 2 > l[x])
			return false;
	}
	return true;
}

bool judgeShorter(int x) {
	for (int i = 0; i < 4; i++) {
		if (i == x)
			continue;

		if (l[i] < l[x] * 2)
			return false;
	}
	return true;
}

int main () {
	for (int i = 0; i < 4; i++) {
		scanf("%s", str);
		l[str[0]-'A'] = strlen(str+2);
	}

	int cnt = 0, ans = 0;

	for (int i = 0; i < 4; i++) {
		if (judgeLonger(i) || judgeShorter(i)) {
			cnt++;
			ans = i;
		}
	}

	if (cnt == 1)
		printf("%c\n", ans + 'A');
	else
		printf("C\n");
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 205;
const char sign[5] = "desu";

bool check (int pos, char* s) {
	for (int i = 0; i < 4; i++)
		if (s[pos+i] != sign[i])
			return false;
	return true;
}

int main () {
	int cas;
	char str[maxn];
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%s", str);
		int n = strlen(str);
		if (check(n - 4, str))
			str[n-4] = '\0';
		strcat(str, "nanodesu");
		printf("Case #%d: %s\n", kcas, str);
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;

char s[maxn], t[maxn];

bool judge () {
	int ms = 1;
	while (s[ms-1] == s[ms]) ms++;
	int mt = 1;
	while (t[mt-1] == t[mt]) mt++;

	if (s[0] != t[0] || ms < mt) return false;


	int m = strlen(t), p = mt, bo = false;
	//char pre = s[ms-1];
	for (int i = mt; i < m; i++) {
		if (s[p] == t[i]) {
		//	pre = s[ms];
			p++, bo = false;
		} else if (bo || t[i] != t[i-1]) {
			//pre = t[i];
			bo = true;
		} else {
			bo = false;
		}
	}
	//printf("!%c!\n", s[p]);
	return s[p] == '\0';
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s%s", s, t);
		printf("%s\n", judge() ? "Yes" : "No");
	}
	return 0;
}

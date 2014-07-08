#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main () {
	char ch;
	int cnt = 0, state = 0;
	while (scanf("%c", &ch) == 1) {
		if (state == 0 && (ch == 'd' || ch == 'D'))
			state++;
		else if (state == 1 && (ch == 'o' || ch == 'O'))
			state++;
		else if (state == 2 && (ch == 'g' || ch == 'G')) {
			state++;
		} else if (state == 3 && (ch == 'e' || ch == 'E')) {
			cnt++;
			state = 0;
		} else
			state = 0;
	}
	printf("%d\n", cnt);
	return 0;
}

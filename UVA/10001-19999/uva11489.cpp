#include <stdio.h>
#include <string.h>

const int N = 1005;
int s, n, c[20];

void init () {
	s = 0;
	memset(c, 0, sizeof(c));

	char str[N];
	scanf("%s", str);	
	n = strlen(str);
	for (int i = 0; i < n; i++) {
		int a = str[i] - '0';
		s += a;
		c[a]++;
	}
}

bool judge () {
	int t = s % 3;

	bool flag = true;
	for (int i = t; i < 10; i += 3) 
		if (c[i]) {
			flag = false;
			c[i]--;
			break;
		}

	if (flag) return false;

	int cnt = c[3] + c[6] + c[9];

	return !(cnt&1);
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init ();
		printf("Case %d: %c\n", i, judge() ? 'S' : 'T');
	}
	return 0;
}

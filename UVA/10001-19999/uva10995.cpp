#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

const int N = 50;
const int M = 5;

int s, t[M];

char str[N];

int cat (char* str) {
	int hh, mm, ss;
	sscanf(str, "%d:%d:%d", &hh, &mm, &ss);
	return hh * 60 * 60 + mm * 60 + ss;
}

void init () {
	s = cat(str);

	for (int i = 0; i < 4; i++) {
		scanf("%s", str);
		t[i] = cat(str);
	}
}

void solve () {
	double v[M];
	for (int i = 1; i < 3; i++)
		v[i] = 1.0 / (t[i] - s);
	v[3] = (t[1] - t[0]) * v[1] / (t[3] - t[0]);

	double d = (v[1] - v[3]) * (t[0] - s);
	int ans = (int)(d / (v[2] - v[3]) + 0.5);
	ans += s;
	
	int ss = ans % 60;
	ans /= 60;

	int mm = ans % 60;
	ans /= 60;

	int hh = ans % 24;
	printf("%02d:%02d:%02d\n", hh, mm, ss);
}

int main () {
	while (scanf("%s", str) == 1 && strcmp(str, "-1") != 0) {
		init();
		solve();
	}
	return 0;
}

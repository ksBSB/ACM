#include <stdio.h>
#include <string.h>
const int N = 10000;
const int M = 50;

int rec[N];

int change(char str[]) {
    int num = 0;
    for (int i = 0; i < 12; i++) {
	if (str[i] == 'o') num = num * 2 + 1;
	else num = num * 2;
    }
    return num;
}

int count(char str[]) {
    int cnt = 0;
    for (int i = 0; i < 12; i++)
	if (str[i] == 'o') cnt++;
    return cnt;
}

int dp(char str[]) {
    int now = change(str);
    if (rec[now] >= 0)	return rec[now];
    int& cnt = rec[now];
    cnt = count(str);

    for (int i = 1; i < 11; i++) {
	if (str[i] == 'o') {
	    if (str[i - 1] == 'o' && str[i + 1] == '-') {
		str[i - 1] = str[i] = '-', str[i + 1] = 'o';
		int cur = dp(str);
		str[i - 1] = str[i] = 'o', str[i + 1] = '-';
		if (cur < cnt) cnt = cur;
	    }
	    else if (str[i - 1] == '-' && str[i + 1] == 'o') {
		str[i - 1] = 'o', str[i] = str[i + 1] = '-';
		int cur = dp(str);
		str[i - 1] = '-', str[i] = str[i + 1] = 'o';
		if (cur < cnt) cnt = cur;
	    }
	}
    }
    return cnt;
}

int main() {
    int cas;
    char str[M];
    memset(rec, -1, sizeof(rec));
    scanf("%d", &cas);
    while (cas--) {
	scanf("%s", str);
	printf("%d\n", dp(str));
    }
    return 0;
}

#include <stdio.h>
#include <string.h>

const int N = 10005;

int count(char str[]) {
    int cnt = 0, len = strlen(str);
    for (int i = 0; i < len; i++)
	if (str[i] == 'X')
	    cnt++;
    return cnt;
}

int main() {
    char str[N];
    int n, max, sum, tmp;
    while (scanf("%d%*c", &n), n) {
	max = sum = 0;
	for (int i = 0; i < n; i++) {
	    gets(str);
	    tmp = count(str);
	    if (max < tmp)
		max = tmp;
	    sum += tmp;
	}
	printf("%d\n", max * n - sum );
    }
    return 0;
}

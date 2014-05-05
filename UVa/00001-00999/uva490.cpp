#include <stdio.h>
#include <string.h>
const int N = 107;
char str[N][N];

int main() {
    int n = 0, len = 0;
    memset(str, 0, sizeof(str));
    while (gets(str[n])) {
	int a = strlen(str[n++]);
	if (len < a)
	    len = a;
    }

    for (int i = 0; i < n; i++)
	for (int j = 0; j < len; j++)
	    if (!str[i][j])
		str[i][j] = ' ';

    for (int i = 0; i < len; i++) {
	for (int j = n - 1; j >= 0; j--)
	    printf("%c", str[j][i]);
	printf("\n");
    }
    return 0;
}

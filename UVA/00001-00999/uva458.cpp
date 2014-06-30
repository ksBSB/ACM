#include <stdio.h>
#include <string.h>
const int N = 1005;
int main() {
    char s[N];
    while (gets(s)) {
	int len = strlen(s);
	for (int i = 0; i < len; i++)
	    s[i] = s[i] - 7;
	puts(s);
    }
    return 0;
}

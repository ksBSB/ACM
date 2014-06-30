#include <stdio.h>
#include <string.h>

const int N = 10005;

bool judge(char c) {
    if (c >= 'a' && c <= 'z')
	return true;
    else if (c >= 'A' && c <= 'Z')
	return true;
    return false;
}

int main() {
    char str[N];
    while (gets(str)) {
	int len = strlen(str), flag = 0, n = 0;
	for (int i = 0; i < len; i++) {
	    if (judge(str[i])) {
		if (flag)   continue;
		flag = 1;
		n++;
	    }
	    else
		flag = 0;
	}
	printf("%d\n", n);
    }
    return 0;
}
